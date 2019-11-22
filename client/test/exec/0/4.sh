#!/bin/bash

./sc-client exec --gid 0 whoami
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/exec/0/4.comm