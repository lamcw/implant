#!/bin/sh

./sc-client help kill > output.txt
diff -Z output.txt client/test/help/0/4.stdout