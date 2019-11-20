#!/bin/sh

./sc-client unhide --pid 1
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/unhide/0/1.comm