#ifndef HANDLERS_H
#define HANDLERS_H

#include <type_traits>
#include "ConnectionPool.hpp"
#include "Exception.hpp"
#include "defines.hpp"
#include "utility/QueryParser.hpp"
#include "SessionParser.hpp"

namespace PuzzleServer {

extern unique_ptr<ConnectionPool> pool;
extern unique_ptr<json> config;
extern crow::App<SessionParser> app;

class BaseController {
 public:
  template <typename Handler>
  static crow::response proxy(const crow::request &req);

  virtual crow::response Get();
  virtual crow::response Post();
  virtual crow::response Put();
  virtual crow::response Delete();
  crow::response handle();

 protected:
  string return_json(const string &error = "",
                     const vector<json> &content = {});
  string escapeSQL(const string &param);
  string get_argument(const string &param,
                      const string &def = "MISSINGARGUMENT");

  // TODO
  void set_secure_cookie(const string &key, const string &value);
  string get_current_user_id();

 protected:
  BaseController(const crow::request &r);

 protected:
  const crow::request &req;
  SessionParser::context &ctx;
  shared_ptr<QueryParser> query_params = nullptr;
};

class UserHandler : public BaseController {
 public:
  UserHandler(const crow::request &r);
  crow::response Get();
  crow::response Post();
};

class RecordHandler : public BaseController {
 public:
  RecordHandler(const crow::request &r);
  crow::response Get();
  crow::response Post();
};

class UserRecordHandler : public BaseController {
 public:
  UserRecordHandler(const crow::request &r);
  crow::response Get();
  crow::response Post();
};
class UserInfoHandler : public BaseController {
 public:
  UserInfoHandler(const crow::request &r);
  crow::response Get();
  crow::response Post();
};

class PhotoHandler : public BaseController {
 public:
  PhotoHandler(const crow::request &r);
  crow::response Get();
  crow::response Post();
};

/* definition */

template <typename Handler>
crow::response BaseController::proxy(const crow::request &req) {
  crow::response res;
  Handler handler(req);
  try {
    return handler.handle();
  } catch (MissingArgumentException &e) {
    res.code = 400;
    res.body = e.what();
  } catch (UnauthorizedException &e) {
    res.code = 403;
    res.body = e.what();
  } catch (std::exception &e) {
    res.code = 500;
    res.body = fmt::format("500 Interval Error, reason: {}", e.what());
  }
  return res;
}

}  // namespace PuzzleServer

#endif  // HANDLERS_H
