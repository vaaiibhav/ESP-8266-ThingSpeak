
#include "SoftwareSerial.h"


#define IP "184.106.153.149" // ThingSpeak IP Address: 184.106.153.149
String ssid = "Camimac";

String password = "codefishacademy@123";

SoftwareSerial esp(6, 7);// RX, TX

unsigned long myChannelNumber = 209451;
const char * myWriteAPIKey = "X79KH9GADR6ZG3OA";

String server = "api.thingspeak.com";
// GET /update?key=[THINGSPEAK_KEY]&field1=[data 1]&field2=[data 2]...;
String GET = "GET /update?key=X79KH9GADR6ZG3OA";

void setup() {


  esp.begin(9600);

  Serial.begin(9600);

  reset();

  connectWifi();
  //ThingSpeak.begin(client);

}

//reset the esp8266 module

void reset() {

  esp.println("AT+RST");

  delay(1000);

  if (esp.find("OK") ) Serial.println("Module Reset");

}

//connect to your wifi network

void connectWifi() {
  esp.println("AT+CWMODE=1");

  esp.println("AT+CIPMUX=1");
  String cmd = "AT+CWJAP=\"" + ssid + "\",\"" + password + "\"";
  Serial.println("Connecting");
  esp.println(cmd);
  Serial.println(cmd);
  delay(4000);

  if (esp.find("OK")) {

    Serial.println("WIFI Connected!");
    delay(2000);
  }

  else {



    Serial.println("Cannot connect to wifi");
    
    delay(5000);
    Serial.println("Reconnecting");
    connectWifi();
  }

}





void loop () {
  int voltage = 12;
  //thingspeak();
  Serial.println("Sending Data to Thingspeak");
  delay(2000);
  //ThingSpeak.writeField(myChannelNumber, 1, voltage, myWriteAPIKey);
  thngspks();
  delay(2000);


  delay(20000);

}




void thngspks() {
  

   String cmd = "AT+CIPSTART=1\",""TCP\",\"";// Setup TCP connection
  cmd += server;
  cmd += "\",80";
  //sendDebug(cmd);
  delay(2000);
  
  delay(2000);
  esp.println(cmd);
  Serial.println(cmd);
  delay(4000);
  if (esp.find("OK")) {
    Serial.println("Linked..");
  }
 delay(2000);
  String T="12.5";
  String L="15.8";
  String H="21.8";
  
  String GET = "GET /update?key=X79KH9GADR6ZG3OA";  
  String cmds = GET + "&field1=" + T +"&field2="+ L + "&field3=" + H +"\r\n\r\n";
//  esp.println("AT+CIPMUX=1");
  Serial.println(cmds);
  delay(2000);

   String stringLength="AT+CIPSEND=";
    stringLength +=String(cmds.length( ));
    esp.println(stringLength);
    Serial.println(stringLength);
//  esp.print("AT+CIPSEND=1,");
//  esp.println(cmds.length());
// 
 //  Serial.println(String(cmds.length()));

  if (esp.find(">")){
  Serial.println("Ready to Send");
  }

  delay(5000);
 

  esp.println(cmds);
  Serial.println("Data Sent is "+cmds);
  if (esp.find("OK")) {
    Serial.println("Sent Succesfully..");
    delay(1000);
  }

  else {
    Serial.println("UnSuccesfull..");
  }

  delay(20000);




  esp.println("AT+CIPCLOSE");
  Serial.println("AT+CLOSE");

}
