#include "SessionParser.hpp"
#include <ctime>

using namespace PuzzleServer;
using namespace crow;

std::unordered_map<std::string, time_t> SessionParser::context::sessions;

std::string SessionParser::context::get_cookie(const std::string& key) const {
  auto cookie = jar.find(key);
  if (cookie != jar.end()) {
    auto session = sessions.find(cookie->second);
    if (session != sessions.end() && session->second > std::time(0)) {
      return cookie->second;
    }
  }
  return {};
}

void SessionParser::context::set_cookie(const std::string& key,
                                        const std::string& value,
                                        int expired_time) {
  cookies_to_add.emplace(key, value);
  // add session
  sessions[value] = std::time(0) + expired_time;
}

void SessionParser::before_handle(request& req, response& res, context& ctx) {
  int count = req.headers.count("Cookie");
  if (!count) return;
  if (count > 1) {
    res.code = 400;
    res.end();
    return;
  }
  std::string cookies = req.get_header_value("Cookie");
  size_t pos = 0;
  while (pos < cookies.size()) {
    size_t pos_equal = cookies.find('=', pos);
    if (pos_equal == cookies.npos) break;
    std::string name = cookies.substr(pos, pos_equal - pos);
    boost::trim(name);
    pos = pos_equal + 1;
    while (pos < cookies.size() && cookies[pos] == ' ') pos++;
    if (pos == cookies.size()) break;

    size_t pos_semicolon = cookies.find(';', pos);
    std::string value = cookies.substr(pos, pos_semicolon - pos);

    boost::trim(value);
    if (value[0] == '"' && value[value.size() - 1] == '"') {
      value = value.substr(1, value.size() - 2);
    }

    ctx.jar.emplace(std::move(name), std::move(value));

    pos = pos_semicolon;
    if (pos == cookies.npos) break;
    pos++;
    while (pos < cookies.size() && cookies[pos] == ' ') pos++;
  }
}

void SessionParser::after_handle(request& /*req*/, response& res,
                                 context& ctx) {
  for (auto& cookie : ctx.cookies_to_add) {
    if (cookie.second.empty())
      res.add_header("Set-Cookie", cookie.first + "=\"\"");
    else
      res.add_header("Set-Cookie", cookie.first + "=" + cookie.second);
  }
}

void SessionParser::context::remove_session(const std::string& session) {
  auto it = sessions.find(session);
  if (it != sessions.end()) {
    sessions.erase(it);
  }
}