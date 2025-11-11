#!/bin/bash

echo "========================================="
echo "Phase 3 Verification Script"
echo "========================================="

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

echo -e "${YELLOW}[1/8] Checking build directory...${NC}"
if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

cd build

echo -e "${YELLOW}[2/8] Configuring project...${NC}"
cmake -G Ninja ..
print_status $? "CMake configuration"

echo -e "${YELLOW}[3/8] Building project...${NC}"
ninja
print_status $? "Project build"

echo -e "${YELLOW}[4/8] Running DataModels tests...${NC}"
./test_datamodels
print_status $? "DataModels unit tests"

echo -e "${YELLOW}[5/8] Running GradeCalculator tests...${NC}"
./test_gradecalculator
print_status $? "GradeCalculator tests"

echo -e "${YELLOW}[6/8] Running FileSystem tests...${NC}"
./test_filesystem
print_status $? "FileSystem utilities tests"

echo -e "${YELLOW}[7/8] Running DirectoryScanner tests...${NC}"
./test_directory_scanner
print_status $? "DirectoryScanner comprehensive tests"

echo -e "${YELLOW}[8/8] Testing demo programs...${NC}"
./bin/demo_datamodels > /dev/null
print_status $? "Demo datamodels execution"

./bin/demo_directory_scanner --help > /dev/null
print_status $? "Demo directory scanner execution"

echo ""
echo "========================================="
echo -e "${GREEN}🎉 PHASE 3 VERIFICATION COMPLETED SUCCESSFULLY!${NC}"
echo "========================================="
echo ""
echo "📊 Available executables:"
echo "   ./bin/analytics_app         - Main application"
echo "   ./bin/demo_datamodels       - Data models demonstration"
echo "   ./bin/demo_directory_scanner - Directory scanner demonstration"
echo ""
echo "🧪 Test executables:"
echo "   ./test_datamodels          - Data models tests"
echo "   ./test_gradecalculator     - Grade calculator tests"
echo "   ./test_filesystem          - File system tests"
echo "   ./test_directory_scanner   - Directory scanner tests"
echo ""
echo "🚀 All Phase 3 components are working correctly!"