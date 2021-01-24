#include <WiFi.h>
const char* ssid     = "Mr.Hvidsten";
const char* password = "*****";

WiFiServer server(80);
 
void setup()
{
    pinMode(12, OUTPUT);
    Serial.begin(115200);
    delay(10);
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
 
    WiFi.begin(ssid, password);
 
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
 
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();
 
}
 
int value = 0;
 
void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

int t6val = touchRead(T6);
Serial.print("T6 value: ");
Serial.println(t6val);
 if (t6val <= 38){
              digitalWrite(12, LOW);
            }else{
              digitalWrite(12, HIGH);
            }
            
  
 
  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character
 
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
 
            // the content of the HTTP response follows the header:
            if (t6val <= 38){
              client.print("<h1> WATER LEVEL OK </h1>");
             
            }else{
              client.print("<h1> PLEASE FILL MORE WATER ON COFFEE MACHINE </h1>");
              
            }
            
 
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
  
}
