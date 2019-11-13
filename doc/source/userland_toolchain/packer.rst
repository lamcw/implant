Packer
======

The **sc-client** binary makes use of a runtime packer, otherwise known as a
`executable compressor <https://en.wikipedia.org/wiki/Executable_compression>`_,
to obfuscate the binary and make it more difficult to use static analysis tools
to reverse engineer it.

Since release v0.2.0, **sc-client** is packed using the popular and well-known
open source executable compressor tool called `UPX <https://upx.github.io/>`_.
