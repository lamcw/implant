#!/bin/bash

./sc-client hide --pid 1
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/hide/0/1.comm