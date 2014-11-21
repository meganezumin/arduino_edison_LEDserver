#include <WiFi.h>
 
char ssid[] = "SSID";      //  your network SSID (name) 
char pass[] = "password";   // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)
 
int status = WL_IDLE_STATUS;
WiFiServer server(70);
 
void setup() {
  pinMode(9, OUTPUT);      // set the LED pin mode
 if (WiFi.status() == WL_NO_SHIELD) {
    while(true);        // don't continue
  } 
 
  while ( status != WL_CONNECTED) { 
    status = WiFi.begin(ssid, pass);
    delay(10000);
  } 
  server.begin();                           // start the web server on port 80
}
 
 
void loop() {
  WiFiClient client = server.available();   // listen for incoming clients
 
  if (client) {                             // if you get a client,
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        if (c == '\n') {                    // if the byte is a newline character
 
          if (currentLine.length() == 0) {  
 
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
 
            client.print("Click <a href=\"/H\">here</a> turn the LED on pin 9 on<br>");
            client.print("Click <a href=\"/L\">here</a> turn the LED on pin 9 off<br>");
 
            client.println();
 
            break;         
          } 
          else {
            currentLine = "";
          }
        }     
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
 
        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(9, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(9, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
  }
}
