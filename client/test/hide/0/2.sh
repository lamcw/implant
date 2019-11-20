#!/bin/sh

./sc-client hide --file tmp
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/hide/0/2.comm