#!/bin/sh

./sc-client payload 2>&1 | sed 's/\x1b\[[0-9;]*m//g' > output.txt
diff -Z output.txt client/test/payload/0/4.stdout