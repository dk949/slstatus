# See LICENSE file for copyright and license details
# slstatus - suckless status monitor
.POSIX:

include config.mk

REQ = util
COM =\
    components/battery\
    components/cpu\
    components/datetime\
    components/disk\
    components/entropy\
    components/hostname\
    components/ip\
    components/kernel_release\
    components/keyboard_indicators\
    components/keymap\
    components/load_avg\
    components/netspeeds\
    components/num_files\
    components/ram\
    components/run_command\
    components/separator\
    components/swap\
    components/temperature\
    components/uptime\
    components/user\
    components/volume\
    components/wifi\
    components/env_var\
    components/check_updates\
    components/check_packages\
    components/driver_active\
    components/run_command_timed\


all: slstatus

$(COM:=.o): config.mk $(REQ:=.h)
slstatus.o: slstatus.c slstatus.h arg.h config.h config.mk $(REQ:=.h)

.c.o:
	$(CC) -o $@ -c $(CFLAGS) $<

config.h:
	cp config.def.h $@

slstatus: slstatus.o $(COM:=.o) $(REQ:=.o)
	$(CC) -o $@ $(LDFLAGS) $(COM:=.o) $(REQ:=.o) slstatus.o

clean:
	rm -f slstatus slstatus.o $(COM:=.o) $(REQ:=.o)

install: all
	mkdir -p "$(DESTDIR)$(PREFIX)/bin"
	cp -f slstatus "$(DESTDIR)$(PREFIX)/bin"
	chmod 755 "$(DESTDIR)$(PREFIX)/bin/slstatus"
	mkdir -p "$(DESTDIR)$(MANPREFIX)/man1"
	cp -f slstatus.1 "$(DESTDIR)$(MANPREFIX)/man1"
	chmod 644 "$(DESTDIR)$(MANPREFIX)/man1/slstatus.1"

uninstall:
	rm -f "$(DESTDIR)$(PREFIX)/bin/slstatus"
	rm -f "$(DESTDIR)$(MANPREFIX)/man1/slstatus.1"
