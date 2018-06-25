#include "ConnectionPool.hpp"
#include "defines.hpp"
#include "routers.hpp"
// #include "Configure"

using namespace PuzzleServer;

namespace PuzzleServer {

shared_ptr<ConnectionPool> pool = nullptr;

int main() {
  // initial configure

  // initial connection pool
  pool = std::make_shared<ConnectionPool>(
      "puzzle", "xiaomi388.cn", 3306, "android", "061515690e0c0a51", "utf8");

  crow::SimpleApp app;
  initRoute(app);
  app.port(18080).multithreaded().run();
  return 0;
}

}  // namespace PuzzleServer

int main() {
  PuzzleServer::main();
}
