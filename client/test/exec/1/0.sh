#!/bin/sh

valgrind --error-exitcode=1 ./sc-client exec --bash --hide --uid 0 --gid 0 whoami
