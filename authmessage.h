#ifndef AUTHMESSAGE_H_INCLUDED
#define AUTHMESSAGE_H_INCLUDED

std:: string SHA512(std::string message);
std::string MAC(std::string message, std::string key);

#endif // AUTHMESSAGE_H_INCLUDED
