KDIR = /lib/modules/`uname -r`/build

kbuild:
	make -C $(KDIR) M=`pwd`

clean:
	make -C $(KDIR) M=`pwd` clean

format:
	type clang-format > /dev/null && git ls-files "*.c" "*.h" | xargs clang-format -i
