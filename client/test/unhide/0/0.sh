#!/bin/bash

./sc-client unhide --module
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/unhide/0/0.comm
