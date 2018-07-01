#ifndef ROUTERS_H
#define ROUTERS_H

#include "Handlers.hpp"
#include "defines.hpp"

namespace PuzzleServer {


void initRoute(crow::App<crow::CookieParser> &app) {
  CROW_ROUTE(app, "/user")(BaseController::proxy<UserHandler>);
}

}  // namespace PuzzleServer

#endif