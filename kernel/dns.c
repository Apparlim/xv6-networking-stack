#include "dns.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct dns_cache_entry dns_cache[MAX_DNS_ENTRIES];
int dns_cache_count = 0;

int dns_lookup(const char* hostname, uint32_t* ip) {
    for (int i = 0; i < dns_cache_count; i++) {
        if (strcmp(dns_cache[i].hostname, hostname) == 0) {
            if (time(NULL) - dns_cache[i].timestamp < 3600) { // 1 hour cache
                *ip = dns_cache[i].ip;
                return 0;
            }
        }
    }
    return -1;
}

int dns_add_entry(const char* hostname, uint32_t ip) {
    if (dns_cache_count >= MAX_DNS_ENTRIES) {
        return -1;
    }

    strncpy(dns_cache[dns_cache_count].hostname, hostname, 255);
    dns_cache[dns_cache_count].hostname[255] = '\0';
    dns_cache[dns_cache_count].ip = ip;
    dns_cache[dns_cache_count].timestamp = time(NULL);
    dns_cache_count++;

    return 0;
}
