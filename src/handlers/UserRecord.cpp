#include <mysql++.h>
#include "ConnectionPool.hpp"
#include "Exception.hpp"
#include "Handlers.hpp"
#include "defines.hpp"
#include "fmt/format.h"
#include "fmt/printf.h"

using namespace PuzzleServer;

UserRecordHandler::UserRecordHandler(const crow::request &r) : BaseController(r) {}

crow::response UserRecordHandler::Get() {
  return return_json("");
}

crow::response UserRecordHandler::Post() {
  return return_json("");
}