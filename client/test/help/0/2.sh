#!/bin/sh

./sc-client help disinfect > output.txt
diff -Z output.txt client/test/help/0/2.stdout