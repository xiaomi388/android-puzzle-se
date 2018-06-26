#ifndef BASE_H
#define BASE_H

#include "defines.hpp"

namespace PuzzleServer {

extern unique_ptr<ConnectionPool> pool;
extern unique_ptr<json> config;

class BaseController {
};

} // namespace PuzzleServer


#endif // BASE_H
