#!/bin/bash

./sc-client exec --uid 0 --hide --bash whoami
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/exec/0/47.comm