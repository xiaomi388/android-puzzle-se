#ifndef QUERY_PARSER_H
#define QUERY_PARSER_H

namespace PuzzleServer {
// QueryParser an HTTP query string into a map.
// Based on https://github.com/ipkn/crow/issues/170
class QueryParser {
public:
  std::map<std::string, std::string> jar;

public:
  QueryParser(std::string s) { jar = parse(s); }

  // Returns the value for a given key. If the key does not exist
  // an empty string is returned.
  std::string get(const std::string key) {
    try {
      return jar.at(key);
    } catch (const std::out_of_range &o) {
      return "";
    }
  }

  // Returns the value for a given key. If the key does not exist,
  // the given default value is returned.
  std::string get(const std::string key, const std::string def) {
    try {
      return jar.at(key);
    } catch (const std::out_of_range &o) {
      return def;
    }
  }

  // Returns the list of all parsed keys.
  std::vector<std::string> keys() {
    std::vector<std::string> ks;
    for (auto const &i : jar) {
      ks.push_back(i.first);
    }

    return ks;
  }

private:
  // Splits a string given a character delimiter.
  void split(const std::string &s, char delim,
             std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
      elems.push_back(item);
    }
  }

  // "Unescapes" an HTTP urlencoded value. This should be applied
  // on values after query parsing.
  void urlDecode(const std::string &in, std::string &out) {
    out.clear();
    out.reserve(in.size());
    for (std::size_t i = 0; i < in.size(); ++i) {
      if (in[i] == '%') {
        if (i + 3 <= in.size()) {
          int value = 0;
          std::istringstream is(in.substr(i + 1, 2));

          if (is >> std::hex >> value) {
            out += static_cast<char>(value);
            i += 2;
          } else {
            return;
          }
        } else {
          return;
        }
      } else if (in[i] == '+') {
        out += ' ';
      } else {
        out += in[i];
      }
    }
  }

  // Parses an HTTP query string.
  std::map<std::string, std::string> parse(const std::string &req_body) {
    std::map<std::string, std::string> body;
    std::vector<std::string> vec;
    split(req_body, '&', vec);

    uint pos;
    for (uint i = 0; i < vec.size(); i++) {
      pos = vec[i].find("=");

      if (pos != std::string::npos) {
        urlDecode(vec[i].substr(pos + 1), body[vec[i].substr(0, pos)]);
      } else {
        break;
      }
    }

    return body;
  }
};
  // Usage.
//   QueryParser post = QueryParser("name=Bob&sign=A%26B&number=1");

//   auto keys = post.keys();
//   for (uint i = 0; i < keys.size(); i++) {
//     std::cout << keys[i] << " = " << post.get(keys[i]) << std::endl;
//   }
}

#endif /* QUERY_PARSER_H */