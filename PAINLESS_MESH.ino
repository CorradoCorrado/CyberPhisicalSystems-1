#include "painlessMesh.h"
#include <Arduino_JSON.h>

// MESH Details
#define   MESH_PREFIX     "MESH1234" //name for your MESH
#define   MESH_PASSWORD   "MESH1234" //password for your MESH
#define   MESH_PORT       5555 //default port

//Number for this node
int nodeNumber = 3;

String readings;

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;

// User stub
void sendMessage() ; 
void repeatMessage() ; 
String getReadings();

String getReadings () {
  JSONVar jsonReadings;
  jsonReadings["node"] = 1;
  jsonReadings["msg"] = 1;
  readings = JSON.stringify(jsonReadings);
  return readings;
}

void sendMessage () {
  String msg = getReadings();
  mesh.sendBroadcast(msg);
}

void repeatMessage (String msg_1) {
  mesh.sendBroadcast(msg_1);
}

// Needed for painless library
void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("Received from %u msg=%s\n", from, msg.c_str());
  JSONVar myObject = JSON.parse(msg.c_str());
  int node = myObject["node"];
  int temp = myObject["data"];
  if (node != nodeNumber){
    repeatMessage(msg);
  }else{
    blinkLED();
  }
    
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}

void setup() {
  Serial.begin(115200);
  pinMode(2,OUTPUT);


  //mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  //userScheduler.addTask(taskSendMessage);
  //taskSendMessage.enable();
}

void blinkLED(){
  digitalWrite(2,HIGH);
  delay(50);
  digitalWrite(2,LOW);
}


void loop() {
  // it will run the user scheduler as well
  mesh.update();
}
