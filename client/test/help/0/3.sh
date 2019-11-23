#!/bin/sh

./sc-client help exec > output.txt
diff -Z output.txt client/test/help/0/3.stdout