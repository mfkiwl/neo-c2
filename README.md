# neo-c2

C extension compiler language. Some compatibility for C language.

This language is self-hosted.

version 1.0.9

```
#include <neo-c2.h>

int main() 
{
    puts(xsprintf("%d", 1+1));

    auto v = new vector<char*>.initialize();

    v.push_back("AAA");
    v.push_back("BBB");
    v.push_back("CCC");

    foreach(it, v) {
        puts(it);
    }

    auto m = new map<char*,int>.initialize();

    m.insert("AAA", 1);
    m.insert("BBB", 2);
    m.insert("CCC", 3);

    foreach(key, m) {
        auto item = m.at(key, -1);

        printf("%s %d\n", key, item);
    }

    auto str = string("ABC");

    puts(str.substring(0,1));

    int fd = open("ABC", O_RDONLY).expect {
        fprintf(stderr, "can't open ABC");
        exit(1);
    }

    3.times {
        puts("HELLO METHOD BLOCK");
    }

    auto li = new list<int>.initialize();

    li.push_back(1);
    li.push_back(2);
    li.push_back(3);

    li.filter { return it > 1; }.each {
        printf("%d\n", it);
    }

    return 0;
}
```

1. It is compatible with C language to some extent. The C preprocessor also works.

2. It has its own heap system. It has an automatic free of the temporarily generated heap (rvalue) and an automatic free of the heap assigned to the variable.

3. It has Generics, Method Generics, inline function, debug info (-g option), and lambda.

4. The library is written in neo-c2.h and you don't need to link any library. The library is minimal and keeps learning costs down. It has a collection library and a string library.

5. It has a mixin-layers system. You can implement your application in layers. Each layer is complete and useful for debugging and porting. A vi clone called vico is implemented as an editor implemented in mixin-layers. Please refer to it because it is in a directory called vico.

6. Parallel excuting functions like Go.

7. Macro and Reflection. Combination using with its can generate code on compile time. Compile time reflection.

8. method block like Ruby

10. Macro

11. defer

1. C言語とある程度互換性があります。Cプリプロセッサーも動きます。

2. 独自のヒープシステムを備えます。一時的に生成されたヒープ（右辺値）の自動freeと変数に代入されたヒープの自動freeを備えます。

3. Generics, Method Generics, inline function, debug info(-g option), lambdaを備えます。

4. ライブラリはneo-c2.hに書かれてあり、何もライブラリをリンクする必要はありません。ライブラリは最小限となっており学習コストを抑えています。コレクションライブラリと文字列ライブラリを備えます。

5. mixin-layersシステムを備えます。アプリケーションをレイヤーを重ねるように実装できます。各レイヤーは完結しており、デバッグや移植作業でも有効です。mixin-layersで実装されたエディッタとしてvinというviクローンを実装しています。vinというディレクトリの中に入っているので参考にしてください。

6. Goのような関数の並列実行の機能があります。チャネルも備えます。

7. マクロとリフレクションを備えます。コンパイルタイムにリフレクションとコード生成が行えます。

8. Rubyのようなメソッドブロックがあります。

9. 正規表現を使った文字列ライブラリがあります。

10. マクロがあります。

11. 遅延評価(defer)があります。

0. INSTALL

Required libraries are llvm-dev, clang, clang++, g++,  gcc, make, autoconf, valgrind, gdb, pcre-dev, gc-dev

Examples

```
sudo apt-get install clang clang++ g++ make autoconf llvm-dev git gdb valgrind gcc libpcre-dev libgc-dev
```

For PC, WSL, Raspberry PI OS and iSH(iPhone)

```
git clone https://github.com/ab25cq/neo-c2

cd neo-c2

./configure --with-optimize
make
sudo make install
make test

or 

bash all_build.sh
```

Without self-host. 

```
git clone https://github.com/ab25cq/neo-c2

cd neo-c2

./configure --with-optimize
make no-self-host
sudo make install
make test

or 

bash no_self_host.sh
```

Install to home directory. For termux(android), and MacOS(INTEL)

```
git clone https://github.com/ab25cq/neo-c2

cd neo-c2

./configure --with-optimize --prefix=$HOME
make
sudo make install
make test

or 

bash home_build.sh
```

1. Language specifications

It is almost the same as C language. Since it is not POSIX compliant, it is not compatible with C language in every detail, but I think that anyone who can use C language can use it immediately. If you don't use the heap system and do #include <neo-c2.h>, you can just use it as a C compiler.

C言語とほぼ一緒です。POSIX準拠じゃないため、あまり細部までC言語とは互換性がありませんが、C言語を使える人ならすぐ使えると思います。
ヒープシステムを使わずに#include <neo-c2.h>をしなければ、単なるCコンパイラとして使えます。

2. HELLO WORLD

```
> vim a.c
#include <stdio.h>

int main()
{
    puts("HELLO WORLD");
    return 0;
}
> neo-c2 a.c
> clang a.c.ll
> ./a.out
HELLO WORLD
```

The compilation result is output to the source file name.ll. The output of the C preprocessor is saved in the source file name .i. The library does not need to be linked. It can be used like a normal C compiler. Of course, you can freely use the library in C language. If you add the -g option, debug information will also be output. 

コンパイル結果はソースファイル名.llに出力されます。ソースファイル名.iにCプリプロセッサの出力が保存されます。ライブラリは何もリンクする必要がありません。
通常のCコンパイラと同じように使えます。もちろんライブラリもC言語のものを自由に使えます。-gオプションをつけるとデバッグ情報も出力されます。

