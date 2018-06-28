
#include <mysql++.h>
#include "defines.hpp"
#include "Handlers.hpp"
#include "ConnectionPool.hpp"
#include "fmt/format.h"
#include "fmt/printf.h"

using namespace PuzzleServer;

string UserHandler::Get(const crow::request& req) {
  vector<json> content;
  mysqlpp::ScopedConnection conn(*pool);
  mysqlpp::Query query = conn->query("select * from user");
  if (mysqlpp::StoreQueryResult res = query.store()) {
    for (auto &row : res) {
      json rec = json::parse(fmt::sprintf(R"({
        "uid": "%s",
        "username": "%s",
        "password": "%s"
      })", row[0], row[1], row[2]));
      content.push_back(rec);
    }
  }

  return BaseController::return_json("", content);
}

string UserHandler::Post(const crow::request& req) {
  std::ostringstream os;
  return os.str();
}
