#include "ConnectionPool.hpp"

using namespace PuzzleServer;

ConnectionPool::ConnectionPool(const string& dbname, const string& serverip,
                               int port, const string& user,
                               const string& passwd, const string& charset)
    : m_dbname(dbname),
      m_server_ip(serverip),
      m_user(user),
      m_passwd(passwd),
      m_charset(charset),
      m_port(port) {
  m_max_idle_time = 300;
}

ConnectionPool::~ConnectionPool() {
  clear();
}

mysqlpp::Connection* ConnectionPool::grab() {
  return mysqlpp::ConnectionPool::grab();
}

const string& ConnectionPool::getDBName() const {
  return m_dbname;
}
const string& ConnectionPool::getServerIP() const {
  return m_server_ip;
}
const string& ConnectionPool::getUser() const {
  return m_user;
}
const string& ConnectionPool::getPassword() const {
  return m_passwd;
}
const string& ConnectionPool::getCharset() const {
  return m_charset;
}
int ConnectionPool::getPort() const {
  return m_port;
}

void ConnectionPool::setMaxIdleTIme(int max_idle) {
  m_max_idle_time = max_idle;
}

void ConnectionPool::release(const mysqlpp::Connection* pc) {
  mysqlpp::ConnectionPool::release(pc);
}

mysqlpp::Connection* ConnectionPool::create() {
  mysqlpp::Connection* conn = new mysqlpp::Connection(true);
  mysqlpp::SetCharsetNameOption* pOpt =
      new mysqlpp::SetCharsetNameOption(m_charset.c_str());
  conn->set_option( pOpt );
  conn->connect(m_dbname.empty() ? 0 : m_dbname.c_str(),
    m_server_ip.empty() ? 0 : m_server_ip.c_str(),
    m_user.empty() ? 0 : m_user.c_str(),
    m_passwd.empty() ? 0 : m_passwd.c_str(),
    m_port);
  return conn;
}

void ConnectionPool::destroy(mysqlpp::Connection* cp) { delete cp; }
unsigned int ConnectionPool::max_idle_time() { return m_max_idle_time; }

