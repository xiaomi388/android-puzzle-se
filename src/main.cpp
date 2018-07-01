#include "ConnectionPool.hpp"
#include "defines.hpp"
#include "fmt/format.h"
#include "Routers.hpp"
// #include "Configure"

using namespace PuzzleServer;

namespace PuzzleServer {

unique_ptr<ConnectionPool> pool = nullptr;
unique_ptr<json> config = nullptr;
crow::App<crow::CookieParser> app;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("usage: %s [ production | development | test ]", argv[0]);
    return 1;
  }

  // initial configure
  config = std::make_unique<json>();
  std::ifstream i(fmt::format("./config/{0}.json", argv[1]));
  i >> (*config);

  cout << *config << endl;

  // initial connection pool
  pool = std::make_unique<ConnectionPool>(
      (*config)["mysql"]["database"], (*config)["mysql"]["host"],
      (*config)["mysql"]["port"], (*config)["mysql"]["user"],
      (*config)["mysql"]["passwd"], (*config)["mysql"]["charset"]);

  initRoute(app);
  app.port((*config)["runtime"]["port"]).multithreaded().run();
  return 0;
}

}  // namespace PuzzleServer

int main(int argc, char* argv[]) {
  PuzzleServer::main(argc, argv);
}