コンパイルするclangですがLLVM-10以上が必要でLLVM-7が標準のdebianではsudo apt-get install llvm-11-devしてください。その場合はllをコンパイルするclangはclang-11としてください。まあ、今のbusterでのDebianの話ですが。

It is clang to compile, but LLVM-10 or higher is required, and LLVM-7 is standard debian, please do sudo apt-get install llvm-11-dev. In that case, clang to compile ll should be clang-11. Well, it's about Debian in the current buster.

```
> vim a.c
#include <stdio.h>

int main()
{
    puts("HELLO WORLD");
    return 0;
}
> neo-c2 a.c
> clang-11 a.c.ll
> ./a.out
HELLO WORLD
```

3. Heap System

The cost of learning the library is low, but the heap system will take some time to learn. Basically, use valgrind to check if a memory leak is occurring. You can also find out illegal memory access by using valgrind. You can also use the -g option to find out the location of memory leaks in the source code and unauthorized memory access in the source code. The basic rule is that rvalues (temporary heap generation that is not assigned to variables) are automatically freed.

ライブラリの学習コストは低いですが、ヒープシステムは学習するのに少し時間がかかるでしょう。基本的にメモリーリークが起こっているかの確認はvalgrindを使ってください。
また不正なメモリアクセスもvalgrindを使えば分かるでしょう。-gオプションを使うとソースコードでのメモリーリークや不正なメモリアクセスのソースコードでの位置も分かります。

基本的なルールですが、右辺値（変数に代入されない一時的なヒープの生成)は自動的にfreeされます。

```
puts(xsprintf("1 + 1 == %d\n", 1 + 1));
```

xsprintf uses the heap to generate memory, but since it is an rvalue, it is automatically freed after puts. It is the timing when the rvalue is freed, but after one sentence is executed. I don't expect code that makes heavy use of method chains like Ruby, but even if method chains are used, method chains can be performed because the memory of the rvalue heap exists until the execution of one sentence is completed. Probably. The next rule is that the function that creates the heap assigned to the variable with% and the memory such as new will be freed after the block escapes.

xsprintfはヒープを使ったメモリが生成されますが、右辺値なので、puts後に自動的にfreeされます。右辺値がfreeされるタイミングですが、1文が実行された後です。
あまり、Rubyのようにメソッドチェインを多用するコードは想定していませんが
メソッドチェインしても１文の実行が終わるまで右辺値のヒープのメモリは存在しているためメソッドチェインを行うことも可能でしょう。

次のルールは%をつけた変数に代入されたヒープを生成する関数やnewなどのメモリはブロックの脱出後にfreeされます。

```
char*% str = new char[123];

strncpy(str, "AAA", 123);

puts(str);
```

Note that if char * str is used, the result of new char [123] will be judged as an rvalue and will be freed before being assigned. If you find it awkward to write char *%, use auto. The rvalue type is type inferred and declared.

char* strとするとnew char[123]の結果は右辺値と判断されて代入される前にfreeされるので注意してください。
char*%と書くのがめんどくさい場合はautoを使ってください。右辺値の型が型推論されて宣言されます。

```
auto str = new char[123];

strncpy(str, "ABC", 123);

puts(str);
```

If you want to manage the memory yourself, add borrow to declare heap memory that is not an rvalue, and then assign it to a pointer without%.

自分でメモリを管理したい場合はborrowをつけて右辺値じゃないヒープメモリと宣言してから%をつけないポインタに代入してください。

```
char* str = borrow char str[123];

strncpy(str, "ABC", 123);

puts(str);

delete str;
```

If you add borrow, it will be excluded from the target of automatic free of rvalue, and automatic free of rvalue will not be done. Assignment between variables with% added to the type name causes a transfer of ownership.

borrowをつけると右辺値の自動freeの対象から外されて、右辺値の自動freeがされないようになります。

型名に%をつけた変数同士の代入は所有権の移動が起こります。

```
    auto a = new char[128];
    auto b = a;
```

It is b that is freed. a cannot be used after auto b. Use no move to prevent this.

freeされるのはbです。aはauto b以降使えなくなります。これを防ぐにはnomoveを使ってください。

```
    auto a = new char[128];
    auto b = nomove a;
```

It is a that is freed. When nomove is used for the rvalue, the rvalue is not automatically freed at the end of the line, but is freed when the variable disappears.

freeされるのはaです。

右辺値にnomoveを使った場合ですが、その場合は右辺値は行末で自動freeされるのではなく変数が消えた時にfreeされます。

```
char* fun() 
{
    return new char[128];
}

int main()
{
    auto a = nomove fun();
    return 0;
}
```

a is freed at the end of main. Next is the case of a function. If% is attached to the argument of the function, the management of heap memory shifts to the function side. On the other hand, if you do not add%, you will simply refer to the memory.

aはmainの終了時にfreeされます。

次は関数の場合です。関数の引数に%がついていた場合はヒープメモリの管理は関数側に移ります。逆に%をつけていない場合は単にメモリの参照をすることとなります。

```
void fun(char* str)
{
    puts(str);
}

int main()
{
    char*% str = new char[123];
    
    strncpy(str, "ABC", 123);

    fun(str);

    return 0;
}
```

In this case, str is freed before the return of the main function. You can still use str after calling fun.

この場合はmain関数のreturnの前にstrがfreeされます。funの呼び出し後もstrは使えます。

```
void fun(char*% str)
{
    puts(str);
}

int main()
{
    char*% str = new char[123];
    
    strncpy(str, "ABC", 123);

    fun(str);

    return 0;
}
```

