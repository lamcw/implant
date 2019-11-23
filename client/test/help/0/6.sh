#!/bin/sh

./sc-client help unhide > output.txt
diff -Z output.txt client/test/help/0/6.stdout