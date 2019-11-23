#!/bin/sh

./sc-client help unset > output.txt
diff -Z output.txt client/test/help/0/8.stdout