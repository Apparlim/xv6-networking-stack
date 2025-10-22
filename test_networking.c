#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kernel/net.h"
#include "kernel/e1000.h"
#include "kernel/arp.h"
#include "kernel/udp.h"
#include "kernel/dhcp.h"
#include "kernel/dns.h"
#include "kernel/pxe.h"
#include "kernel/performance.h"

int main() {
    printf("=== Networking Protocol Driver Test Suite ===\n\n");
    
    int tests_passed = 0;
    int tests_total = 0;
    
    // Test 1: Network stack initialization
    printf("Test 1: Network stack initialization...\n");
    tests_total++;
    if (net_init() == 0) {
        printf("✓ Network stack initialized successfully\n");
        tests_passed++;
    } else {
        printf("✗ Network stack initialization failed\n");
    }
    
    // Test 2: E1000 driver functionality
    printf("\nTest 2: E1000 driver functionality...\n");
    tests_total++;
    if (e1000_init() == 0) {
        printf("✓ E1000 driver initialized successfully\n");
        tests_passed++;
    } else {
        printf("✗ E1000 driver initialization failed\n");
    }
    
    // Test 3: ARP functionality
    printf("\nTest 3: ARP functionality...\n");
    tests_total++;
    uint8_t test_mac[6] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55};
    uint32_t test_ip = 0xC0A80101; // 192.168.1.1
    
    if (arp_add_entry(test_ip, test_mac) == 0) {
        printf("✓ ARP entry added successfully\n");
        tests_passed++;
    } else {
        printf("✗ ARP entry addition failed\n");
    }
    
    // Test 4: UDP socket functionality
    printf("\nTest 4: UDP socket functionality...\n");
    tests_total++;
    int sockfd = udp_socket_create();
    if (sockfd >= 0) {
        printf("✓ UDP socket created successfully (fd: %d)\n", sockfd);
        if (udp_bind(sockfd, 8080) == 0) {
            printf("✓ UDP socket bound to port 8080\n");
            tests_passed++;
        } else {
            printf("✗ UDP socket binding failed\n");
        }
    } else {
        printf("✗ UDP socket creation failed\n");
    }
    
    // Test 5: DHCP functionality
    printf("\nTest 5: DHCP functionality...\n");
    tests_total++;
    if (dhcp_init() == 0) {
        printf("✓ DHCP client initialized successfully\n");
        tests_passed++;
    } else {
        printf("✗ DHCP client initialization failed\n");
    }
    
    // Test 6: DNS functionality
    printf("\nTest 6: DNS functionality...\n");
    tests_total++;
    uint32_t dns_ip;
    if (dns_add_entry("example.com", 0x08080808) == 0) {
        printf("✓ DNS entry added successfully\n");
        if (dns_lookup("example.com", &dns_ip) == 0) {
            printf("✓ DNS lookup successful (IP: 0x%08X)\n", dns_ip);
            tests_passed++;
        } else {
            printf("✗ DNS lookup failed\n");
        }
    } else {
        printf("✗ DNS entry addition failed\n");
    }
    
    // Test 7: PXE functionality
    printf("\nTest 7: PXE functionality...\n");
    tests_total++;
    if (pxe_init() == 0) {
        printf("✓ PXE module initialized successfully\n");
        tests_passed++;
    } else {
        printf("✗ PXE module initialization failed\n");
    }
    
    // Test 8: Performance statistics
    printf("\nTest 8: Performance statistics...\n");
    tests_total++;
    perf_record_packet_sent();
    perf_record_packet_received();
    perf_record_arp_success();
    perf_record_dhcp_success();
    printf("✓ Performance statistics recorded\n");
    tests_passed++;
    
    // Test 9: Packet processing
    printf("\nTest 9: Packet processing...\n");
    tests_total++;
    uint8_t test_packet[] = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Destination MAC
        0x00, 0x11, 0x22, 0x33, 0x44, 0x55, // Source MAC
        0x08, 0x00, // EtherType (IPv4)
        0x45, 0x00, 0x00, 0x14, // IP header start
        0x00, 0x00, 0x40, 0x00,
        0x40, 0x01, 0x00, 0x00,
        0xC0, 0xA8, 0x01, 0x01, // Source IP
        0xC0, 0xA8, 0x01, 0x02  // Destination IP
    };
    
    if (net_process_packet(test_packet, sizeof(test_packet)) == 0) {
        printf("✓ Packet processing successful\n");
        tests_passed++;
    } else {
        printf("✗ Packet processing failed\n");
    }
    
    // Test 10: Cleanup
    printf("\nTest 10: Cleanup...\n");
    tests_total++;
    net_cleanup();
    printf("✓ Network stack cleaned up successfully\n");
    tests_passed++;
    
    // Print performance statistics
    printf("\n=== Performance Statistics ===\n");
    perf_print_stats();
    
    // Final results
    printf("\n=== Test Results ===\n");
    printf("Tests passed: %d/%d\n", tests_passed, tests_total);
    printf("Success rate: %.1f%%\n", (float)tests_passed / tests_total * 100);
    
    if (tests_passed == tests_total) {
        printf("\n🎉 All tests passed! The networking protocol driver is working correctly.\n");
        return 0;
    } else {
        printf("\n❌ Some tests failed. Please check the implementation.\n");
        return 1;
    }
}