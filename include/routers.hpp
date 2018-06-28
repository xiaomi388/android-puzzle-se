#ifndef ROUTERS_H
#define ROUTERS_H

#include "Handlers.hpp"
#include "defines.hpp"

namespace PuzzleServer {


void initRoute(crow::SimpleApp &app) {
  CROW_ROUTE(app, "/user").methods("GET"_method)(UserHandler::Get);
  CROW_ROUTE(app, "/user").methods("POST"_method)(UserHandler::Post);
}

}  // namespace PuzzleServer

#endif