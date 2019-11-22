#!/bin/bash

./sc-client exec --bash --uid 0 --gid 0 --hide whoami
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/exec/0/13.comm