#!/bin/bash

./sc-client exec --bash --gid 0 whoami
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/exec/0/33.comm