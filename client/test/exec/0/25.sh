#!/bin/bash

./sc-client exec --uid 0 --gid 0 --bash --hide whoami
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/exec/0/25.comm