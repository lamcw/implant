#!/bin/bash

./sc-client exec --uid 0 --hide --bash --gid 0 whoami
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/exec/0/22.comm