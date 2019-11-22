#!/bin/bash

./sc-client exec --hide --bash whoami
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/exec/0/7.comm