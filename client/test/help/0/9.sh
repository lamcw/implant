#!/bin/sh

./sc-client help payload > output.txt
diff -Z output.txt client/test/help/0/9.stdout