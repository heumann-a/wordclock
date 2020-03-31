/*
Code by Heumann
Project for Wordclock with Wifi NTP updates
- March 2020
*/

#include "wifi.h"
#include "ntptime.h"
#include "webserver.h"

// Var to initialize local AP
IPAddress Current_IP(192,168,1,5);
IPAddress gateway(192,168,1,10);
IPAddress subnet(255,255,255,0);


// void startWebServer(){
//   server.begin();
//   Serial.print("Server is at: ");
//   Serial.println(Current_IP);
// }

// void displayNetworks(WiFiClient &client){
//   byte numSsid = WiFi.scanNetworks();
//   // print the list of networks seen:
//   client.print("<p>SSID List:  ");
//   client.print(numSsid);
//   client.println("</p>");
//   // print the network number and name for each network found:
//   for (int thisNet = 0; thisNet<numSsid; thisNet++) {
//     client.print("<p>");
//     client.print(thisNet);
//     client.print(") Network: ");
//     client.print(WiFi.SSID(thisNet));
//     client.println("</p>");
//   }
// }

// void sendWebsite(WiFiClient &client){
//   // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
//   // and a content-type so the client knows what's coming, then a blank line:
//   client.println("HTTP/1.1 200 OK");
//   client.println("Content-Type: text/html");
//   client.println("Connection: close");
//   client.println();

//   // Here comes the get values of Input fields


//   // Display the HTML web page
//   client.println("<!DOCTYPE HTML><html>");
//   client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
//   client.println("<link rel=\"icon\" href=\"data:,\">");
  
//   // CSS to style everything
//   client.println("<style>html { font-family: Helvetica; }"); 
//   client.println("</style>");

//   // Web Page Title
//   client.println("<title>Sebi & Eli Wortuhr</title>");

//   // Script for send InputData
//   client.println("<script>strText = \"ad\";");
//   client.println("function SendText() {");
//   client.println("nocache = \"&nocache=\" + Math.random() * 1000000;");
//   client.println("var request = new XMLHttpRequest();");
//   client.println("strText = \"&txt=\" + document.getElementById(\"txt_form\").form_text.value + \"&end=end\";");
//   client.println("request.open(\"GET\", \"ajax_inputs\" + strText + nocache, true);");
//   client.println("request.send(null);}</script>");
//   client.println("</head>");

//   // Web Page Data
//   client.println("<body>");
//   // Web Page Headline
//   client.println("<h1>&#10084 Willkommen Sebi & Eli &#10084</h1>");
//   // Available WiFis
//   displayNetworks(client);

//   // Input Fields for Setting Wifi Data
//   client.println("<br><p>SSID:</p>");
//   client.println("<input type=\"text\" name=\"SSID\" value=\"\"><br>");
//   client.println("<p>Passwort:</p>");
//   client.println("<input type=\"text\" name=\"Passwort\" value=\"\">");

//   // Close HTML Tags
//   client.println("</font></body>");
//   client.println("</html>");
// }

// void serveWebServer(){
//   WiFiClient client = server.available();
//   if (client) {
//     Serial.println("New Client");
//     // an http request ends with a blank line
//     boolean currentLineIsBlank = true;
//     while (client.connected()) {
//       if (client.available()) {
//         char c = client.read();
//         Serial.write(c);
//         // if you've gotten to the end of the line (received a newline
//         // character) and the line is blank, the http request has ended,
//         // so you can send a reply
//         if (c == '\n' && currentLineIsBlank) {
//           // send a standard http response header
//           sendWebsite(client);
//           break;
//         }
//         if (c == '\n') {
//           // you're starting a new line
//           currentLineIsBlank = true;
//         } 
//         else if (c != '\r') {
//           // you've gotten a character on the current line
//           currentLineIsBlank = false;
//         }
//       }
//     }
//     // give the web browser time to receive the data
//     delay(1);
//     // close the connection:
//     client.stop();
//     Serial.println("client disonnected");
//   }
// }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  WLAN::setup();
  NTPTime::setup();
}

void loop() {
  // put your main code here, to run repeatedly
  NTPTime::loop();
  delay(3000);
}
