```
if echo $ARG | sed -e 's/-gc/NEOC_GC/' | grep NEOC_GC 1> /dev/null 2> /dev/null
then
    if [ "$COME_FLAG" = 1 ]
    then
        cat $PREFIX/include/neo-c2-pcre-declare-gc.h | cpp -I . -U__GNUC__
    elif [ -z "$COME_FLAG" ]
    then
        export COME_FLAG=1
        main_module=`neo-c2 function $SOURCE_NAME | fgrep 'main('`

        if [ -z "$main_module" ]
        then
            cat $PREFIX/include/neo-c2-pcre-declare-gc.h | cpp -I . -U__GNUC__
        else
            cat $PREFIX/include/neo-c2-pcre-main-gc.h | cpp -I . -U__GNUC__
        fi
    fi
else
    if [ "$COME_FLAG" = 1 ]
    then
        cat $PREFIX/include/neo-c2-pcre-declare.h | cpp -I . -U__GNUC__
    elif [ -z "$COME_FLAG" ]
    then
        export COME_FLAG=1
        main_module=`neo-c2 function $SOURCE_NAME | fgrep 'main('`

        if [ -z "$main_module" ]
        then
            cat $PREFIX/include/neo-c2-pcre-declare.h | cpp -I . -U__GNUC__
        else
            cat $PREFIX/include/neo-c2-pcre-main.h | cpp -I . -U__GNUC__
        fi
    fi
fi
```
