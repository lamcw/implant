#!/bin/bash

./sc-client exec --hide --gid 0 --bash --uid 0 whoami
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/exec/0/18.comm