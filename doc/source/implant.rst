Implant
=======

The core of **sc-implant** is realised as a loadable Linux kernel module. This
kernel module is specifically designed supported for the kernel shipping with
the popular Linux distribution, Debian Buster.

Communication with **sc-implant** is done through a character device created by
the kernel module on load. This device, by default, is accessible at
*/dev/implant*. Along with the device, **sc-implant** provides a protocol that
allows userland applications to send requests to the kernel module. These
requests allow **sc-implant** to perform operations on behalf of unprivileged
userland processes.

The **sc-implant** API allows users to execute tasks (start
processes). These tasks are spawned from within the kernel, can be hidden, and
can belong to any user on the system including *root*.

.. code-block:: shell

   $ echo exec <command> > /dev/implant
   $ echo exec --bash <command> > /dev/implant
   $ echo exec --hide <command> > /dev/implant
   $ echo exec --uid <uid> --gid <gid> <command> > /dev/implant

The **sc-implant** API allows users to kill tasks (kill
processes).

.. code-block:: shell

   $ echo kill <pid> > /dev/implant

The **sc-implant** API allows users to hide tasks (hide
processes). These tasks are hidden from userland applications but continue to be
scheduled by the kernel.

.. code-block:: shell

   $ echo hide --pid <pid> > /dev/implant

The **sc-implant** API allows users to unhide tasks (unhide
processes). These tasks will become visible to userland applications again.

.. code-block:: shell

   $ echo unhide --pid <pid> > /dev/implant

The **sc-implant** API allows users to modify the state of
running tasks (running processes). This can be used to elevate or lower the
privilege of a running process.

.. code-block:: shell

   $ echo set <pid> --uid <uid> > /dev/implant
   $ echo set <pid> --gid <gid> > /dev/implant
   $ echo set <pid> --uid <uid> --gid <gid> /dev/implant

The **sc-implant** API allows users to revert the
modifications they made to running tasks. The previous is stored by
**sc-implant**.

.. code-block:: shell

   $ echo unset <pid> --uid > /dev/implant
   $ echo unset <pid> --gid > /dev/implant
   $ echo unset <pid> --uid --gid > /dev/implant
