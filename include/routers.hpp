#ifndef ROUTERS_H
#define ROUTERS_H

#include "defines.hpp"
#include "handlers/test.hpp"


namespace PuzzleServer {

void initRoute(crow::SimpleApp &app) {
    CROW_ROUTE(app, "/").methods("GET"_method)(TestHandler::get);
}

} // namespace PuzzleServer

#endif