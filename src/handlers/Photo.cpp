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
  vector<json> content;
  mysqlpp::ScopedConnection conn(*pool);
  mysqlpp::Query query = conn->query("select pid, src from photo");
  if (mysqlpp::StoreQueryResult res = query.store()) {
    for (auto &row : res) {
      json rec = json::parse(fmt::sprintf(R"({
        "pid": "%s",
        "src": "%s"
      })", row[0], row[1]));
      content.push_back(rec);
    }
  }
  return return_json("", content);
}

crow::response PhotoHandler::Post() {
  return return_json("");
}