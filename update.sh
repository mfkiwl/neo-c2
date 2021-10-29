#!/bin/bash

if [ -e vin/Makefile ]
then
    (cd vin && make distclean)
fi

if [ -e zash/Makefile ]
then
    (cd zash && make distclean)
fi

if [ -e yajs/Makefile ]
then
    (cd yajs && make distclean)
fi


if [ -e Makefile ]
then
    make distclean
fi

if [ ! -e Makefile ]
then
    git add .
    git commit 
    git remote add origin https://github.com/ab25cq/neo-c2
    git push -f -u origin master
fi

