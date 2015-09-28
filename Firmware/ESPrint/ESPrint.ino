]#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
const char* ssid = "Myndale Mobile";
const char* password = "mongerasasasd";

const char page[] PROGMEM = 
"<!DOCTYPE html><html><head> <meta charset=\"utf-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> <title>Multi-page template</title> <link rel=\"stylesheet\" "
"href=\"http://code.jquery.com/mobile/1.4.4/jquery.mobile-1.4.4.min.css\"/><script src=\"http://code.jquery.com/jquery-1.11.1.min.js\"></script><script src=\"http://code.jquery.com/mobile/"
"1.4.4/jquery.mobile-1.4.4.min.js\"></script></head><body> <div data-role=\"page\"> <div data-role=\"header\" data-position=\"fixed\"> <h1>ESPrint</h1> </div><div data-role=\"tabs\"> <div d"
"ata-role=\"navbar\"> <ul> <li><a href=\"#bot\" class=\"ui-btn-active\" data-theme=\"a\" data-ajax=\"false\">Bot</a></li><li><a href=\"#extruder\" data-theme=\"a\" data-ajax=\"false\">Extrud"
"er</a></li><li><a href=\"#sdcard\" data-theme=\"a\" data-ajax=\"ignore\">SD Card</a></li></ul> </div><div id=\"bot\" class=\"ui-content\"> <div class=\"ui-grid-b\"> <div class=\"ui-block-a\">"
"<a href=\"#\" class=\"ui-shadow ui-btn ui-corner-all\">X:</a></div><div class=\"ui-block-b\"><a href=\"#\" class=\"ui-shadow ui-btn ui-corner-all\">Left</a></div><div class=\"ui-block-c\"><a "
"href=\"#\" class=\"ui-shadow ui-btn ui-corner-all\">Right</a></div></div><div class=\"ui-grid-b\"> <div class=\"ui-block-a\"><a href=\"#\" class=\"ui-shadow ui-btn ui-corner-all\">Y:</a></div>"
"<div class=\"ui-block-b\"><a href=\"#\" class=\"ui-shadow ui-btn ui-corner-all\">Forward</a></div><div class=\"ui-block-c\"><a href=\"#\" class=\"ui-shadow ui-btn ui-corner-all\">Back</a></div>"
"</div><div class=\"ui-grid-b\"> <div class=\"ui-block-a\"><a href=\"#\" class=\"ui-shadow ui-btn ui-corner-all\">Z:</a></div><div class=\"ui-block-b\"><a href=\"#\" class=\"ui-shadow ui-btn "
"ui-corner-all\">Up</a></div><div class=\"ui-block-c\"><a href=\"#\" class=\"ui-shadow ui-btn ui-corner-all\">Down</a></div></div></div><div id=\"extruder\" class=\"ui-content\"> <h1>Extruder</h1>"
"</div><div id=\"sdcard\" class=\"ui-content\"> <h1>SD Card</h1> </div></div><div data-role=\"footer\" data-position=\"fixed\"> <button class=\"ui-btn ui-corner-all ui-shadow\">Stop All</button> "
"</div></div></body></html>";

void* __dso_handle;

ESP8266WebServer server(80);

char send_buffer[257];

void send_to_server(const char * content)
{
  server.send(200, "text/html");
  while (*content)
  {
    int i;
    for (i=0; (i<sizeof(server)-1) && *content; i++)
      send_buffer[i] = pgm_read_byte(content++);
    send_buffer[i] = '\0';
    server.client().print(send_buffer);
  }
}
 
const int led = 2;
 
void handle_root() {
  digitalWrite(led, 1);
  //server.send(200, "text/plain", "hello from esp8266!");
  send_to_server(page);
  delay(100);
  digitalWrite(led, 0);
}
 
void setup(void)
{
  Serial.begin(115200);
  Serial.println("Starting....");
  
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.println("");

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
   
  server.on("/", handle_root);
  
  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });
  
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void)
{
  server.handleClient();
} 
