#!/bin/bash

./sc-client exec --uid 0 --hide --gid 0 --bash whoami
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/exec/0/23.comm