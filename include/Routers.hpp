#ifndef ROUTERS_H
#define ROUTERS_H

#include "Handlers.hpp"
#include "defines.hpp"

namespace PuzzleServer {


void initRoute(crow::App<crow::CookieParser> &app) {
  CROW_ROUTE(app, "/user").methods("POST"_method, "GET"_method)(BaseController::proxy<UserHandler>);
  CROW_ROUTE(app, "/photo").methods("POST"_method, "GET"_method)(BaseController::proxy<PhotoHandler>);
  CROW_ROUTE(app, "/record").methods("POST"_method, "GET"_method)(BaseController::proxy<RecordHandler>);
  CROW_ROUTE(app, "/user/record").methods("POST"_method, "GET"_method)(BaseController::proxy<UserRecordHandler>);
}

}  // namespace PuzzleServer

#endif