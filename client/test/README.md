# sc-client tests

[![pipeline](https://gitlab.com/team-sc/sc-implant/badges/master/pipeline.svg)](https://gitlab.com/team-sc/sc-implant/pipelines)

To provide quality assurance to clients, we provide a testing suite for
sc-client. The testing suite offers black-box testing for all modules
in the client application.

## Background

This testing suite takes advantage of a compile-time generated device
path. The device is typically used to communicate between sc-client and
the kernel module, but in this scenario, the device is set to a
temporary file.

Tests are grouped together by module, such as `exec`, `help` and 
`hide`. Hence each module has tests located in a directory. Within each
directory, there are sub-directories for different types of test sets.
Each sub-directory is numbered starting from 0. Within each sub-
directory, there are test scripts with corresponding test outputs. Again,
each test is numbered starting from 0. Output extensions indicate where
the output will be located. The two main types for this project are:
- `.comm` - output in the compile-time generated device used for
communicating with the kernel module
- `.stdout` - output printed to stdout

```
.
├── <module>
│   └── <set_number>
│       ├── <test_output_number>.<output_type>
│       └── <test_script_number>.sh
...
```

## Prequisites

1. All dependencies to compile `sc-client` (please refer to `/README.md`).
2. Working on a Linux machine with `sh` and `diff`.
3. Set the environment variable TEST_PATH to `/tmp/implant`

```console
$ export TEST_PATH="/tmp/implant"
```

## How to add new tests?

1. Write an expected output file. This file should contain all output
that is expected after running a command, and stored in a text file
with the file extension matching where the output would be located.

For example, for the command `./sc-client hide --module`, the output 
will be printed into the compile-time generated device. Hence, the 
expected output file, `0.comm`, will contain (note that the output ends
with a newline character):

```
hide --module

```
2. Write a corresponding bash script which will run the command, then
`diff` the output with the expected-output-file.

For example, for the same command above, `./sc-client hide --module`, 
the test script would be called `0.sh`, and would contain:

```bash
#!/bin/sh

./sc-client hide --module
echo >> ${TEST_PATH}
diff -Z ${TEST_PATH} client/test/hide/0/0.comm
```

## How to run the test?

1. Change directory into the root directory of the `sc-implant` 
workspace (e.g. `cd ~/sc-implant/`)
2. To build the client with communication being redirected to a 
temporary file, the following command should be used to compile.

```console
$ make IMPLANT_DEVICE_PATH='\"${TEST_PATH}\"' sc-client
```

3. Run the test. e.g.

```console
$ bash client/test/0/0.sh
```

If there is no output, that means the test has passed. The test should
also return 0 on success, which can be checked using:

```console
$ echo $?
```

## How to add tests to Gitlab CI?

Assuming the test has been run and it succeeds, the test can be added
to the Gitlab CI pipeline. This can be done by appending the following
lines to the `.gitlab-ci.yml` (found in the workspace root directory):

```yml
/test/<module>/<set_number>/<test_number>:
  extends: .test
```

For example:

```yml
/test/hide/0/0:
  extends: .test
```
