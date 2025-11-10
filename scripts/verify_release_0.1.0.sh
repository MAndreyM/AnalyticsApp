#!/bin/bash

echo "========================================="
echo "Release 0.1.0 Verification"
echo "========================================="

# Цвета для вывода
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

print_status() {
    if [ $1 -eq 0 ]; then
        echo -e "${GREEN}✅ $2${NC}"
    else
        echo -e "${RED}❌ $2${NC}"
        exit 1
    fi
}

echo -e "${YELLOW}[1/6] Cleaning build directory...${NC}"
rm -rf build
mkdir build
cd build

echo -e "${YELLOW}[2/6] Production configuration...${NC}"
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..
print_status $? "Production CMake configuration"

echo -e "${YELLOW}[3/6] Production build...${NC}"
ninja
print_status $? "Production build"

echo -e "${YELLOW}[4/6] Running unit tests...${NC}"
./test_datamodels
print_status $? "DataModels tests"
./test_gradecalculator
print_status $? "GradeCalculator tests"
./test_filesystem
print_status $? "FileSystem tests"

echo -e "${YELLOW}[5/6] Testing demo program format...${NC}"
DEMO_OUTPUT=$(./bin/demo_datamodels)

# Исправленная проверка формата - используем fgrep вместо grep с опциями
if echo "$DEMO_OUTPUT" | fgrep -q "------"; then
    echo -e "${GREEN}✅ Format check: PASSED (found separator lines)${NC}"
else
    echo -e "${RED}❌ Format check: FAILED (no separator lines found)${NC}"
    echo "Demo output:"
    echo "$DEMO_OUTPUT"
    exit 1
fi

# Дополнительная проверка на наличие данных
if echo "$DEMO_OUTPUT" | fgrep -q " <-> "; then
    echo -e "${GREEN}✅ Data format: PASSED (found data lines)${NC}"
else
    echo -e "${YELLOW}⚠️  Data format: No data found (might be empty results)${NC}"
fi

echo -e "${YELLOW}[6/6] Testing main application...${NC}"
./bin/analytics_app --help > /dev/null
print_status $? "Main application help"

echo ""
echo "========================================="
echo -e "${GREEN}🎉 RELEASE 0.1.0 VERIFICATION COMPLETED!${NC}"
echo "========================================="
echo ""
echo -e "${YELLOW}📊 Demo output preview:${NC}"
echo "$DEMO_OUTPUT" | head -20
echo ""
echo -e "${GREEN}🚀 Release 0.1.0 is ready for distribution!${NC}"