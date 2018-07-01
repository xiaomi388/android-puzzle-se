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
  vector<json> content;
  auto mode = req.url_params.get("mode");
  string sql;

  if(mode == nullptr) { //all records
    sql = R"(
    select U.username, R.mode, R.score 
    from user U, record R 
    where U.uid = R.uid 
    order by R.score limit 10)";
  }
  else { //record sort by mode
    sql = fmt::format(R"(
    select U.username, R.mode, R.score 
    from user U, record R 
    where U.uid = R.uid and R.mode = {}
    order by R.score limit 10)", 
    escapeSQL(mode));
  }

  mysqlpp::ScopedConnection conn(*pool);
  mysqlpp::Query query = conn->query(sql);

  if (mysqlpp::StoreQueryResult res = query.store()) {
    for (auto &row : res) {
      json rec = json::parse(fmt::sprintf(R"({
        "username": "%s",
        "mode": "%s",
        "score": "%s"
      })", row[0], row[1], row[2]));
      content.push_back(rec);
    }
  }
  return return_json("", content);
}

crow::response RecordHandler::Post() {
  auto uid = this->get_current_user_id();
  auto score = this->get_argument("score");
  auto playtime = this->get_argument("time");
  auto mode = this->get_argument("mode");
  vector<json> content;

  mysqlpp::ScopedConnection conn(*pool);
  mysqlpp::Query query = conn->query(fmt::format(
          "insert into record(uid,score,time,mode) values({},{},'{}',{})", 
          escapeSQL(uid),escapeSQL(score),escapeSQL(playtime),escapeSQL(mode)));
  bool r = query.exec(); 
  if (r) { // insert success
    query = conn->query("select last_insert_id()"); //get new uid
    mysqlpp::StoreQueryResult res = query.store();
    if (res && res.num_rows()) {
      auto row = res[0];
      json rec = json::parse(fmt::sprintf(R"({
        "rid": "%s"
      })", row[0]));
      content.push_back(rec);
    }    
    return return_json("", content);
  }
  else return return_json("数据库异常错误"); // insert failed
}