#!/bin/sh

./sc-client set 1 --gid 0
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/set/0/1.comm
