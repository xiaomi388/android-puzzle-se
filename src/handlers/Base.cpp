#include "Handlers.hpp"

using namespace PuzzleServer;

string BaseController::return_json(const string &error,
                                   const vector<json> &content) {
  std::ostringstream os;
  json j;
  j["error"] = error;
  if (!content.empty()) j["content"] = content;
  os << j;
  return (os.str());
}

string BaseController::escapeSQL(const string &param) {
  // TODO: avoid sql injection
  return param;
}

BaseController::BaseController(const crow::request &r)
    : req(r), ctx(app.get_context<crow::CookieParser>(r)) {}

crow::response BaseController::handle() {
  switch (req.method) {
    case crow::HTTPMethod::GET:
      return this->Get();
    case crow::HTTPMethod::POST:
      return this->Post();
    case crow::HTTPMethod::PUT:
      return this->Put();
    case crow::HTTPMethod::DELETE:
      return this->Delete();
    default:
      break;
  }
  return this->Get();
}

crow::response BaseController::Get() {
  return crow::response(400);
}

crow::response BaseController::Post() {
  return crow::response(400);
}

crow::response BaseController::Put() {
  return crow::response(400);
}

crow::response BaseController::Delete() {
  return crow::response(400);
}

char *BaseController::get_argument(const string &param) {
  char *arg = this->req.url_params.get(param);
  if (arg == nullptr)
    throw MissingArgumentException(fmt::format("Missing argument {}", param));
  return arg;
}

void BaseController::set_secure_cookie(const string &key, const string &value) {
  // FIXME: use cookie-secret to encrypt the value
  ctx.set_cookie(key, value);
}

string BaseController::get_current_user_id() {
  string cookie = ctx.get_cookie("uid");
  if (cookie.empty()) {
    return cookie;
  }
  // FIXME: use cookie-secret to decrypt the user id
  return cookie;
}