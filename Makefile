INSTALL = install
INSTALL_DATA = $(INSTALL) -m644
INSTALL_DIR = $(INSTALL) -d
prefix = /usr/local
datarootdir = $(prefix)/share
datadir = $(datarootdir)

all:

installdirs:
	$(INSTALL_DIR) "$(DESTDIR)$(datadir)"/arduino/libraries/CircularBuffer/src

install: all installdirs
	$(INSTALL_DATA) src/*.h "$(DESTDIR)$(datadir)"/arduino/libraries/CircularBuffer/src
	$(INSTALL_DATA) *.* "$(DESTDIR)$(datadir)"/arduino/libraries/CircularBuffer

uninstall:
	rm -rf "$(DESTDIR)$(datadir)"/arduino/libraries/CircularBuffer

.PHONY: all installdirs uninstall
