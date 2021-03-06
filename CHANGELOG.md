# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.3.5] - 2019-11-24
### Fixed
- `gid` not being set correctly in kmod.

## [0.3.4] - 2019-11-24
### Added
- Tests for the `help` module in the client.
- Tests for the `payloads` module in the client.
- Tests for invalid inputs to the client.

### Changed
- Tests for `set` and `unset` modules in the client.

### Fixed
- `set`, `unset` and `kill` modules to ensure no memory leaks.
- `set` module in client to accept multiple flags and validate `uid` and `gid`.

## [0.3.3] - 2019-11-23
### Added
- Tests with valgrind to check for memory leaks in the client.

## [0.3.2] - 2019-11-22
### Added
- README for sc-implant project.
- README for sc-client test suite.
- CONTRIBUTING.
- Test coverage reporting.

### Changed
- Tests for exec module to improved client test coverage.

## [0.3.1] - 2019-11-18
### Fixed
- Merlin leaving artefact on unsuccessful exec.
- Client error codes not being propagated to the user.

### Changed
- Structure of tests for Gitlab CI for more modular testing.

### Removed
- Support for file hiding in client.

## [0.3.0] - 2019-11-17
### Added
- Sphinx auto-generated documentation.
- GitLab CI job to build and deploy documentation to GitLab pages.
- GitLab CI stage to test sc-client.
- Implant implementation for hiding the kernel module from userland tools.
- Client support for hiding the implant kernel module.
- Client modular payload framework.
- Example Merlin payload to the client.
- Strict compiler options to catch possible bugs.
- CHANGELOG.

### Changed
- GitLab merge request template to ask if changes to CHANGELOG are required.
- Filenames to remove inconsistent pluralisations.

### Fixed
- Fix device path not being configurable for both the client and implant.
- Fix various type confusion bugs in the client.

## [0.2.0] - 2019-11-12
### Added
- GitLab CI job to build the implant.
- GitLab CI job to build the client.
- GitLab CI job to detect if the style guide is not followed.
- Implant implementation for killing processes.
- Client command shell interface.
- Client binary packed by UPX.
- Unofficial support for building the project for the Linux kernel 4.19+.

### Changed
- Implant API specification to be easier to use.
- Client API specification to closely match the changed implant API.
- Client command line interface install feature renamed to infect.
- Client command line interface uninstall feature renamed to disinfect.

### Removed
- Client command line interface self-erase on successful completion option.

## [0.1.0] - 2019-11-5
### Added
- Vagrantfile for building and manually testing the project.
- Merge request templates to ensure that acceptance criteria is met.
- Implant API specification.
- Implant implementation for setting and resetting process owners.
- Implant implementation for process hiding.
- Implant implementation for userland process execution.
- Implant logging library.
- Client command line interface specification.
- Client command line interface implementation for setting process owners.
- Client command line interface implementation for process hiding.
- Client command line interface implementation for userland process execution.
- Client command line interface install feature.
- Client command line interface uninstall feature.
- Client command line interface self-erase on successful completion option.
- Client logging library.
