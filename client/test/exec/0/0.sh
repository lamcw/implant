#!/bin/bash

./sc-client exec --bash whoami
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/exec/0/0.comm