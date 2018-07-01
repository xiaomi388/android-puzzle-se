#include <mysql++.h>
#include "ConnectionPool.hpp"
#include "Exception.hpp"
#include "Handlers.hpp"
#include "defines.hpp"
#include "fmt/format.h"
#include "fmt/printf.h"

using namespace PuzzleServer;

RecordHandler::RecordHandler(const crow::request &r) : BaseController(r) {}

crow::response RecordHandler::Get() {
  return return_json("");
}

crow::response RecordHandler::Post() {
  return return_json("");
}