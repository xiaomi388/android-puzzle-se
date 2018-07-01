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
  vector<json> content;
  auto mode = req.url_params.get("mode");
  auto uid = this->get_current_user_id();
  string sql;

  if(mode == nullptr) { //all records
    sql = fmt::format(
    "select mode, score, time from record where uid = {} order by score limit 10", escapeSQL(uid));
  }
  else { //record sort by mode
    sql=fmt::format(
      "select mode, score, time from record where uid = {} and mode = {} order by score limit 10", 
      escapeSQL(uid), escapeSQL(mode));
  }

  mysqlpp::ScopedConnection conn(*pool);
  mysqlpp::Query query = conn->query(sql);

  if (mysqlpp::StoreQueryResult res = query.store()) {
    for (auto &row : res) {
      json rec = json::parse(fmt::sprintf(R"({
        "mode": "%s",
        "score": "%s",
        "time": "%s"
      })", row[0], row[1], row[2]));
      content.push_back(rec);
    }
  }
  return return_json("", content);
}

crow::response UserRecordHandler::Post() {
  return return_json("");
}