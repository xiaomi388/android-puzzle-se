#ifndef SESSION_PARSER
#define SESSION_PARSER

#include "defines.hpp"

namespace PuzzleServer {

struct SessionParser {
  struct context {
    std::unordered_map<std::string, std::string> jar;
    std::unordered_map<std::string, std::string> cookies_to_add;

    // 根据value反查该cookie的过期时间，从而实现session的机制
    static std::unordered_map<std::string, time_t> sessions;

    std::string get_cookie(const std::string& key) const;

    void set_cookie(const std::string& key, const std::string& value,
                    const int expired_time = 3600*24);
  };

  void before_handle(crow::request& req, crow::response& res, context& ctx);

  void after_handle(crow::request& /*req*/, crow::response& res, context& ctx);
};

}  // namespace PuzzleServer

#endif /* SESSION_PARSER_H */