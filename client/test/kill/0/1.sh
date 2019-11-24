#!/bin/sh

./sc-client kill 2>&1 | sed 's/\x1b\[[0-9;]*m//g' > output.txt
diff -Z output.txt client/test/kill/0/1.stdout