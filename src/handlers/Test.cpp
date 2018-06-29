#include <mysql++.h>
#include "defines.hpp"
#include "Handlers.hpp"
#include "ConnectionPool.hpp"

using namespace PuzzleServer;

string TestHandler::Get(const crow::request& req) {
  std::ostringstream os;
  mysqlpp::ScopedConnection conn(*pool);

  mysqlpp::Query query = conn->query("select 1");
  if (mysqlpp::StoreQueryResult res = query.store()) {
    os << "We have:" << endl;
    mysqlpp::StoreQueryResult::const_iterator it;
    for (auto& row : res) {
      os << '\t' << row[0] << endl;
    }
  }
  return os.str();
}