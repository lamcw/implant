# sc-implant

[![pipeline](https://gitlab.com/team-sc/sc-implant/badges/master/pipeline.svg)](https://gitlab.com/team-sc/sc-implant/pipelines)

The **sc-implant** project consists of a loadable Linux kernel module and a companion
toolchain, internally referred to as **sc-client**, for managing the module. The
objective of this project is to provide an easy-to-use implant to be used as a
home base for further operations when red-teaming and conducting penetration
tests.

## Dependencies

The **sc-implant** project targets the
[Debian Buster](https://wiki.debian.org/DebianBuster) Linux-based operating
system. The following dependencies are required to build the project.

```console
$ sudo apt-get update -y && sudo apt-get dist-upgrade -y
$ sudo apt-get install -y --no-install-recommends linux-headers-4.19.0-6-amd64 build-essential upx-ucl
```

Alternatively, [Vagrant](https://www.vagrantup.com/) can be used to build a
ready-made virtual machine. A Vagrantfile has been provided in the root of the
project repository.

## Build

```console
$ make # Builds the loadable Linux kernel module.
$ make sc-client # Builds the userland toolchain.
```

## Documentation

Documentation is generated using
[Sphinx](https://www.sphinx-doc.org/en/master/). The documentation can be built
from the root directory of the repository.

```console
$ sudo apt-get install python3-sphinx
$ pip3 install hawkmoth sphinx-rtd-theme --user
$ make -C doc html
```

The built documentation can be viewed in a web browser by opening
`doc/build/html/index.html`.

## Contributing

See [CONTRIBUTING.md](./CONTRIBUTING.md).

## Changelog

See [CHANGELOG.md](./CHANGELOG.md).

## License

[GNU GPLv3](./LICENSE).

## Third Party Library Usage

The project uses
[ketopt](https://github.com/attractivechaos/klib/blob/master/ketopt.h) for
argument parsing in both the userland toolchain and the kernel module. The
example payload is [merlin](https://github.com/Ne0nd0g/merlin).
