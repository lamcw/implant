#!/bin/bash

./sc-client kill 1
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/kill/0/0.comm