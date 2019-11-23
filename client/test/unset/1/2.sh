#!/bin/sh

valgrind --error-exitcode=1 --leak-check=full ./sc-client unset 1 --uid
