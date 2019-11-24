#!/bin/sh

./sc-client exec --gid --uid 2>&1 | sed 's/\x1b\[[0-9;]*m//g' > output.txt
diff -Z output.txt client/test/exec/0/67.stdout