In this case, str is freed in fun. You cannot use str after calling fun. The same rule applies when a heap is temporarily created with a function argument.

この場合はfunの中でstrがfreeされます。funを呼び出した後はstrは使えません。

関数の引数で一時的にヒープを生成した場合も同様のルールとなります。


```
void fun(char* str)
{
    puts(str);
}

int main()
{
    fun(string("AAA"));
}
```

string is a function that returns a char *% type string. In this case, the return value (rvalue) of string is freed after calling fun. string is defined as follows.

stringはchar*%型の文字列を返す関数です。この場合はfunの呼び出し後にstringの戻り値(右辺値)がfreeされます。

stringは以下のように定義されています。

```
typedef char*% string;

inline string string(char* str)
{
    int len = strlen(str) + 1;
    char* result = (char*)calloc(len, sizeof(char));

    strncpy(result, str, len);

    return dummy_heap result;
}
```

dummy_heapは普通のポインタに%を付与します。

便利なstring関数としては以下があります。

dummy_heap gives% to ordinary pointers. Some useful string functions are:

```
static string xsprintf(char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    char* result;
    int len = vasprintf(&result, msg, args);
    va_end(args);

    if(len < 0) {
        fprintf(stderr, "can't get heap memory.\n");

        exit(2);
    }

    return dummy_heap result;
}

static string char::reverse(char* str) 
{
    int len = strlen(str);
    string result = new char[len + 1];

    for(int i=0; i<len; i++) {
        result[i] = str[len-i-1];
    }

    result[len] = '\0';

    return result;
}

static string char::substring(char* str, int head, int tail)
{
    if(str == null) {
        return string("");
    }

    int len = strlen(str);

    if(head < 0) {
        head += len;
    }
    if(tail < 0) {
        tail += len + 1;
    }

    if(head > tail) {
        return str.substring(tail, head).reverse();
    }

    if(head < 0) {
        head = 0;
    }

    if(tail >= len) {
        tail = len;
    }

    if(head == tail) {
        return string("");
    }

    if(tail-head+1 < 1) {
        return string("");
    }

    string result = new char[tail-head+1];

    memcpy(result, str + head, tail-head);
    result[tail-head] = '\0';

    return result;
}
```

使い方は

Usage is bellow:

```
if(strcmp(xsprintf("%d", 2), "2") == 0) {
    puts("OK");
}
if(strcmp("ABC".reverse(), "CBA") == 0) {
    puts("OK");
}

if(strcmp("ABC".substring(0,1), "A") == 0) {
    puts("OK");
}
```

It will be. It is called when "object type name_method name" is called as an OOP-like function. In other words, "ABC" .reverse () is the same as calling char_reverse ("ABC") or char::reverse("ABC"). Another important point is that the memory allocated in the heap is called finalizer according to the type name.

となります。OOP的な機能として"オブジェクトの型名_メソッド名"がメソッドコールした場合は呼ばれます。
つまり、"ABC".reverse()はchar_reverse("ABC")もしくはchar::reverse("ABC")を呼び出したことと同じことです。

もう一つ重要な点はヒープで確保されたメモリは型名に応じてfinalizerが呼ばれることです。

```
struct sData
{
    string value1;
    string value2;
};

sData*% sData_initialize(sData*% self)
{
    self.value1 = string("ABC");
    self.value2 = string("DEF");
    
    return self;
}

void sData_finalize(sData* self)
{
    delete self.value1;
    delete self.value2;
}

int main(int argc, char** argv)
{
    auto d = new sData.initialize();

    printf("%s %s\n", d.value1, d.value2);

    return 0;
}
```

If you keep the heap in the struct, it will not be automatically freed. Be sure to define finalizer and use delete to free up memory. The other heap-related function is clone. clone copies the memory allocated in the heap as it is.

structの中にヒープを保持する場合、自動的にはfreeされません。必ずfinalizerを定義してdeleteを使い、メモリを開放してください。

後一つヒープ関連である機能は、cloneです。cloneはヒープに確保されたメモリを内容をそのままにコピーします。

```
struct sData
{
    int value1;
    int value2;
};

sData*% sData_initialize(sData*% self)
{
    self.value1 = 123;
    self.value2 = 234;

    return self;
}

int main(int argc, char** argv)
{
    auto d = new sData.initialize();

    printf("%d %d\n", d.value1, d.value2);

    auto e = clone d;

    printf("%d %d\n", e.value2, e.value2);

    return 0;
}
```

e also holds the same value as d. However, this feature only copies the pointer if you hold the heap in a shallow copy. If you delete the pointer, you will get a segmentation fault if you clone it. To prevent this, implement a method called clone.

eもdと同じ値を保持しています。ただし、この機能は浅いコピーでヒープを保持していた場合ポインタがコピーされるだけです。
もしそのポインタをdeleteしてしまうとcloneした場合segmentation faultが起こるでしょう。
これを防ぐためにはcloneというメソッドを実装します。

```
struct sData
{
    string value1;
    string value2;
};

sData*% sData_initialize(sData*% self)
{
    self.value1 = string("ABC");
    self.value2 = string("DEF");
    
    return self;
}

sData*% sData_clone(sData* self)
{
    auto result = new sData;

    result.value1 = clone self.value1;
    result.value2 = clone self.value2;

    return result;
}

void sData_finalize(sData* self)
{
    delete self.value1;
    delete self.value2;
}

int main(int argc, char** argv)
{
    auto d = new sData.initialize();

    printf("%s %s\n", d.value1, d.value2);

    auto e = clone d;

    printf("%s %s\n", e.value1, e.value2);

    return 0;
}
```

