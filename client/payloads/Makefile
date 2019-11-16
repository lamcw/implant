TARGETSRCS := $(wildcard client/payloads/*/*.c)
TARGETOBJS := merlinClient.o

merlinClient.o:
	ld -r -b binary client/payloads/merlin/merlinClient -o $@

payloads_clean:
	rm -f *.o