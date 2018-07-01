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
  auto mode = this->get_argument("mode");

  // Just for debug, you can use get_current_user_id() to
  // get the current login user's id.
  if (this->get_current_user_id().empty()) {
    cout << "当前用户没有登录" << endl;
  } else {
    cout << this->get_current_user_id() << endl;
  }

  // Find user info from database.
  // If succeed, set a cookie to the current user.
  // This is a meaningless action, just in order to 
  // show how to connect to the database and set
  // cookie for user.
  mysqlpp::ScopedConnection conn(*pool);
  mysqlpp::Query query = conn->query(fmt::format(
      "select * from user where username = {}", escapeSQL(mode)));
  if (mysqlpp::StoreQueryResult res = query.store()) {
    for (auto &row : res) {
      json rec = json::parse(fmt::sprintf(R"({
        "uid": "%s",
        "username": "%s",
        "password": "%s"
      })", row[0], row[1], row[2]));
      content.push_back(rec);
      this->set_secure_cookie("uid", string(row[0]));
    }
  }
  return return_json("", content);
}

crow::response UserRecordHandler::Post() {
  return return_json("");
}