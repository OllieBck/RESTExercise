/*
  Repeating Wifi Web Client

  This sketch connects to a a web server and makes a request
  using an Arduino Wifi shield.

  Circuit:
   WiFi shield attached to pins SPI pins and pin 7

  created 23 April 2012
  modified 31 May 2012
  by Tom Igoe
  modified 13 Jan 2014
  by Federico Vanzati

  http://arduino.cc/en/Tutorial/WifiWebClientRepeating
  This code is in the public domain.
*/

#include <SPI.h>
#include <WiFi101.h>

char ssid[] = "itpsandbox"; //  your network SSID (name)
char pass[] = "NYU+s0a!+P?";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

char redVal;
int greenVal;
int blueVal;

String inString = "";

//
boolean bodyStart = false;
boolean bodyEnd = false;
String body = "";
String request;

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
IPAddress server(159, 203, 190, 133); // numeric IP for Google (no DNS)
//char server[] = "job271.itp.io";    // name address for Google (using DNS)

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;

const int red = 5;
const int green = 4;
const int blue = 3;
const int lum = 2;

unsigned long lastConnectionTime = 0;            // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10L * 1000L; // delay between updates, in milliseconds

void setup() {
  //Initialize serial and wait for port to open:
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(lum, OUTPUT);
  Serial.begin(9600);

  /*
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  */
  
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  // you're connected now, so print out the status:
  printWifiStatus();
}

void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  //httpRequest();
  //stringConvert();

  while (client.available()) {
     char c = client.read();
    stringConvert(c);
  }

  // if ten seconds have passed since your last connection,
  // then connect again and send data:

  if (millis() - lastConnectionTime > postingInterval) {
    //int test = millis() - lastConnectionTime;
    //Serial.print(test);
    //Serial.println(postingInterval);
    httpRequest();
    //Serial.print(request);
  }
}

// this method makes a HTTP connection to the server:
void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 9999)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.println("GET /color HTTP/1.1");
    client.println("Host: job271.itp.io");
    //client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  }

  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

int stringConvert(char c) {
  if (c == '{') {
    Serial.println("start");
    bodyStart = true;
  }
  if (c == '}') {
    Serial.println("stop");
    Serial.print(body);
    bodyStart == false;
    bodyEnd == false;
    int redOne = body.indexOf(":");
    int redTwo = body.indexOf(",");
    int greenOne = body.indexOf(":", redOne + 1);
    int greenTwo = body.indexOf(",", redTwo + 1);
    int blueOne = body.indexOf(":", greenOne + 1);
    int blueTwo = body.indexOf(",", greenTwo + 1);
    int lumOne = body.indexOf(":", blueTwo + 1);
    int lumTwo = body.indexOf("}");

    String sRed = body.substring(redOne + 2, redTwo - 1);
    String sGreen = body.substring(greenOne + 2, greenTwo - 1);
    String sBlue = body.substring(blueOne + 2, blueTwo - 1);
    String sLum = body.substring(lumOne + 2, lumTwo - 1);

    analogWrite(red, 255 - sRed.toInt());
    analogWrite(green, 255 - sGreen.toInt());
    analogWrite(blue, 255 - sBlue.toInt());
    analogWrite(lum, sLum.toInt());

  }
  
  if (bodyStart == true && bodyEnd == false) {
    body += c;
  }
}


