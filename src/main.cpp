#include "defines.hpp"
#include "routers.hpp"

using namespace PuzzleServer;

namespace PuzzleServer {
int main() {
    crow::SimpleApp app;
    initRoute(app);
    app.port(18080).multithreaded().run();
    return 0;
}
}  // namespace PuzzleServer

int main() { PuzzleServer::main(); }
