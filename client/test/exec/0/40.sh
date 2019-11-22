#!/bin/bash

./sc-client exec --bash --hide --uid 0 whoami
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/exec/0/40.comm