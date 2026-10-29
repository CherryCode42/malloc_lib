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

        if [ -x "./test" ]; then
        echo "================================"
        echo "Running my test"
        echo "================================"
        LD_LIBRARY_PATH=.. ./test
		fi

        if [ -x "./test_realloc" ]; then
        echo "================================"
        echo "Running my test for realloc"
        echo "================================"
        LD_LIBRARY_PATH=.. ./test_realloc
		fi

        if [ -x "./test_threads" ]; then
        echo
        echo "================================"
        echo "Running my test for threads"
        echo "================================"
        LD_LIBRARY_PATH=.. ./test_threads
        fi

        if [ -x "./test_mutexes" ]; then
        echo
        echo "================================"
        echo "Running my test for mutexes"
        echo "================================"
        LD_LIBRARY_PATH=.. ./test_mutexes
        fi

        if [ -x "./test_bulk" ]; then
        echo
        echo "================================"
        echo "Running my test for bulk"
        echo "================================"
        LD_LIBRARY_PATH=.. ./test_bulk
        fi

        if [ -x "./test_002" ]; then
        echo "================================"
        echo "Running Konstantins test"
        echo "================================"
        LD_LIBRARY_PATH=.. ./test_002
        fi