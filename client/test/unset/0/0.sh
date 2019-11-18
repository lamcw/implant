#!/bin/bash

./sc-client exec --hide whoami
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/unset/0/0.comm