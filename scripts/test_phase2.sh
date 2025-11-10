#!/bin/bash

echo "========================================="
echo "Phase 2 Verification Script"
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

echo -e "${YELLOW}[1/7] Checking build directory...${NC}"
if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

cd build

echo -e "${YELLOW}[2/7] Configuring project...${NC}"
cmake -G Ninja ..
print_status $? "CMake configuration"

echo -e "${YELLOW}[3/7] Building project...${NC}"
ninja
print_status $? "Project build"

echo -e "${YELLOW}[4/7] Running DataModels tests...${NC}"
./test_datamodels
print_status $? "DataModels unit tests"

echo -e "${YELLOW}[5/7] Running GradeCalculator tests...${NC}"
./test_gradecalculator
print_status $? "GradeCalculator tests (4 scenarios)"

echo -e "${YELLOW}[6/7] Running FileSystem tests...${NC}"
./test_filesystem
print_status $? "FileSystem utilities tests"

echo -e "${YELLOW}[7/7] Testing demo program...${NC}"
./bin/demo_datamodels > /dev/null
print_status $? "Demo program execution"

echo ""
echo "========================================="
echo -e "${GREEN}🎉 PHASE 2 VERIFICATION COMPLETED SUCCESSFULLY!${NC}"
echo "========================================="
echo ""
echo "📊 Available executables:"
echo "   ./bin/analytics_app    - Main application"
echo "   ./bin/demo_datamodels  - Demonstration program"
echo "   ./test_datamodels      - Data models tests"
echo "   ./test_gradecalculator - Grade calculator tests"
echo "   ./test_filesystem      - File system tests"
echo ""
echo "🚀 All Phase 2 components are working correctly!"