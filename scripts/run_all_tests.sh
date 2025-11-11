#!/bin/bash

echo "========================================"
echo "AnalyticsApp - Complete Test Suite"
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

echo -e "${YELLOW}[1/4] Running Phase 3 verification...${NC}"
./scripts/test_phase3.sh
print_status $? "Phase 3 verification"

echo -e "${YELLOW}[2/4] Running integration tests...${NC}"
./scripts/test_integration.sh
print_status $? "Integration tests"

echo -e "${YELLOW}[3/4] Running all unit tests with ctest...${NC}"
cd build
ctest --output-on-failure
print_status $? "All unit tests"

echo -e "${YELLOW}[4/4] Testing demo programs functionality...${NC}"
./bin/demo_directory_scanner . > /dev/null
print_status $? "Demo directory scanner"

./bin/demo_datamodels > /dev/null
print_status $? "Demo datamodels"

echo ""
echo "========================================"
echo -e "${GREEN}🎉 ALL TESTS PASSED SUCCESSFULLY!${NC}"
echo "========================================"
echo ""
echo "📋 Test Summary:"
echo "   ✅ Phase 3 verification"
echo "   ✅ Integration tests"
echo "   ✅ All unit tests (ctest)"
echo "   ✅ Demo programs"
echo ""
echo "🚀 Application is fully functional and ready for use!"