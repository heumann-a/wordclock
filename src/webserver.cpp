#include "webserver.h"
#include "webcontroller.h"

void WebServer::setup() {
    WebServer::IP = WiFi.localIP().toString();

    WebServer::httpwebserver.on("/", WebController::index);

    WebServer::httpwebserver.onNotFound(WebController::notFound);

    WebServer::httpwebserver.begin();
}

void WebServer::loop() {
    WebServer::httpwebserver.handleClient();
}

ESP8266WebServer WebServer::httpwebserver(80);
String WebServer::IP;