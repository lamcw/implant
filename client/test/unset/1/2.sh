#!/bin/sh

valgrind --error-exitcode=1 ./sc-client unset 1 --uid
