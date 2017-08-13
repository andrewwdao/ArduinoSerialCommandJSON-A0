#include <SoftwareSerial.h>
#include <ArduinoJson.h>

/********************** Software Serial Setup *********************************/
#define RX D1  
#define TX D2
SoftwareSerial ROOM1 = SoftwareSerial(RX,TX,false,256);

void setup() {
  Serial.begin(57600); //optional, usually use together to debug.
  ROOM1.begin(57600); //turn on software serial to communicate with other arduino or esp

}

void loop() {
  //The message will be sent is structured like this: <COMMAND>\r<JSON string>\r
  //JSON String can be: {"action":"ON","id":"0DCD9435"} or {"action":"ON"} or more
  //You can add as many as Function as you want
  //But don't forget that COMMAND is limited to 16 separated command (in the shape of <COMMAND>\r<JSON string>\r)
  //in order to keep the connection stable
  ROOM1.print("COMMAND");
  ROOM1.print('\r');      // '' is a must, cannot use ""
  ROOM1.print("JSON String (include variables you want to deliver)");
  ROOM1.print('\r');

  //you can also use ROOM1.println(""); as well, but not for the purpose of transmit messages.
}
