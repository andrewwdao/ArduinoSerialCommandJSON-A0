#include <SoftwareSerial.h>
#include <SerialCommand.h> 
#include <ArduinoJson.h>

/********************** Software Serial Setup *********************************/
#define RX 3          // pin 3 is used for RX
#define TX 2          // pin 2 is used for TX
SoftwareSerial espSerial = SoftwareSerial(RX, TX); // object which get signal from ESP
SerialCommand server(espSerial); // Initialize object which use the Serial Command A0 library

void setup() {
  Serial.begin(57600); //optional, usually use together to debug.
  espSerial.begin(57600); //turn on software serial to communicate with other arduino or esp


  server.addCommand("COMMAND",Function1);     //if it catch the message has COMMAND command, it will execute Function1
  server.addCommand("COMMAND2",Function2);
  //You can add as many as Function as you want
  //But don't forget that COMMAND is limited to 16 separated command (in the shape of <COMMAND>\r<JSON string>\r)
  //in order to keep the connection stable
  Serial.println(F("Waiting for command..."));

}

void loop() {
  server.readSerial();      //no need to add anything else
}

void Function1() {
  char *json = server.next(); //this is required to read the buffer of the server, it will return the JSON string you compress in the message
  Serial.println(F("Command recieved:"));
  Serial.println(json);
  String id = parsestring(json,"id");          // get the id, if the JSON is {"action":"ON","id":"0DCD9435"} or {"id":"0DCD9435"} or more
  server.clearBuffer(1);                       // clear the server buffer, it can be also 0 and 2 inside the bracket, for more information, see the library
  //done getting the message from the Sender, Function2 is the same

  //This is the new function that I have added
  while ("something here") {
  if (server.available()>0) {      // if there is new message from the server, the loop will stop
    break;                         //server.available() = 1 if there is new message comming, =0 if nothing new happend
    //this only work if server.clearBuffer(1); has been call before server.available();, outside the loop.
    //If not, server.available() will always=1
   }
  }
}
void Function2() {
  
}



//THIS IS THE FUNCTION TO GET THE INFORMATION YOU WANT IN THE JSON STRING RECIEVED
String parsestring(String json,String names)  {
   StaticJsonBuffer<200> jsonBuffer;   //create a json Buffer which can contain 200 characters
   //DynamicJsonBuffer jsonBuffer(300);  //use dynamic memory, but somehow make error in the previous project
   JsonObject& root = jsonBuffer.parseObject(json); //create an array name root, save the address of each member of root as the address of each member of json string
   if (!root.success()) {
    Serial.println("parseObject() failed");
    exit;
  }
  return root[names];
}


