TARGETSRCS := $(wildcard client/payload/*/*.c)
TARGETOBJS := merlinClient.o

merlinClient.o:
	ld -r -b binary client/payload/merlin/merlinClient -o $@

payloads_clean:
	rm -f *.o