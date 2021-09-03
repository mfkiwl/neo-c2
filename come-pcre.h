```
if [ "$COME_FLAG" = 1 ]
then
    cat $PREFIX/include/come-pcre-declare.h | cpp -I . -U__GNUC__
elif [ -z "$COME_FLAG" ]
then
    export COME_FLAG=1
    main_module=`come function $SOURCE_NAME | egrep ^main\\ `

    if [ -z "$main_module" ]
    then
        cat $PREFIX/include/come-pcre-declare.h | cpp -I . -U__GNUC__
    else
        cat $PREFIX/include/come-pcre-main.h | cpp -I . -U__GNUC__
    fi
fi
```
