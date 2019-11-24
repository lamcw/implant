#!/bin/sh

./sc-client payload --list > output.txt
diff -Z output.txt client/test/payload/0/0.stdout
