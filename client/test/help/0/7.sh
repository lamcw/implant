#!/bin/sh

./sc-client help set > output.txt
diff -Z output.txt client/test/help/0/7.stdout