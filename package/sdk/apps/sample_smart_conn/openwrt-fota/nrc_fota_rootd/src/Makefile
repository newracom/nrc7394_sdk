CC ?= gcc
CFLAGS ?= -Wall -Wextra -O2 -pthread
LDFLAGS ?= -ljson-c

all: nrc_fota_rootd

nrc_fota_rootd: nrc_fota_rootd.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f nrc_fota_rootd
