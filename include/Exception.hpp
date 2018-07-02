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

class UnauthorizedException : public Exception {
 public:
  UnauthorizedException(const string &msg = "") : Exception(msg) {}
  virtual ~UnauthorizedException() {}
};

class MethodNotAllowException : public Exception {
 public:
  MethodNotAllowException(const string &msg = "") : Exception(msg) {}
  virtual ~MethodNotAllowException() {}
};

} // PuzzleServer

#endif /* EXCEPTION_H */