#include <mysql++.h>
#include "ConnectionPool.hpp"
#include "Exception.hpp"
#include "Handlers.hpp"
#include "defines.hpp"
#include "fmt/format.h"
#include "fmt/printf.h"

using namespace PuzzleServer;

UserInfoHandler::UserInfoHandler(const crow::request &r) : BaseController(r) {}

crow::response UserInfoHandler::Get() {
  vector<json> content;
  auto uid = this->get_current_user_id();
  string sql,sql1,sql2,sql3;
  sql = fmt::format(
    "select username from user where uid = {}", escapeSQL(uid)
	);	
  sql1 = fmt::format(
    "SELECT COUNT(DISTINCT uid) from record where mode = 3 AND score <= (SELECT MIN(score) from record where uid = {} AND mode = 3)", escapeSQL(uid)
	);
  sql2 = fmt::format(
    "SELECT COUNT(DISTINCT uid) from record where mode = 4 AND score <= (SELECT MIN(score) from record where uid = {} AND mode = 4)", escapeSQL(uid)
	);
  sql3 = fmt::format(
    "SELECT COUNT(DISTINCT uid) from record where mode = 5 AND score <= (SELECT MIN(score) from record where uid = {} AND mode = 5)", escapeSQL(uid)
	);
  mysqlpp::ScopedConnection conn(*pool);
  mysqlpp::Query query = conn->query(sql);
  mysqlpp::Query query1 = conn->query(sql1);
  mysqlpp::Query query2 = conn->query(sql2);
  mysqlpp::Query query3 = conn->query(sql3);
  mysqlpp::StoreQueryResult res = query.store();
  mysqlpp::StoreQueryResult res1 = query1.store();
  mysqlpp::StoreQueryResult res2 = query2.store();
  mysqlpp::StoreQueryResult res3 = query3.store();

  auto &row = res[0];
  auto &row1 = res1[0];
  auto &row2 = res2[0];
  auto &row3 = res3[0];
  int a = atoi(row1[0].c_str());
  int b = atoi(row2[0].c_str());
  int c = atoi(row3[0].c_str());
  if(a==0){
    if(b!=0)a = b;
    if(c!=0)a = c;
  }
  if(a!=0){
    if(b!=0)a = a>b?b:a;
    if(c!=0)a = a>c?c:a;
  }
  json rec = json::parse(fmt::sprintf(R"({
         "username": "%s",
         "rank":"%d"
  })", row[0],a));
  content.push_back(rec);

  return return_json("", content);
}
crow::response UserInfoHandler::Post() {
  return return_json("");
}