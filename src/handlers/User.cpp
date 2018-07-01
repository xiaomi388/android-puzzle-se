
#include <mysql++.h>
#include "ConnectionPool.hpp"
#include "Exception.hpp"
#include "Handlers.hpp"
#include "defines.hpp"
#include "fmt/format.h"
#include "fmt/printf.h"

using namespace PuzzleServer;

UserHandler::UserHandler(const crow::request &r) : BaseController(r) {}

crow::response UserHandler::Get() {
  // This is for test, and a template, please don't edit it.
  // This interface is to get user info by username.
  vector<json> content;
  auto username = this->get_argument("username");

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
      "select * from user where username = '{}'", escapeSQL(username)));
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

crow::response UserHandler::Post() {
  // TODO: user register and login
  auto username = this->get_argument("username");
  auto password = this->get_argument("passwd");
  auto action = this->get_argument("action");

  mysqlpp::ScopedConnection conn(*pool);

  if(action == "login") {
    mysqlpp::Query query = conn->query(fmt::format(
        "select * from user where username = '{}'", escapeSQL(username)));
    mysqlpp::StoreQueryResult res = query.store();
    if (res && res.num_rows()) {
      auto row = res[0];
      if(string(row[2]) == password) { // login success
        this->set_secure_cookie("uid", string(row[0]));
        return return_json("");
      }
      else return return_json("密码错误");
    }
    else return return_json("用户名不存在");
  }
  else if(action == "register") {
    mysqlpp::Query query = conn->query(fmt::format(
        "select * from user where username = '{}'", escapeSQL(username)));
    mysqlpp::StoreQueryResult res = query.store();
    if (res && res.num_rows()) {
      return return_json("用户名已存在");
    }
    else { // username usable
      query = conn->query(fmt::format(
          "insert into user(username, password) values('{}', '{}')", 
          escapeSQL(username), escapeSQL(password)));
      bool r = query.exec();    
      if (r) { // register success
        query = conn->query("select last_insert_id()"); //get new uid
        res = query.store();
        if (res && res.num_rows()) {
          auto row = res[0];
          this->set_secure_cookie("uid", string(row[0]));
        }    
        return return_json("");
      }
      else return return_json("数据库异常错误"); // insert failed
    }
  }
}
