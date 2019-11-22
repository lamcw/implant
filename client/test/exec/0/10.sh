#!/bin/bash

./sc-client exec --bash --gid 0 --hide --uid 0 whoami
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/exec/0/10.comm