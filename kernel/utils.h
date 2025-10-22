#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

// Network byte order functions
uint16_t htons(uint16_t hostshort);
uint32_t htonl(uint32_t hostlong);
uint16_t ntohs(uint16_t netshort);
uint32_t ntohl(uint32_t netlong);

#endif // UTILS_H