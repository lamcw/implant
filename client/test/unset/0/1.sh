#!/bin/bash

./sc-client unset 1 --uid
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/unset/0/1.comm
