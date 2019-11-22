#!/bin/bash

./sc-client exec --hide --uid 0 --bash whoami
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/exec/0/45.comm