This should work fine.

これで不具合なく動くはずです。

You can also new using Boehm GC. In this case, assign it to an ordinary pointer. Since it is a conservative GC, it seems that the memory may not be released, but for the time being, I think that the memory will not be exhausted. finalize is not called. The usage is as follows.

BoehmGCを使ったnewもできます。この場合は普通のポインタに代入してください。保守的GCなのでメモリが解放されない場合もある様子ですが、とりあえずは、メモリは枯渇しないと思います。finalizeは呼ばれません。使い方は以下です。

```
#include <neo-c2.h>

struct sObj {
    int a;
    int b;
};

int main()
{
    sObj* obj = new (GC) sObj;

    obj.a = 1;
    obj.b = 2;

    xassert("gc test", obj.a == 1 && obj.b == 2);

    return 0;
}
```

clone is below:

```
#include <neo-c2.h>

struct sObj {
    int a;
    int b;
};

int main()
{
    sObj* obj = new (GC) sObj;

    obj.a = 1;
    obj.b = 2;

    xassert("gc test", obj.a == 1 && obj.b == 2);

    sObj* obj2 = clone (GC) obj;

    xassert("gc test2", obj2.a == 1 && obj2.b == 2);

    return 0;
}
```

However, in this example, it seems that memory is leaking when valgrind is applied. Isn't it free at the end? I prepared it for the time being. If you use this feature, please -lgc the linker.

ただ、この例ではvalgrindをかけるとメモリがリークしている様子です。終了時にはfreeしないんですかね。とりあえず用意しました。この機能を使った場合はリンカーに-lgcしてください。

4. Generics

Generics is a code generation method. I have implemented it, but basically I am making it for the collection library of the basic library. We do not recommend using Generics for your own application code. This is because the code beneo-c2 complicated. If you want to make your own library, you can use it. The vector is defined as follows.

Genericsはコード生成方式です。実装してますが、基本的に基本ライブラリのコレクションライブラリ用に作っています。
自作のアプリケーションコードにGenericsを使うことはお勧めしません。コードが複雑になるためです。
ライブラリを自作したい場合には使ってもいいと思います。

vectorは以下のように定義されています。

```
struct vector<T> 
{
    T&* items;
    int len;
    int size;

    int it;
};

impl vector<T> 
{
    vector<T>*% initialize(vector<T>*% self);
    void finalize(vector<T>* self);
    void push_back(vector<T>* self, T item);
    T& item(vector<T>* self, int index, T& default_value);
    bool equals(vector<T>* left, vector<T>* right);
    bool replace(vector<T>* self, int index, T value);
    int find(vector<T>* self, T& item, int default_value);
    int length(vector<T>* self);
    void reset(vector<T>* self);
    T& begin(vector<T>* self);
    T& next(vector<T>* self);
    bool end(vector<T>* self);

    list<T>*% to_list(vector<T>* self);
}

#define foreach(o1, o2) for(auto _obj = nomove (o2), auto o1 = _obj.begin(); !_obj.end(); o1 = _obj.next())
```

The & in the type name removes% from the generic type name. Even if T has a%, it is treated as a pointer. managed removes% from variables with%. The usage is as follows.

型名の&はジェネリクスの型名から%を消すものです。Tに%がついていてもポインタとして処理されます。managedは%がつけられた変数から%を取り除きます。

使い方は以下です。

```
auto v = new vector<int>.initialize();

v.push_back(1);
v.push_back(2);
v.push_back(3);

if(v.length() == 3 && v.item(0, -1) == 1 && v.item(1, -1) == 2 && v.item(2, -2) == 3 && v.item(10000, -1) == -1) {
    puts("OK");
}

foreach(it , v) {
    printf("%d\n", it);
}
```

-1 of item is the default value. If index is out of range, the default value is returned. foreach is a macro that accesses all elements. list is below. 

itemの-1はデフォルト値でもしindexが範囲外ならデフォルト値を返します。foreachは全ての要素にアクセスするマクロです。

listは以下です。

```
impl list <T>
{
    list<T>*% initialize(list<T>*% self);
    void finalize(list<T>* self);
    list<T>*% clone(list<T>* self);
    int length(list<T>* self);
    void push_back(list<T>* self, T item) ;
    T& item(list<T>* self, int position, T& default_value);
    void insert(list<T>* self, int position, T item);
    void reset(list<T>* self) ;
    void delete(list<T>* self, int head, int tail);
    void replace(list<T>* self, int position, T item);

    int find(list<T>* self, T& item, int default_value) ;
    list<T>*% sublist(list<T>* self, int begin, int tail) ;

    list<T>*% reverse(list<T>* self);
    list<T>*% merge_list(list<T>* left, list<T>* right, int (*compare)(T&,T&));
    list<T>*% merge_sort(list<T>* self, int (*compare)(T&,T&));
    list<T>*% sort(list<T>* self, int (*compare)(T&,T&));
    list<T>*% uniq(list<T>* self);
    bool equals(list<T>* left, list<T>* right);
    T& begin(list<T>* self);
    T& next(list<T>* self);
    bool end(list<T>* self);
}
```

Usage is almost the same as vector.

使い方はvectorとほぼ同じです。

```
auto l = new list<int>.initialize();

l.push_back(1);
l.push_back(2);
l.push_back(3);

if(l.length() == 3 && l.item(0, -1) == 1 && l.item(1, -1) == 2 && l.item(2, -1) == 3 && l.item(1000, -1) == -1) {
    puts("OK");
}

foreach(it, l) {
    printf("%d\n", it);
}
```

