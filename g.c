int gGlobal;

struct sA 
{
    int a;
    int b;
};

typedef int tType;
typedef int tType2;

enum eEnumA { kA, kB };

```
ruby <<EOS
    type = "`./come -n global $SOURCE_NAME | grep gGlobal`".split()[1];
    puts(type + " gGlobal2;");
EOS
```

int fun() 
{
    return 1 + 1;
}
