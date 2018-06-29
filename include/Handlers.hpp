#ifndef HANDLERS_H
#define HANDLERS_H

#include <type_traits>
#include "ConnectionPool.hpp"
#include "defines.hpp"

namespace PuzzleServer {

extern unique_ptr<ConnectionPool> pool;
extern unique_ptr<json> config;

class BaseController {
 public:
  static json return_json(const string& error = "",
                          const vector<json>& content = {});

  static string escapeSQL(const string& param);
};

class TestHandler : public BaseController {
 public:
  static string Get(const crow::request& req);
  static string Post(const crow::request& req);
};

class UserHandler : public BaseController {
 public:
  static string Get(const crow::request& req);
  static string Post(const crow::request& req);
};

}  // namespace PuzzleServer

#endif  // HANDLERS_H
