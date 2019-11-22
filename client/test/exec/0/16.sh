#!/bin/bash

./sc-client exec --hide --uid 0 --bash --gid 0 whoami
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/exec/0/16.comm