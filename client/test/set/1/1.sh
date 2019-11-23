#!/bin/sh

valgrind --error-exitcode=1 --leak-check=full ./sc-client set 1 --uid 0
