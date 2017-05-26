#!/bin/sh

# Run a set of test regex search cases with tinygrep.

TEST_DIR="test/manual-testcases/"
TEST_PREFIX="testcase"
TEST_POSTFIX=".txt"
TEST_COUNT=16
APP_PATH="bin/tinygrep"

echo "-- Running $TEST_COUNT testcases with tinygrep."
echo "-- Most output lines should have leading zig zag pattern or + signs."
echo "-- Sample good output:"
echo "  \    Nice"
echo "   \   Output"
echo "    \  Pattern"
echo "     \ Looks"
echo "      \Something"
echo "      /Like"
echo "     / This"
echo "    /  Beauty."

echo "-- Sample bad output:"
echo " /\/\/ This"
echo "  \    Output"
echo " /\/\/ Is"
echo " /\/\/ Plain"
echo " /\/\/ Wrong."

echo "-- Running actual tests..."
for TEST_NUMBER in $(seq 1 $TEST_COUNT)
do
  echo "-- TEST #$TEST_NUMBER --"
  TEST_PATH=$TEST_DIR$TEST_PREFIX$TEST_NUMBER$TEST_POSTFIX
  echo "-- $TEST_PATH"
  tail -n +3 $TEST_PATH | $APP_PATH "$(head -2 $TEST_PATH | tail -1)"
done

