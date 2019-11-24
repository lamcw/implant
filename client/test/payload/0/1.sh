#!/bin/sh

./sc-client payload --exec merlin | sed 's/\x1b\[[0-9;]*m//g' > output.txt
diff -Z output.txt client/test/payload/0/1.stdout
