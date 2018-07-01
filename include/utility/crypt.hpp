#ifndef CRYPT_H
#define CRYPT_H

#include <openssl/aes.h>
#include <string>

namespace PuzzleServer {

int char2int(char input)
{
  if(input >= '0' && input <= '9')
    return input - '0';
  if(input >= 'A' && input <= 'F')
    return input - 'A' + 10;
  if(input >= 'a' && input <= 'f')
    return input - 'a' + 10;
  throw std::invalid_argument("Invalid input string");
}

string hex2bin(const char* src) {
  string ret;
  while(*src && src[1]) {
    ret += char2int(*src)*16 + char2int(src[1]);
    src += 2;
  }
  return ret;
}

std::string EncodeAES(const std::string& password, const std::string& data) {
  AES_KEY aes_key;
  if (AES_set_encrypt_key((const unsigned char*)password.c_str(),
                          password.length() * 8, &aes_key) < 0) {
    assert(false);
    return "";
  }
  std::string strRet;
  std::string data_bak = data;
  unsigned int data_length = data_bak.length();
  int padding = 0;
  if (data_bak.length() % AES_BLOCK_SIZE > 0) {
    padding = AES_BLOCK_SIZE - data_bak.length() % AES_BLOCK_SIZE;
  }
  data_length += padding;
  while (padding > 0) {
    data_bak += '\0';
    padding--;
  }
  for (unsigned int i = 0; i < data_length / AES_BLOCK_SIZE; i++) {
    std::string str16 = data_bak.substr(i * AES_BLOCK_SIZE, AES_BLOCK_SIZE);
    unsigned char out[AES_BLOCK_SIZE];
    ::memset(out, 0, AES_BLOCK_SIZE);
    AES_encrypt((const unsigned char*)str16.c_str(), out, &aes_key);
    // Encode into hex
    for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
        strRet += fmt::sprintf("%02x", *((char*)out + i));
    }
  }
  return strRet;
}

std::string DecodeAES(const std::string& strPassword,
                      const std::string& strDataHex) {

  // Decode into raw code
  string strData = hex2bin(strDataHex.c_str());
  AES_KEY aes_key;
  if (AES_set_decrypt_key((const unsigned char*)strPassword.c_str(),
                          strPassword.length() * 8, &aes_key) < 0) {
    assert(false);
    return "";
  }
  std::string strRet;
  for (unsigned int i = 0; i < strData.length() / AES_BLOCK_SIZE; i++) {
    std::string str16 = strData.substr(i * AES_BLOCK_SIZE, AES_BLOCK_SIZE);
    unsigned char out[AES_BLOCK_SIZE];
    ::memset(out, 0, AES_BLOCK_SIZE);
    AES_decrypt((const unsigned char*)str16.c_str(), out, &aes_key);
    strRet += std::string((const char*)out, AES_BLOCK_SIZE);
  }
  return strRet;
}

}  // namespace PuzzleServer

#endif /* CRYPT_H */