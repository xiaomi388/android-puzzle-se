#ifndef ROUTERS_H
#define ROUTERS_H

#include "Handlers.hpp"
#include "defines.hpp"

namespace PuzzleServer {


void initRoute(crow::App<crow::CookieParser> &app) {
  CROW_ROUTE(app, "/user")(BaseController::proxy<UserHandler>);
  CROW_ROUTE(app, "/photo")(BaseController::proxy<PhotoHandler>);
  CROW_ROUTE(app, "/record")(BaseController::proxy<RecordHandler>);
  CROW_ROUTE(app, "/user/record")(BaseController::proxy<UserRecordHandler>);
}

}  // namespace PuzzleServer

#endif