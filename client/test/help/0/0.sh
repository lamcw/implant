#!/bin/sh

./sc-client help > output.txt
diff -Z output.txt client/test/help/0/0.stdout