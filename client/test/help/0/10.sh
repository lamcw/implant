#!/bin/sh

./sc-client help help > output.txt
diff -Z output.txt client/test/help/0/10.stdout