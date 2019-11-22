#!/bin/bash

./sc-client exec --hide --bash --gid 0 --uid 0 whoami
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/exec/0/15.comm