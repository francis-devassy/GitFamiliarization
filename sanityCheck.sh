#!/bin/bash

# sanityCheck.sh
# Purpose: Pull latest code, build, run static analysis, check memory leaks,
# capture build warnings, and generate a consolidated report.

REPORT="report.txt"
TARGET="release/main_linux"

echo "===== Sanity Check Report =====" > $REPORT
echo "Generated on: $(date)" >> $REPORT
echo "" >> $REPORT

# 1. Pull latest code
echo ">>> Pulling latest code..." | tee -a $REPORT
git pull >> $REPORT 2>&1
echo "" >> $REPORT

# 2. Clean and build
echo ">>> Building project..." | tee -a $REPORT
make clean >> $REPORT 2>&1
make linux >> $REPORT 2>&1
BUILD_STATUS=$?
if [ $BUILD_STATUS -ne 0 ]; then
    echo "Build failed. See details above." | tee -a $REPORT
    exit 1
else
    echo "Build succeeded." | tee -a $REPORT
fi
echo "" >> $REPORT

# 3. Static analysis (cppcheck)
echo ">>> Running static analysis (cppcheck)..." | tee -a $REPORT
cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem \
    -I ./appTimer \
    -I . \
    . 2>> $REPORT
echo "" >> $REPORT

# 4. Build warnings (captured during make)
echo ">>> Build warnings (from make)..." | tee -a $REPORT
make linux 2>&1 | grep "warning" >> $REPORT
echo "" >> $REPORT

# 5. Memory leak check (valgrind with timeout)
if [ -f "$TARGET" ]; then
    echo ">>> Running memory leak check (valgrind, 5s timeout)..." | tee -a $REPORT
    timeout 5 valgrind --leak-check=full --error-exitcode=1 $TARGET >> $REPORT 2>&1
    VALGRIND_STATUS=$?
    if [ $VALGRIND_STATUS -eq 0 ]; then
        echo "No memory leaks detected." | tee -a $REPORT
    elif [ $VALGRIND_STATUS -eq 124 ]; then
        echo "Valgrind timed out (program runs indefinitely)." | tee -a $REPORT
    else
        echo "Memory leaks detected. See valgrind output above." | tee -a $REPORT
    fi
else
    echo "Target binary not found: $TARGET" | tee -a $REPORT
fi
echo "" >> $REPORT

echo "===== End of Report =====" >> $REPORT