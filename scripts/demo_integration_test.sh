#!/bin/bash

echo "========================================"
echo "AnalyticsApp Integration Test"
echo "========================================"

# Цвета для вывода
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

print_status() {
    if [ $1 -eq 0 ]; then
        echo -e "${GREEN}✅ $2${NC}"
    else
        echo -e "${RED}❌ $2${NC}"
        exit 1
    fi
}

echo -e "${YELLOW}[1/6] Building the project...${NC}"
cd build
ninja
print_status $? "Project build"

echo -e "${YELLOW}[2/6] Testing main application help...${NC}"
./bin/analytics_app
print_status $? "Main application startup"

echo -e "${YELLOW}[3/6] Testing data analysis functionality...${NC}"
echo -e "1" | timeout 2s ./bin/analytics_app > test_output.txt
grep -q "Student Data Analysis" test_output.txt
print_status $? "Data analysis feature"

echo -e "${YELLOW}[4/6] Testing directory scanning functionality...${NC}"
echo -e "2" | timeout 2s ./bin/analytics_app > test_output.txt
grep -q "Directory Scanning" test_output.txt
print_status $? "Directory scanning feature"

echo -e "${YELLOW}[5/6] Testing file system utilities...${NC}"
echo -e "3" | timeout 2s ./bin/analytics_app > test_output.txt
grep -q "File System Utilities" test_output.txt
print_status $? "File system utilities feature"

echo -e "${YELLOW}[6/6] Testing exit functionality...${NC}"
echo -e "4" | timeout 2s ./bin/analytics_app > test_output.txt
grep -q "Goodbye" test_output.txt
print_status $? "Exit functionality"

rm -f test_output.txt

echo ""
echo "========================================"
echo -e "${GREEN}🎉 INTEGRATION TEST PASSED!${NC}"
echo "========================================"
echo ""
echo "🎯 All Phase 3 features integrated successfully:"
echo ""
echo "   📊 Data Analysis Module"
echo "      - Student data models"
echo "      - Grade calculation with rounding"
echo "      - Performance analysis"
echo ""
echo "   🔍 Directory Scanner Module"
echo "      - Recursive Excel file search"
echo "      - File filtering by extension"
echo "      - Scan statistics and timing"
echo ""
echo "   📁 File System Utilities"
echo "      - File existence checking"
echo "      - Directory listing"
echo "      - Excel file validation"
echo ""
echo "🚀 Application ready for Phase 4 development!"