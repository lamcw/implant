#!/bin/sh

./sc-client set 1 --gid 0 --uid 0
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/set/0/3.comm
