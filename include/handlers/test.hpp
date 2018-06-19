#ifndef TEST_H
#define TEST_H

#include "handlers/base.hpp"
#include "defines.hpp"

using namespace PuzzleServer;

namespace PuzzleServer {

class TestHandler : public BaseController {
public:
    static auto get(const crow::request& req);
    static auto post(const crow::request& req);
};

auto TestHandler::get(const crow::request& req) {
    std::ostringstream os;
    os << "Hello World" << (req.url_params.get("uid") ?: "Null");
    return os.str();

}

} // namespace PuzzleServer

#endif /* TEST_H */