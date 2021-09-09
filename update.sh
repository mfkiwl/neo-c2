#!/bin/bash

if [ -e vico/Makefile ]
then
    (cd vico && make distclean)
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

