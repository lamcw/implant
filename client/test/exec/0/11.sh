#!/bin/bash

./sc-client exec --bash --gid 0 --uid 0 --hide whoami
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/exec/0/11.comm