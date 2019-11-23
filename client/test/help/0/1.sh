#!/bin/sh

./sc-client help infect > output.txt
diff -Z output.txt client/test/help/0/1.stdout