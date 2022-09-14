#include <WiFi.h>
#include <WiFiUdp.h>

/* WiFi network name and password */
// Your wirelless router ssid and password
//const char * ssid = "PT. SAS Aero"; 
//const char * pwd = "elanghitam";
//192.168.18.71
const char * ssid = "CharGG"; 
const char * pwd = "kirikanan";
//192.168.184.37

// IP address to send UDP data to.
// it can be ip address of the server or 
// a network broadcast address
// here is broadcast address
const char * udpAddress = "192.168.184.14"; // your pc ip
const int udpPort = 8080; //port server

long i=1;
float iFloat;
char iString[50] = "hello world";
char iTest[50] = "Test to Server";

#define nBuffer 100
char bufferData[nBuffer] = "hello world";
#define fBuffer 100
char bufferFeed[fBuffer] = " back to ";

//create UDP instance
WiFiUDP udp;

void setup(){
  Serial.begin(115200); // to monitor activity
  
  //Connect to the WiFi network
  WiFi.begin(ssid, pwd);
  

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //This initializes udp and transfer buffer
  udp.begin(udpPort);

    sprintf(bufferData, "%s;",iTest);
    Serial.println(bufferData);
    
    //send "test to Server" to server
    udp.beginPacket(udpAddress, udpPort);
    udp.print(bufferData);
    udp.endPacket();
    memset(bufferData, 0, nBuffer);
}

void loop(){
  //data dummy
  i++;
  iFloat = i/3.14;
  

  //----------------------------SEND
//  sprintf(bufferData, "%s;%d;%.3f",iString,i,iFloat);
//  Serial.println(bufferData);
//  
//  //send hello world to server
//  udp.beginPacket(udpAddress, udpPort);
//  //udp.beginPacket(udp.remoteIP(), udp.remotePort());
//  udp.print(bufferData);
//  udp.endPacket();
//  memset(bufferData, 0, nBuffer);
  //----------------------------SEND


  //----------------------------RECEIVE
  //processing incoming packet, must be called before reading the buffer
  udp.parsePacket();
  //receive response from server, it will be HELLO WORLD
  if(udp.read(bufferData, 50) > 0){
    Serial.print("Server to client: ");
    Serial.println((char *)bufferData);
  //----------------------------RECEIVE
    //----------------------------SEND
    udp.beginPacket(udpAddress, udpPort);
    udp.print(bufferData);
    udp.print(bufferFeed);
    udp.print(WiFi.localIP());
    udp.endPacket();
    memset(bufferData, 0, fBuffer);
    //----------------------------SEND
  }


  
  //Optional
  delay(100);
}
