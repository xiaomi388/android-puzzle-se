#ifndef HANDLERS_H
#define HANDLERS_H

#include <type_traits>
#include "ConnectionPool.hpp"
#include "Exception.hpp"
#include "defines.hpp"

namespace PuzzleServer {

extern unique_ptr<ConnectionPool> pool;
extern unique_ptr<json> config;
extern crow::App<crow::CookieParser> app;

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
  char *get_argument(const string &param);

  //TODO
  void set_secure_cookie(const string &key, const string &value);
  string get_current_user_id();

 protected:
  BaseController(const crow::request &r);

 protected:
  const crow::request &req;
  crow::CookieParser::context &ctx;
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
  }
  return res;

}

}  // namespace PuzzleServer

#endif  // HANDLERS_H
