include config.mk

SRC = main.c
OBJ = $(SRC:.c=.o)
CRYPTOOBJ = $(CRYPTO:.c=.o)
TOMOBJ = $(LIBTOM:.c=.o)
UPGRADEOBJ = $(UPGRADE:.c=.o)

all: options mktiupgrade

options:
	@echo mktiupgrade build options:
	@echo "CFLAGS	= $(CFLAGS)"
	@echo "CC	= $(CC)"

$(CRYPTOOBJ) $(TOMOBJ) $(UPGRADEOBJ) $(OBJ):
	$(CC) -c -o $@ $(CFLAGS) $(@:.o=.c)

mktiupgrade: $(CRYPTOOBJ) $(TOMOBJ) $(UPGRADEOBJ) $(OBJ)
	$(CC) -o $@ $(CRYPTOOBJ) $(TOMOBJ) $(UPGRADEOBJ) $(OBJ)
	a2x --no-xmllint --doctype manpage --format manpage mktiupgrade.1.txt -v

clean:
	rm -rf mktiupgrade mktiupgrade.1
	rm -rf $(OBJ) $(CRYPTOOBJ) $(TOMOBJ) $(UPGRADEOBJ)

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f mktiupgrade $(DESTDIR)$(PREFIX)/bin
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	cp -f mktiupgrade.1 $(DESTDIR)$(MANPREFIX)/man1

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/mktiupgrade $(DESTDIR)$(MANPREFIX)/man1/mktiupgrade.1

.PHONY: all options clean install uninstall
