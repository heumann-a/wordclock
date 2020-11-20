#include "webserver.h"
#include "webgui.h"
#include "controller.h"

void WebServer::setup() {
    WebServer::IP = WiFi.localIP().toString();

    WebServer::httpwebserver.on("/", Controller::index);
	
        WebServer::httpwebserver.on("/manifest.json", Controller::getManifest);
        WebServer::httpwebserver.on("/logo.svg", Controller::getLogoSvg);

        WebServer::httpwebserver.on("/api/color", HTTP_PUT, Controller::saveColor);
        WebServer::httpwebserver.on("/api/time", HTTP_PUT, Controller::saveTime);
        WebServer::httpwebserver.on("/api/dnd", HTTP_PUT, Controller::saveDnd);
        WebServer::httpwebserver.on("/api/wifi", HTTP_DELETE, Controller::deleteWiFi);
        WebServer::httpwebserver.onNotFound(Controller::notFound);

    WebServer::httpwebserver.begin();
}

void WebServer::loop() {
    WebServer::httpwebserver.handleClient();
}

ESP8266WebServer WebServer::httpwebserver(80);
String WebServer::IP;