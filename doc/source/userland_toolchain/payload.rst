Payload
=======

The **sc-client** binary provides payloads that can be deployed on a host
system. These payloads are provided by the user at compile time.

The user can check the available payloads by using the command line interface
or the command shell. Afterwards, the name of the desired payload can be
provided to the command line interface or the command shell to deploy it.

Merlin
======

`Merlin <https://github.com/Ne0nd0g/merlin>`_ is a cross-platform
post-exploitation HTTP/2 command and control toolkit. The toolkit provides a
server and a client binary.

As an example for the usage of **sc-client**'s modular payload framework, A
Merlin payload is provided along with the default configuration of
**sc-implant**.
