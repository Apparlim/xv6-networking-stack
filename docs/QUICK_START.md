# Quick Start Guide

## Windows Users

### Option 1: Automated Build
```bash
# Double-click or run:
build.bat
```

### Option 2: Manual Build
```bash
# Compile all kernel modules
gcc -Wall -Wextra -std=c99 -O2 -g -c kernel/*.c

# Link and create executable
gcc -Wall -Wextra -std=c99 -O2 -g -I. test_networking.c kernel/*.o -o test_networking.exe

# Run tests
test_networking.exe
```

## Linux/Unix Users

### Option 1: Using Make
```bash
# Build and run tests
make test

# Or just build
make

# Run manually
./test_networking
```

### Option 2: Manual Build
```bash
# Compile all kernel modules
gcc -Wall -Wextra -std=c99 -O2 -g -c kernel/*.c

# Link and create executable
gcc -Wall -Wextra -std=c99 -O2 -g -I. test_networking.c kernel/*.o -o test_networking

# Run tests
./test_networking
```

## Expected Output

When successful, you should see:
```
=== xv6 Networking Stack Test Suite ===

Test 1: Network Stack Initialization... PASSED
Test 2: E1000 Driver Initialization... PASSED
Test 3: ARP Cache Operations... PASSED
Test 4: UDP Socket Management... PASSED
Test 5: DHCP Client Operations... PASSED
Test 6: DNS Resolution... PASSED
Test 7: PXE Boot Support... PASSED
Test 8: Performance Statistics... PASSED
Test 9: Packet Processing... PASSED
Test 10: Cleanup Procedures... PASSED

=== Test Results ===
Total Tests: 10
Passed: 10
Failed: 0
Success Rate: 100.00%

=== Performance Statistics ===
Uptime: 0 seconds
Packets sent: 0
Packets received: 0
Bytes sent: 0
Bytes received: 0
ARP successes: 0
DHCP successes: 0
Packet loss: 0.00%

All tests completed successfully!
```

## Troubleshooting

### Common Issues

1. **"gcc not found"**
   - Install GCC compiler
   - Windows: Install MinGW or use Visual Studio
   - Linux: `sudo apt install gcc` (Ubuntu/Debian)

2. **"Permission denied"**
   - Linux: `chmod +x build.sh`
   - Windows: Run as Administrator if needed

3. **"No such file or directory"**
   - Ensure you're in the project root directory
   - Check that all source files exist

### Getting Help

If you encounter issues:
1. Check that all source files are present
2. Verify GCC is installed and in PATH
3. Ensure you're in the correct directory
4. Try the manual build steps above
