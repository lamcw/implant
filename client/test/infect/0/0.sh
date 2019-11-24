#!/bin/sh

./sc-client infect 2>&1 | sed 's/\x1b\[[0-9;]*m//g' > output.txt
diff -Z output.txt client/test/infect/0/0.stdout