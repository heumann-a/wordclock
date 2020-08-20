#include "webserver.h"
#include "webgui.h"
#include "webcontroller.h"

void WebServer::setup() {
    WebServer::IP = WiFi.localIP().toString();

    WebServer::httpwebserver.on("/", WebController::index);
	
    // HttpServer::web.on("/manifest.json", Controller::getManifest);
	// HttpServer::web.on("/logo.svg", Controller::getLogoSvg);

	// HttpServer::web.on("/api/color", HTTP_PUT, Controller::saveColor);
	// HttpServer::web.on("/api/time", HTTP_PUT, Controller::saveTime);
	// HttpServer::web.on("/api/dnd", HTTP_PUT, Controller::saveDnd);
	// HttpServer::web.on("/api/wifi", HTTP_DELETE, Controller::deleteWiFi);

    WebServer::httpwebserver.onNotFound(WebController::notFound);
    WebServer::httpwebserver.begin();
}

void WebServer::loop() {
    WebServer::httpwebserver.handleClient();
}

ESP8266WebServer WebServer::httpwebserver(80);
String WebServer::IP;