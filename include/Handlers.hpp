#ifndef HANDLERS_H
#define HANDLERS_H

#include <type_traits>
#include "defines.hpp"
#include "ConnectionPool.hpp"

namespace PuzzleServer {

extern unique_ptr<ConnectionPool> pool;
extern unique_ptr<json> config;

class BaseController {
  public:
    static json return_json(const string &error = "", const vector<json> &content={}) {
      std::ostringstream os;
      json j;
      j["error"] = error;
      if (!content.empty()) j["content"] = content;
      os << j;
      return (os.str());
    }
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

} // namespace PuzzleServer


#endif // HANDLERS_H
