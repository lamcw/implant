#!/bin/sh

valgrind --error-exitcode=1 ./sc-client set 1 --uid 0