The difference from vector is that there is an insert for element insertion. insert is fast. Instead, item is slow. (Random access). foreach will not be too slow. Use sort as follows. 

vectorと違う点は要素の挿入のinsertがある点です。insertは高速です。その代わりitemは遅いです。（ランダムアクセス)。foreachはそれほど遅くないでしょう。

sortは以下のように使います。

```
int int::compare(int left, int right) {
    if(left < right) {
        return -1;
    }
    else if(left > right) {
        return 1;
    }
    else {
        return 0;
    }
}

int main(int argc, char** argv)
{
    auto l = new list<int>.initialize();

    l.push_back(7);
    l.push_back(1);
    l.push_back(2);

    auto l2 = l.sort(int_compare);

    if(l2.item(0, -1) == 1 && l2.item(1, -1) == 2 && l2.item(2, -1) == 7) {
        puts("OK");
    }
}
```

The map is below.

mapは以下です。

```
impl map <T, T2>
{
    map<T,T2>*% initialize(map<T,T2>*% self);
    T2& at(map<T, T2>* self, T& key, T2& default_value);
    void rehash(map<T,T2>* self) ;
    void insert(map<T,T2>* self, T key, T2 item) ;
    map<T, T2>*% clone(map<T, T2>* self);
    bool find(map<T, T2>* self, T& key);
    bool equals(map<T, T2>* left, map<T, T2>* right);
    int length(map<T, T2>* self);
    T& begin(map<T, T2>* self);
    T& next(map<T, T2>* self);
    bool end(map<T, T2>* self) ;
}
```

使い方は

Usage is bellow:

```
auto m = new map<char*, int>.initialize();

m.insert("AAA", 1);
m.insert("BBB", 2);
m.insert("CCC", 3);

if(m.length() == 3 && m.at("AAA", -1) == 1 && m.at("BBB", -1) == 2 && m.at("CCC", -1) == 3) {
    puts("OK");
}
```

It will be. There is also a tuple. It is defined as follows.

となります。

tupleもあります。以下のように定義されています。

```
struct tuple1<T>
{
    T v1;
};

impl tuple1 <T>
{
    tuple1<T>*% clone(tuple1<T>* self);
    void finalize(tuple1<T>* self)
    bool equals(tuple1<T>* left, tuple1<T>* right);
}

struct tuple2<T, T2>
{
    T v1;
    T2 v2;
};

impl tuple2 <T, T2>
{
    tuple2<T,T2>*% clone(tuple2<T, T2>* self);
    void finalize(tuple2<T, T2>* self);
    bool equals(tuple2<T, T2>* left, tuple2<T, T2>* right);
}

struct tuple3<T, T2, T3>
{
    T v1;
    T2 v2;
    T3 v3;
};

impl tuple3 <T, T2, T3>
{
    tuple3<T,T2, T3>*% clone(tuple3<T, T2, T3>* self);
    void finalize(tuple3<T, T2, T3>* self)
    bool equals(tuple3<T, T2, T3>* left, tuple3<T, T2, T3>* right);
}

struct tuple4<T, T2, T3, T4>
{
    T v1;
    T2 v2;
    T3 v3;
    T4 v3;
};

impl tuple4 <T, T2, T3, T4>
{
    tuple4<T,T2, T3, T4>*% clone(tuple4<T, T2, T3, T4>* self);
    void finalize(tuple4<T, T2, T3, T4>* self);
    bool equals(tuple4<T, T2, T3, T4>* left, tuple4<T, T2, T3, T4>* right);
}
```
5. Collection and heap system

All the elements added to the Collection are also released from memory and cloned on the collection side. When adding elements, do not add the heap managed by the variable table. This is because the heap managed by the variable table beneo-c2 double free because automatic free occurs when it exits the block and free also occurs on the collection side. For example:

Collectionに追加された要素は全てコレクション側でメモリの解放やcloneなども行われます。要素を追加する場合は変数テーブルで管理されたヒープを追加しないようにしてください。
変数テーブルで管理されたヒープはブロックから出たときに自動freeが起こりコレクション側でもfreeが起こるので、2重freeとなるためです。例えば以下のようにします。

```
auto l = new list<string>.initialzie();

auto str = string("ABC");

managed str;

l.push_back(str)
```

When it is managed str, str is no longer a heap managed by the variable table. The% mark disappears from the variable type. str is just char *. Or

managed strとされるとstrは変数テーブルで管理されるヒープでなくなります。変数の型に%マークがなくなります。strは単なるchar*となります。

もしくは

```
auto l = new list<tring>.initialize();

auto str = borrow string("ABC");

l.push_back(str);
```

You can also do it. borrow removes the% mark on the heap. str is treated as just char *. In both cases str is freed when auto l is freed. Another way is to clone the variables in the variable table. Since two heaps are created, one is freed in the variable table and the other is freed in the Collection.

としてもいいでしょう。borrowはヒープの%マークを消します。strは単なるchar*として扱われます。
どちらの場合もauto lがfreeされるときにstrは一緒にfreeされます。

もう一つの方法としては変数テーブルの変数をcloneすることです。２つのヒープが生成されるため、一つは変数テーブルでfreeされて、もう一つはCollectionの中でfreeされます。

```
auto l = new list<string>.initialize();

auto str = string("ABC");

l.push_back(clone str);
```

This may be the easiest.

これが一番簡単かもしれません。

6. lambda

```
auto fun = int lambda(int x, int y) { return x + y; }

if(fun(1, 2) == 3) {
    puts("OK");
}
```

