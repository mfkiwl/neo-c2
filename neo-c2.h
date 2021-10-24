
```
if echo $ARG | sed -e 's/-gc/NEOC_GC/' | grep NEOC_GC 1> /dev/null 2> /dev/null
then
    cat $PREFIX/include/neo-c2-gc.h | cpp -I . -U__GNUC__
else
    cat $PREFIX/include/neo-c2-no-gc.h | cpp -I . -U__GNUC__
fi
```

#define foreach(o1, o2) for(auto _obj = nomove (o2), auto o1 = _obj.begin(); !_obj.end(); o1 = _obj.next())

