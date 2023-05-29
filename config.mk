# slstatus version
DATE         = $(shell git log -1 --format='%cd' --date=format:'%F')
DATE_TIME    = $(DATE) 00:00
COMMIT_COUNT = $(shell git rev-list --count HEAD --since="$(DATE_TIME)")
VERSION      = $(shell date -d "$(DATE)" +'%Y%m%d')_$(COMMIT_COUNT)

# customize below to fit your system

# paths
DESTDIR   ?=
PREFIX    ?= /usr/local
MANPREFIX  = $(PREFIX)/share/man

REQ_LIBS = x11

LIBFLAGS = `pkg-config $(REQ_LIBS) --cflags`
LIBS     = `pkg-config $(REQ_LIBS) --libs`

# flags
CPPFLAGS = -D_DEFAULT_SOURCE -DVERSION=\"$(VERSION)\"
CFLAGS   = -std=c99 -pedantic -Wall -Wextra -Os $(CPPFLAGS) $(LIBFLAGS)
LDFLAGS  = $(LIBS) -s

# compiler and linker
CC ?= gcc
