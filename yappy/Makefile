#######################################################
# installed directories
#######################################################
prefix=/usr/local
exec_prefix=${prefix}
bindir=${exec_prefix}/bin
datadir=${datarootdir}
mandir=${datarootdir}/man
sharedstatedir=${prefix}/com
sysconfdir=${prefix}/etc/yappy
datarootdir=${prefix}/share/yappy
docdir=${datarootdir}/doc
libdir=${exec_prefix}/lib

##########################################################
# environmnet variables
##########################################################
CC=neo-c2
INSTALL=/usr/bin/install -c
CFLAGS=-Isrc/ -I. -L . -fPIC -rdynamic -DPREFIX="\"${DESTDIR}/\"" -I/usr/local/include -L /usr/local/lib -g
LIBS= -lutil -lreadline -lm -lpcre
OS=LINUX
DESTDIR=/usr/local
OBJS=src/main.o src/01int.o src/02add.o src/03str.o src/04print.o src/05var.o src/06fun.o src/07bool.o src/08if.o src/09comment.o src/10while.o src/11op.o src/vm.o

##########################################################
# main
##########################################################
all: yappy

yappy: config.h $(OBJS) 
	$(CC) -o yappy $(OBJS) $(CFLAGS) $(LIBS)

#########################################################
# Object files
#########################################################
$(OBJ): src/*.h Makefile configure

#########################################################
# install
#########################################################
install:

	mkdir -p "$(DESTDIR)/bin"
	$(INSTALL) -m 755 ./yappy "$(DESTDIR)/bin"

#########################################################
# uninstall
#########################################################
uninstall:
	rm -f "$(DESTDIR)"/bin/yappy

#########################################################
# permission
#########################################################
permission:
	chmod 644 *
	chmod 755 .git man src configure
	chmod 644 src/*.c
	chmod 644 src/*.h
	chmod 755 update_clover.sh

########################################################
# clean
########################################################
clean:
	rm -fR yappy yappy.dSYM src/*.o config.log config.status *.stackdump autom4te.cache .DS_Store core.* core a.out src/*.ll src/*.i

distclean: clean
	rm -fR  config.h Makefile autom4te.cache

########################################################
# test
########################################################
test: 
	PWD=`pwd` && ./yappy code/HelloWorld.py

