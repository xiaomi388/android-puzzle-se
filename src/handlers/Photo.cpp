#include <mysql++.h>
#include "ConnectionPool.hpp"
#include "Exception.hpp"
#include "Handlers.hpp"
#include "defines.hpp"
#include "fmt/format.h"
#include "fmt/printf.h"

using namespace PuzzleServer;

PhotoHandler::PhotoHandler(const crow::request &r) : BaseController(r) {}

crow::response PhotoHandler::Get() {
  return return_json("");
}

crow::response PhotoHandler::Post() {
  return return_json("");
}