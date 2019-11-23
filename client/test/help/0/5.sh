#!/bin/sh

./sc-client help hide > output.txt
diff -Z output.txt client/test/help/0/5.stdout