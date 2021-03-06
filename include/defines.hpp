#ifndef DEFINES_H
#define DEFINES_H

#define FMT_HEADER_ONLY 1

#include "utility/crow_all.h"
#include "utility/json.hpp"
#include "fmt/format.h"
#include "fmt/printf.h"

#include <iostream>
#include <string>
#include <vector>

namespace PuzzleServer {
using std::vector;
using std::string;
using std::shared_ptr;
using std::unique_ptr;
using std::cout;
using std::cerr;
using std::endl;
using nlohmann::json;
}

#endif /* DEFINES_H */
