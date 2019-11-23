#!/bin/sh

./sc-client help non-module 2>&1 | sed 's/\x1b\[[0-9;]*m//g' > output.txt
diff -Z output.txt client/test/help/0/11.stdout