lambdas don't have access to variables in the parent stack.

lambdaは親のスタックの変数にはアクセスできません。

```
auto a = 1;

auto fun = int lambda(int x, int y) { return x + y + a; }
```

The above code will result in a compilation error.

上記のコードはコンパイルエラーとなります。

neo-c2 can access the variables of parent stack frame.

親のスタックの変数にアクセスできるようになりました。

```
int main(int argc, char** argv)
{
    int a;
    auto fun = int lambda(__current__* parent, int b, int c) {
        *parent.a = 4;
        return (*parent.a + b + c);
    }

    printf("%d\n", fun(__stack__, 1, 2));
    printf("a %d\n", a);
}
```

__current__ defines a structure that contains pointers to all variables in the current stack frame. __stack__ returns the pointer of the structure in which the pointer of the stack frame is assigned to the structure that stores the pointers of all variables of the current stack frame. In this case, the structure struct {int * a, int * argc, char *** argv}; is defined.

__current__は現在のスタックフレームのすべての変数のポインタを格納している構造体を定義します。
__stack__は現在のスタックフレームのすべての変数のポインタを格納している構造体にスタックフレームのポインタを代入した構造体のポインタを返します。
この場合はstruct { int* a, int* argc, char*** argv };という構造体が定義されます。

7. buffer

The definition is as follows.

定義は以下です。

```
buffer*% buffer_initialize(buffer*% self);
void buffer_finalize(buffer* self);
int buffer_length(buffer* self) 
void buffer_append(buffer* self, char* mem, size_t size);
void buffer_append_char(buffer* self, char c);
void buffer_append_str(buffer* self, char* str);
void buffer_append_nullterminated_str(buffer* self, char* str);
string buffer_to_string(buffer* self);
void buffer_append_int(buffer* self, int value) ;
void buffer_append_long(buffer* self, long value) ;
void buffer_append_short(buffer* self, short value);
void buffer_alignment(buffer* self);
int buffer_compare(buffer* left, buffer* right);
```

使い方は以下です。

Usage is bellow:

```
buffer*% b1 = new buffer.initialize();

b1.append_str("ABC");
b1.append_str("DEF");

if(strcmp(b1.to_string(), "ABCDEF") == 0) {
    puts("OK");
}
```

7. mixin-layers system

mixin-layersとはレイヤーを重ねるようにアプリケーションを作るプログラミング技法で、仕組み的には関数の上書きを許して、上書きされた関数を上書きした関数から呼び出せるというものです。

Mixin-layers is a programming technique that creates an application so that layers are layered. The mechanism is to allow overwriting of a function and call the overwritten function from the overwritten function.

```
#include <stdio.h>

int fun(char* str);
override int fun(char* str);
override int fun(char* str);

int fun(char* str) version 1
{
    puts(str);
    return 1;
}

int fun(char* str) version 2
{
    int n = inherit(str);

    return n + 1;
}

int fun(char* str)
{
    int n = inherit(str);

    return n + 1;
}

int main()
{
    if(fun("HELLO MIXIN-LAYERS") == 3) {
        puts("OK");
    }

    return 0;
}
```

7. Parallel Processing

It can be executed in parallel with the come function name.

come 関数名で並列実行できます。

```
void fun(int n) 
{
    puts("HELLO PARALLEL WORLD");
    printf("%d\n", n);
}

int main()
{
    come fun(123);

    come join;

    return 0;
}
```

Channels add @ to the variable name.

チャネルは変数名に@をつけます。

```
void fun(int@ n)
{
    @n = 123;
}

int main()
{
    int@ m;
    come fun(m);

    printf("%d\n", @m);

    come join;

    return 0;
}
```

@mはfunの@n = 123が実行されるまでブロックされます。

複数のチャネルを同時に待つにはselectを使います。selectはブロックします。

@m is blocked until @ n = 123 of fun is executed. 
Use select to wait for multiple channels at the same time. select blocks.

```
void fun(int@ n)
{
    sleep(1);
    @n = 123;
}

void fun2(int@ m)
{
    sleep(2);
    @m = 234;
}

int main()
{
    int@ n;
    int@ m 

    come fun(n);
    come fun(m);

    while(true) {
        come select {
            n {
                printf("n %d\n", @n);
            }

            m {
                printf("m %d\n", @m);
            }
        }
    }

    come join;

    return 0;
}
```

polling select

```
void fun(int@ n)
{
    sleep(1);
    @n = 123;
}

void fun2(int@ m)
{
    sleep(2);
    @m = 234;
}

int main()
{
    int@ n;
    int@ m 

    come fun(n);
    come fun(m);

    while(true) {
        come pselect {
            n {
                printf("n %d\n", @n);
            }

            m {
                printf("m %d\n", @m);
            }

            default {
                puts("waiting....");
            }
        }
    }

    come join;

    return 0;
}
```

この機能を使ったときはリンクするときに-lpthreadしてください。

Please link with -lpthread using this functions.

8. Annotation

```
int fun(bool flag) 
{
    if(flag) {
        puts("TRUE");
    }
    else {
        puts("FALSE");
    }
}

int main()
{
    fun(false`flag);

    return 0;
}
```

`[a-zA-Z][a-zA-Z_0-9]* is a comment of expression.

8. Reflection

```
> vim a.c
struct sB {
    int a;
    char* b;
    struct sB* c;
};

int main() {
    sB b;
    b;
> neo-c2 type a.c
struct sB
#0 int a
#1 char* b
#2 struct sB*
```

neo-c2 type file name outputs the type of last expression and the type inner contents. It's useful for reflection. You will make a program output a program with any script languaged or neo-c2 its self.

