#ifndef EXCEPTION_H
#define EXCEPTION_H

namespace PuzzleServer {

class Exception : public std::exception {
 public:
  Exception(const string &msg = "") : m_what(msg) {}
  virtual ~Exception() {}
  virtual const char *what() const noexcept override {
    return m_what.c_str();
  }
 protected:
  string m_what;
};

class MissingArgumentException : public Exception {
 public:
  MissingArgumentException(const string &msg = "") : Exception(msg) {}
  virtual ~MissingArgumentException() {}
};

} // PuzzleServer

#endif /* EXCEPTION_H */