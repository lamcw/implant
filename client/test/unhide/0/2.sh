#!/bin/bash

./sc-client unhide --file tmp
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/unhide/0/2.comm