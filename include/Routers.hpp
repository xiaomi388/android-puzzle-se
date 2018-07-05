#ifndef ROUTERS_H
#define ROUTERS_H

#include "Handlers.hpp"
#include "defines.hpp"
#include "SessionParser.hpp"

namespace PuzzleServer {


void initRoute(crow::App<SessionParser> &app) {
  CROW_ROUTE(app, "/user").methods("POST"_method, "GET"_method)(BaseController::proxy<UserHandler>);
  CROW_ROUTE(app, "/photo").methods("POST"_method, "GET"_method)(BaseController::proxy<PhotoHandler>);
  CROW_ROUTE(app, "/record").methods("POST"_method, "GET"_method)(BaseController::proxy<RecordHandler>);
  CROW_ROUTE(app, "/user/record").methods("POST"_method, "GET"_method)(BaseController::proxy<UserRecordHandler>);
  CROW_ROUTE(app, "/user/info").methods("POST"_method,"GET"_method)(BaseController::proxy<UserInfoHandler>);
}

}  // namespace PuzzleServer

#endif