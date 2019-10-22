KDIR = /lib/modules/`uname -r`/build

# Builds the kernel module.
kmod:
	make -C $(KDIR) M=`pwd`

# Compile the Linux kernel.
#
# This rule allows for the compilation of the kernel module from a different
# host machine.
#
# A useful side-effect is that smart completion and navigation can be provided.
kbuild: ksource
	cd ./usr/src/linux-source-4.19; \
		make -j4 && make modules; \
		wget -nc https://raw.githubusercontent.com/torvalds/linux/master/scripts/gen_compile_commands.py; \
		python2 gen_compile_commands.py;

# Download and patch the Linux kernel.
ksource:
	wget -nc http://security.debian.org/debian-security/pool/updates/main/l/linux/linux-source-4.19_4.19.67-2+deb10u1_all.deb; \
		touch ksource; # Make can use this to know that the rule has been met.
	ar -xv linux-source-4.19_4.19.67-2+deb10u1_all.deb
	tar -xvf data.tar.gz
	cd ./usr/src/; \
		tar -xvf linux-source-4.19.tar.xz
	cd ./usr/src/linux-source-4.19; \
		xzcat ../linux-patch-4.19-rt.patch.xz | patch -p1; \
		make ARCH=x86_64 defconfig; # Use the default configuration.
	rm -rf control.tar.gz data.tar.gz debian-binary linux-source-4.19_4.19.67-2+deb10u1_all.deb

clean:
	make -C $(KDIR) M=`pwd` clean; \
		rm -rf usr ksource

format:
	type clang-format > /dev/null && git ls-files "*.c" "*.h" | xargs clang-format -i