neo-c2 type ファイル名で最後の式の型とその内容を出力することができます。これはリフレクションで便利です。プログラムを生成するプログラムを任意のスクリプト言語やneo-c2自身で作ることができるでしょう。

```
> vim a.c
int gGlobal1;
int gGlobal2;
> neo-c2 global a.c
gGlobal1 int
gGlobal2 int
```

```
> vim a.c
int fun(int a, int b)
{
    return a + b;
}

int fun2()
{
    return 123;
}
> neo-c2 function a.c
fun extern 0 var args 0 gnerics function 0 num params 2
a int
b int
result type int
fun2 extern 0 var args 0 gnerics function 0 num params 0
result type int
```

```
> vim a.c
struct sA 
{
    int a;
    int b;
};

enum eEnumA { kA, kB };
> neo-c2 class a.c
struct sA
#0 int a
#1 int b
enum eEnumA
kA 0
kB 1
```

```
> vim a.c
typedef int tType;
typedef int tType2;
> neo-c2 typedef a.c
tType int
tType2 int
```

9. MACRO

~~~
```
ruby <<EOS
    puts("int gGlobal2;");
EOS
```
~~~

The output of the enclosed code is pasted into the source code. With this and reflection, you'll be able to generate code with reflection at compile time.

囲まれたコードの出力がソースコードに貼り付けます。これとリフレクションを使えばコンパイルタイムにリフレクションでコードを生成できるでしょう。

Do not expand macros with the -n option.

-nオプションを使うとマクロを展開しません。

Compile Time Reflection and code generation is below:

~~~
> vim g.c
int gGlobal;


```
ruby <<EOS
    type = "`./neo-c2 -n global $SOURCE_NAME | grep gGlobal`".split()[1];
    puts(type + " gGlobal2;");
EOS
```
> neo-c2 global g.c
gGlobal int
gGlobal2 int
~~~

SOURCE_NAMEという環境変数にコンパイル中のソースファイル名が入ってます。

10. Method block

```
void times(int n, void* parent, void (*fun)(void* parent))
{
    int i;
    for(i=0; i<n; i++) {
        fun(parent);
    }
}

int main(int argc, char** argv)
{
    int a = 1;

    times(3, __stack__, void lambda(__current__* parent) {
        puts("HELLO LAMBDA");
        printf("a %d\n", *parent.a);
    });

    times(3) {
        puts("HELLO METHOD BLOCK");
        printf("a %d\n", *parent.a);
    }
}
```

__current__ defines a structure that contains pointers to all variables in the current stack frame. __stack__ returns the pointer of the structure in which the pointer of the stack frame is assigned to the structure that stores the pointers of all variables of the current stack frame. In this case, the structure struct {int * a, int * argc, char *** argv}; is defined.

__current__は現在のスタックフレームのすべての変数のポインタを格納している構造体を定義します。
__stack__は現在のスタックフレームのすべての変数のポインタを格納している構造体にスタックフレームのポインタを代入した構造体のポインタを返します。
この場合はstruct { int* a, int* argc, char*** argv };という構造体が定義されます。

The method block arguments are assigned to the structure parent for access to the parent stack, and the subsequent arguments are assigned to the variables it, it2, it3, ....

メソッドブロックの引数は親スタックへのアクセスはparentという構造体、その後の引数はit, it2, it3,... という変数に代入されます。

```
static int int::expect(int self, void* parent, void (*block)(void* parent))
{
    if(self < 0) {
        block(parent);
    }

    return self;
}

static void int::times(int self, void* parent, void (*block)(void* parent))
{
    int i;
    for(i=0; i<self; i++) {
        block(parent);
    }
}

impl list<T>
{
    list<T>*% filter(list<T>* self, void* parent, bool (*block)(void*, T&));
    list<T>* each(list<T>* self, void* parent, void (*block_)(void*, T&,int,bool*));
}
```

```
int fd = open("ABC", O_RDONLY).expect {
    fprintf(stderr, "can't open ABC");
    exit(1);
}

3.times {
    puts("HELLO METHOD BLOCK");
}

auto li = new list<int>.initialize();

li.push_back(1);
li.push_back(2);
li.push_back(3);

int a = 1;

li.filter { return it > 1; }.each {
    (*parent.a) = 2;
    printf("%d\n", it, + *parent.a);
}
// result is 4\n5\n

printf("a %d\n", a);
// result is a 2
```

ただし、親のスタックの変数が配列の場合先頭アドレスが渡されます。

However, if the variable on the parent stack is an array, the start address is passed.

```
    auto li = new list<char>.initialize();
    
    li.push_back("AAA");
    li.push_back("BBB");
    
    char buf[128];
    
    strncpy(buf, "CCC", 128);
    
    li.each {
        printf("%s %s\n", it, parent.buf);
    }
    /// result is AAA CCC\nBBB CCC\n
```


11. Method Generics

```
struct sStruct<T>
{
    T a;
    T b;
};

impl sStruct<T>
{
    void fun(sStruct<T>* self, T xxx, void* parent, void (*fun)(void* parent, T a)) {
        fun(parent, xxx);
    }

    template <R> R fun2(sStruct<T>* self, R a, R b) {
        return a + b;
    }
}

template <R> R fun(R a, int b)
{
    return a + b;
}

int main() 
{
    sStruct<int>*% data = new sStruct<int>;

    xassert("method generics test", fun(1,2) == 3);
    xassert("method generics test", data.fun2(1,2) == 3);

    return 0;
}
```

