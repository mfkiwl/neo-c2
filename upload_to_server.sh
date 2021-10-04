#!/bin/bash

if [ -e Makefile ]
then
    make distclean
fi
if [ -e vin/Makefile ]
then
    (cd vin; make distclean)
fi

if [ ! -e Makefile ]
then
    (cd ..; tar cvfz neo-c2.tgz neo-c2)
    (cd ..; scp neo-c2.tgz ab25cq@clover-lang.org:)
    ssh ab25cq@clover-lang.org bash -c '"cp -f neo-c2.tgz repo/; cd repo; rm -rf neo-c2; tar xvfz neo-c2.tgz"'
fi

