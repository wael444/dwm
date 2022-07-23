# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

# dwm version
VERSION = 6.3

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# flags, includes, libs
DWMCPPFLAGS =  -DVERSION=\"${VERSION}\" -DXINERAMA ${CPPFLAGS}
DWMCFLAGS   = -I/usr/include/freetype2 ${DWMCPPFLAGS} ${CFLAGS}
DWMLDFLAGS  = -lX11 -lXinerama -lfontconfig -lXft ${LDFLAGS}

SRC = drw.c dwm.c util.c
OBJ = ${SRC:.c=.o}

CC = tcc

all: dwm

.c.o:
	${CC} -c ${DWMCFLAGS} $<

dwm: ${OBJ}
	${CC} -o $@ ${OBJ} ${DWMLDFLAGS}

clean:
	rm -f dwm ${OBJ}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f dwm ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/dwm

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/dwm

.PHONY: all clean install uninstall
