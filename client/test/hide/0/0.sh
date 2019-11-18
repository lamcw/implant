#!/bin/bash

./sc-client hide --module
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/hide/0/0.comm