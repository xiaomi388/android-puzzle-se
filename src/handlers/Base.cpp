#include "Handlers.hpp"

using namespace PuzzleServer;

json BaseController::return_json(const string &error,
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
  return "";
}