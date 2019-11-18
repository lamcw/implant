#!/bin/bash

./sc-client exec --hide whoami
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/exec/0/1.comm