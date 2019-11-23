#!/bin/sh

./sc-client < client/test/help/2/0.stdin | sed '1d' | sed 's/\x1b\[[0-9;]*m//g' > output.txt
echo >> output.txt
diff -Z output.txt client/test/help/2/0.stdout