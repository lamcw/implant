#!/bin/sh

valgrind --error-exitcode=1 --leak-check=full ./sc-client hide --module
