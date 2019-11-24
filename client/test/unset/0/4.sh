#!/bin/sh

./sc-client unset 2>&1 | sed 's/\x1b\[[0-9;]*m//g' > output.txt
diff -Z output.txt client/test/unset/0/4.stdout