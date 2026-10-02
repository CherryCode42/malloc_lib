#!/bin/bash

set -e

echo "=== Compiling tests ==="

for file in *.c; do
    name=$(basename "$file" .c)

    echo "Compiling $name..."

    gcc "$file" \
        -I../inc \
        -L.. \
        -lft_malloc \
        -Wl,-rpath,'$ORIGIN/..' \
        -o "$name"
done

echo
echo "=== Running tests ==="

        echo "================================"
        echo "Running my test"
        echo "================================"
        ./test


for test in test0 test1 test2 test3 test4 test5; do
    if [ -x "./$test" ]; then
        echo
        echo "================================"
        echo "Running school $test"
        echo "================================"

        "./$test"

        status=$?

        if [ $status -ne 0 ]; then
            echo
            echo "❌ $test FAILED with exit code $status"
            exit $status
        fi

        echo "✅ $test PASSED"
    fi
done

        echo "================================"
        echo "Running Konstantins test"
        echo "================================"
        ./test_002
