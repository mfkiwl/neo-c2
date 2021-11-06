#!/bin/bash

if [ -e vin/Makefile ]
then
    (cd vin && make distclean)
fi

if [ -e yapy/Makefile ]
then
    (cd yapy && make distclean)
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

