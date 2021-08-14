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
    type = "`./come -n global g.c | grep gGlobal`".split()[1];
    puts(type + " gGlobal2;");
EOS
```
