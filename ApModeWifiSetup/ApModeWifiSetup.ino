/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "ShihM_n_ShangL_Photos";
const char* password = "02140214";
IPAddress local_IP(192, 168, 5, 20);  
IPAddress gateway(192, 168, 5, 1);
IPAddress subnet(255, 255, 255, 0);

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

String mySSID;
String myPassword;
String myURL;


void setup() {
  Serial.begin(921600);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAPConfig(local_IP,gateway,subnet);
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ShihMei and ShangLun's Photo Frame Setup <3</h1>");
            
            // Form for user input
            client.println("<form action=\"/submit\" method=\"get\">");
            client.println("Wifi SSID: <input type=\"text\" name=\"wifiSsid\"><br>");
            client.println("Wifi PWD : <input type=\"text\" name=\"wifiPwd\"><br>");
            client.println("Photo url: <input type=\"text\" name=\"photoUrl\"><br>");
            client.println("<input type=\"submit\" value=\"Submit\"></form>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        } else if (currentLine.startsWith("GET /submit")) 
        {
          // Extract SSID, password, and URL from the GET request
          int ssidStart = header.indexOf("wifiSsid=");
          int ssidEnd = header.indexOf("&", ssidStart);
          String submittedSSID = header.substring(ssidStart + 9, ssidEnd);
          if (submittedSSID != "") mySSID=submittedSSID;

          int pwdStart = header.indexOf("wifiPwd=");
          int pwdEnd = header.indexOf("&", pwdStart);
          String submittedPassword = header.substring(pwdStart + 8, pwdEnd);
          if (submittedPassword != "") myPassword=submittedSSID;

          int urlStart = header.indexOf("photoUrl=");
          int urlEnd = header.indexOf(" ", urlStart);
          String submittedURL = header.substring(urlStart + 9, urlEnd);
          if (submittedURL != "") myURL=submittedURL;

          Serial.print("mySSID: ");
          Serial.println(mySSID);
          Serial.print("myPassword: ");
          Serial.println(myPassword);
          Serial.print("myURL: ");
          Serial.println(myURL);
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