```
impl list<T> {
    template <R> list<R>*% map(list<T>* self, void* parent, R (*block)(void*, T&))
    {
        auto result = new list<R>.initialize();

        list_item<T>?* it = self.head;
        while(it != null) {
            result.push_back(block(parent, it.item));

            it = it.next;
        }

        return result;
    }
}

int main()
{
    auto list3 = new list<char*>.initialize();

    list3.push_back("1");
    list3.push_back("2");
    list3.push_back("3");

    auto list4 = list3.map int { return atoi(it); }

    xassert("map test", list4.item(0, -1) == 1 && list4.item(1, -1) == 2 && list4.item(2, -1) == 3);

    return 0;
}
```

# String libraries

```
typedef wchar_t*% wstring;

struct regex_struct 
{
    char str[128];
    pcre* regex;

    bool ignore_case;
    bool multiline;
    bool global;
    bool extended;
    bool dotall;
    bool anchored;
    bool dollar_endonly;
    bool ungreedy;

    int options;

    pcre* re;
};

typedef regex_struct*% nregex;

regex_struct*% regex(char* str, bool ignore_case, bool multiline, bool global, bool extended, bool dotall, bool anchored, bool dollar_endonly, bool ungreedy);
bool char::match(char* self, regex_struct* reg, list<string>?* group_strings);
int char::index(char* str, char* search_str, int default_value);
int char::rindex(char* str, char* search_str, int default_value);
int char::index_regex(char* self, regex_struct* reg, int default_value);
int char::rindex_regex(char* self, regex_struct* reg, int default_value);
void char::replace(char* self, int index, char c);
string char::multiply(char* str, int n);
string char::sub(char* self, regex_struct* reg, char* replace, list<string>?* group_strings);
list<string>*% char::scan(char* self, regex_struct* reg);
list<string>*% char::split(char* self, regex_struct* reg);
list<string>*% char::split_char(string& self, char c) ;
nregex char::to_regex(char* self) ;
string char::printable(char* str);
char* char::delete(char* str, int head, int tail) ;
string int::to_string(wchar_t* wstr);
wstring wstring(char* str);
wstring char::to_wstring(char* str);
wstring int::substring(wchar_t* str, int head, int tail);
int int::length(wchar_t* str);
wchar_t* int::delete(wchar_t* str, int head, int tail) ;
int int::index(wchar_t* str, wchar_t* search_str, int default_value);
int int::rindex(wchar_t* str, wchar_t* search_str, int default_value);
wstring int::reverse(whar_t* str) ;
wstring int::multiply(wchar_t* str, int n);
```

sample

```
#include <come-pcre.h>

int main()
{
    xassert("char_match test", "ABC".match("A".to_regex(), null));
    xassert("char_index test", "ABC".index("B", -1) == 1);
    xassert("char_rindex test", "ABCABC".rindex("B", -1) == 4);
    xassert("char_index_regex", "ABC".index_regex("B".to_regex(), -1) == 1);
    xassert("char_rindex_regex", "ABCABC".rindex_regex("B".to_regex(), -1) == 4);

    string str = string("ABC");

    str.replace(1, 'C');

    xassert("char_replace", strcmp(str, "ACC") == 0);
    xassert("char_multiply", strcmp(string("ABC").multiply(2), "ABCABC") == 0);

    xassert("char_sub", strcmp("ABC".sub("B".to_regex(), "C", null), "ACC") == 0);

    auto li = "ABC".scan(".".to_regex());

    xassert("char_scan", strcmp(li.item(0, null), "A") == 0 && strcmp(li.item(1, null), "B") == 0 && strcmp(li.item(2, null), "C") == 0);

    auto li2 = "A,B,C".split(",".to_regex());

    xassert("char_split", strcmp(li2.item(0, null), "A") == 0 && strcmp(li2.item(1, null), "B") == 0 && strcmp(li2.item(2, null), "C") == 0);

    auto li3 = "A,B,C".split_char(',');

    xassert("char_split_char", strcmp(li3.item(0, null), "A") == 0 && strcmp(li3.item(1, null), "B") == 0 && strcmp(li3.item(2, null), "C") == 0);

    xassert("char_delete", string("ABC").delete(0,1).equals("BC"));

    xassert("wchar_substring", wcscmp(wstring("ABC").substring(0,1), wstring("A")) == 0);

    return 0;
}
```

If you use these functions, use #include <come-pcre.h>.
When linking object files, append -lpcre option for linker.

もしこれらの関数を使うときは#include <come-pcre.h>をつけてください。
リンクするときに-lpcreを付けてください。

# Macro

```
macro vector
{
    export VAR_NAME=$PARAMS
    cat <<EOS2
auto $VAR_NAME = new vector<int>.initialize();

$VAR_NAME.push_back(1);
$VAR_NAME.push_back(2);
$VAR_NAME.push_back(3);
EOS2
}

int main()
{
    vector!(v);

    xassert("macro test", v.item(0, -1) == 1 && v.item(1, -1) == 2 && v.item(2, -1) == 3);

    return 0;
}
```

# defer

```
inline int fun()
{
    defer puts("fun finish");

    puts("in fun");

    return 123;
}

int fun2()
{
    defer puts("fun2 finish");

    puts("in fun2");

    if(true) {
        return 123;
    }
}

int main()
{
    defer puts("main FINISH");

puts("before fun");
    fun();

puts("before fun2");
    fun2();
puts("after fun2");

    return 0;
}
```

result is below:

```
before fun
in fun
before fun2
in fun2
fun2 finish
after fun2
main FINISH
fun finish
```


