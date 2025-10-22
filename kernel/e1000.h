#ifndef E1000_H 
#define E1000_H 
#include <stdint.h> 
 
struct tx_descriptor { 
    uint64_t buffer_addr; 
    uint16_t length; 
    uint8_t cso; 
    uint8_t cmd; 
    uint8_t status; 
    uint8_t css; 
    uint16_t special; 
}; 
 
struct rx_descriptor { 
    uint64_t buffer_addr; 
    uint16_t length; 
    uint16_t checksum; 
    uint8_t status; 
    uint8_t errors; 
    uint16_t special; 
}; 
 
struct e1000_device { 
    uint32_t base_addr; 
    struct tx_descriptor* tx_descriptors; 
    struct rx_descriptor* rx_descriptors; 
    int tx_ring_size; 
    int rx_ring_size; 
    int tx_head; 
    int tx_tail; 
    int rx_head; 
    int rx_tail; 
}; 
 
extern struct e1000_device e1000_dev; 
int e1000_init(void); 
int e1000_send_packet(void* data, int len); 
int e1000_receive_packet(void* buffer, int max_len); 
void e1000_cleanup(void); 
 
#endif 
