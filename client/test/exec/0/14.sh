#!/bin/bash

./sc-client exec --hide --bash --uid 0 --gid 0 whoami
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/exec/0/14.comm