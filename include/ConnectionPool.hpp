#ifndef CONNECTION_POLL_H
#define CONNECTION_POLL_H

#include <mysql++.h>
#include <string>
#include "defines.hpp"

namespace PuzzleServer {

class ConnectionPool : public mysqlpp::ConnectionPool {
 public:
  virtual ~ConnectionPool();
  ConnectionPool(const string& dbname, const string& serverip, int port,
                 const string& user, const string& passwd,
                 const string& charset);
  const string& getDBName() const;
  const string& getServerIP() const;
  const string& getUser() const;
  const string& getPassword() const;
  const string& getCharset() const;
  int getPort() const;

  void setMaxIdleTIme(int max_idle);
  virtual mysqlpp::Connection* grab();
  virtual void release(const mysqlpp::Connection* pc);

 protected:
  virtual mysqlpp::Connection* create();
  virtual void destroy(mysqlpp::Connection* cp);
  virtual unsigned int max_idle_time();

 private:
  string m_dbname;
  string m_server_ip;
  string m_user;
  string m_passwd;
  string m_charset;
  int m_port;
  int m_max_idle_time;
};

}  // namespace PuzzleServer

#endif /* CONNECTION_POOL_H */