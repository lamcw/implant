#!/bin/sh

set -e

test_num=0
for script in client/test/*/*/*.sh
do
    echo 
    echo "\n============ Test ${test_num}: $script ============\n"
    sh $script
    echo -n > ${TEST_PATH}
    echo -n > output.txt
    echo "\nTest ${test_num} passed."
    test_num=$((test_num + 1))
done

echo All tests passed!
