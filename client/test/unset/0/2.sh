#!/bin/sh

./sc-client unset 1 --uid --gid
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/unset/0/2.comm
