#ifndef TEST_H
#define TEST_H

#include <mysql++.h>
#include "defines.hpp"
#include "handlers/Base.hpp"
#include "ConnectionPool.hpp"

using namespace PuzzleServer;

namespace PuzzleServer {

class TestHandler : public BaseController {
 public:
  static auto get(const crow::request& req);
  static auto post(const crow::request& req);
};

auto TestHandler::get(const crow::request& req) {
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

}  // namespace PuzzleServer

#endif /* TEST_H */