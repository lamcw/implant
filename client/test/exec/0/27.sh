#!/bin/bash

./sc-client exec --gid 0 --uid 0 --bash --hide whoami
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/exec/0/27.comm