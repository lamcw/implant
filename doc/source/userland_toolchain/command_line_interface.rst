Command Line Interface
======================

The **sc-client** binary provides a command line interface for dropper
operations and for communicating with **sc-implant**.

The **sc-client** command line interface allows users to infect and disinfect
their machines with **sc-implant**. Considering that this is a post-exploitation
tool, the initial infection does require root privileges on the host machine.

.. code-block:: shell

   $ sc-client infect
   $ sc-client disinfect

The **sc-client** command line interface allows users to execute tasks (start
processes). These tasks are spawned from within the kernel, can be hidden, and
can belong to any user on the system including *root*.

.. code-block:: shell

   $ sc-client exec <command>
   $ sc-client exec --bash <command>
   $ sc-client exec --hide <command>
   $ sc-client exec --uid <uid> --gid <gid> <command>

The **sc-client** command line interface allows users to kill tasks (kill
processes).

.. code-block:: shell

   $ sc-client kill <pid>

The **sc-client** command line interface allows users to hide tasks (hide
processes). These tasks are hidden from userland applications but continue to be
scheduled by the kernel.

.. code-block:: shell

   $ sc-client hide --pid <pid>

The **sc-client** command line interface allows users to hide the implant
kernel module. The module is hidden from common userland tools.

.. code-block:: shell

   $ sc-client hide --module

The **sc-client** command line interface allows users to unhide tasks (unhide
processes). These tasks will become visible to userland applications again.

.. code-block:: shell

   $ sc-client unhide --pid <pid>

The **sc-client** command line interface allows users to unhide the implant
kernel module.

.. code-block:: shell

   $ sc-client unhide --module

The **sc-client** command line interface allows users to modify the state of
running tasks (running processes). This can be used to elevate or lower the
privilege of a running process.

.. code-block:: shell

   $ sc-client set <pid> --uid <uid>
   $ sc-client set <pid> --gid <gid>
   $ sc-client set <pid> --uid <uid> --gid <gid>

The **sc-client** command line interface allows users to revert the
modifications they made to running tasks. The previous is stored by
**sc-implant**.

.. code-block:: shell

   $ sc-client unset <pid> --uid
   $ sc-client unset <pid> --gid
   $ sc-client unset <pid> --uid --gid

The **sc-client** command line interface allows users to use payloads provided
at compile time.

.. code-block:: shell

   $ sc-client payload --list
   $ sc-client payload --exec merlin
