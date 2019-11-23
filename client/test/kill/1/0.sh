#!/bin/sh

valgrind --error-exitcode=1 --leak-check=full ./sc-client kill 1
