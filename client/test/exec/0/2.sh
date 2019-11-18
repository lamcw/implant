#!/bin/bash

./sc-client exec --bash --hide whoami
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/exec/0/2.comm