#include "webcontroller.h"
#include "webserver.h"
#include "webgui.h"
#include "wifi.h"
#include "ntptime.h"


void WebController::index() {
    String Content = WebGui::index();

    WebServer::httpwebserver.sendHeader("Location", "http://" + WebServer::IP);
    WebServer::httpwebserver.send(200, "text/html", Content);
}

void WebController::notFound() {
  if (WebServer::httpwebserver.method() == HTTP_OPTIONS) {
    WebServer::httpwebserver.sendHeader("Allow", "DELETE,GET,HEAD,OPTIONS,POST,PUT");
    WebServer::httpwebserver.send(200, "text/html", "");

    return;
  }

  WebServer::httpwebserver.send(404, "text/html", "NOT FOUND");
}