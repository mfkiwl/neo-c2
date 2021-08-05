# comelang

come together!

C extension compiler language. Some compatibility for C language.

This language is self-hosted.

version 1.1.2

```
#include <come.h>

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

    return 0;
}
```

1. It is compatible with C language to some extent. The C preprocessor also works.

2. It has its own heap system. It has an automatic free of the temporarily generated heap (rvalue) and an automatic free of the heap assigned to the variable.

3. It has Generics, inline function, debug info (-g option), and lambda.

4. The library is written in come.h and you don't need to link any library. The library is minimal and keeps learning costs down. It has a collection library> and a string library.

5. It has a mixin-layers system. You can implement your application in layers. Each layer is complete and useful for debugging and porting. A vi clone called vico is implemented as an editor implemented in mixin-layers. Please refer to it because it is in a directory called vico.

1. C言語とある程度互換性があります。Cプリプロセッサーも動きます。

2. 独自のヒープシステムを備えます。一時的に生成されたヒープ（右辺値）の自動freeと変数に代入されたヒープの自動freeを備えます。

3. Generics, inline function, debug info(-g option), lambdaを備えます。

4. ライブラリはcome.hに書かれてあり、何もライブラリをリンクする必要はありません。ライブラリは最小限となっており学習コストを抑えています。コレクションライブラリと文字列ライブラリを備えます。

5. mixin-layersシステムを備えます。アプリケーションをレイヤーを重ねるように実装できます。各レイヤーは完結しており、デバッグや移植作業でも有効です。mixin-layersで実装されたエディッタとしてvicoというviクローンを実装しています。vicoというディレクトリの中に入っているので参考にしてください。

For PC, WSL, Raspberry PI OS and iSH(iPhone)

```
sudo apt-get install clang make autoconf llvm-dev git gdb valgrind ctags libxml2-dev g++ gcc 

git clone https://github.com/ab25cq/comelang

cd comelang

./configure --with-optimize
make
sudo make install
make test

or 

bash all_build.sh
```

Without self-host. 

```
sudo apt-get install clang make autoconf llvm-dev git gdb valgrind ctags libxml2-dev g++ gcc 

git clone https://github.com/ab25cq/comelang

cd comelang

./configure --with-optimize
make no-self-host
sudo make install
make test

or 

bash no_self_host.sh
```

Install to home directory. For termux(android), and MacOS(INTEL)

```
sudo apt-get install clang make autoconf llvm-dev git gdb valgrind ctags libxml2-dev g++ gcc 

git clone https://github.com/ab25cq/comelang

cd comelang

./configure --with-optimize --prefix=$HOME
make
sudo make install
make test

or 

bash home_build.sh
```

1. Language specifications

It is almost the same as C language. Since it is not POSIX compliant, it is not compatible with C language in every detail, but I think that anyone who can use C language can use it immediately. If you don't use the heap system and do #include <come.h>, you can just use it as a C compiler.

C言語とほぼ一緒です。POSIX準拠じゃないため、あまり細部までC言語とは互換性がありませんが、C言語を使える人ならすぐ使えると思います。
ヒープシステムを使わずに#include <come.h>をしなければ、単なるCコンパイラとして使えます。

2. HELLO WORLD

```
> vim a.c
#include <stdio.h>

int main()
{
    puts("HELLO WORLD");
    return 0;
}
> come a.c
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
> come a.c
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

4. Generics

Generics is a code generation method. I have implemented it, but basically I am making it for the collection library of the basic library. We do not recommend using Generics for your own application code. This is because the code becomes complicated. If you want to make your own library, you can use it. The vector is defined as follows.

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
    vector<T>*% initialize(vector<T>*% self) 
    {
        self.size = 16;
        self.len = 0;
        self.items = borrow new T[self.size];

        return self;
    }

    void finalize(vector<T>* self)
    {
        if(isheap(T)) {
            for(int i=0; i<self.len; i++) 
            {
                delete self.items[i];

            }
        }
        delete self.items;
    }
    
    void push_back(vector<T>* self, T item) {
        managed item;

        if(self.len == self.size) {
            auto new_size = self.size * 2;
            auto items = self.items;

            self.items = calloc(1, sizeof(T)*new_size);

            int i;
            for(i=0; i<self.size; i++) {
                self.items[i] = items[i];
            }

            self.size = new_size;

            delete items;
        }

        self.items[self.len] = item;
        self.len++;
    }

    T& item(vector<T>* self, int index, T& default_value) 
    {
        if(index < 0) {
            index += self.len;
        }

        if(index >= 0 && index < self.len)
        {
            return self.items[index];
        }

        return default_value;
    }

    bool equals(vector<T>* left, vector<T>* right)
    {
        if(left.len != right.len) {
            return false;
        }

        for(int i=0; i<left.len; i++) {
            if(!(left.items[i].equals(right.items[i])))
            {
                return false;
            }
        }

        return true;
    }

    bool replace(vector<T>* self, int index, T value) 
    {
        if(index < 0) {
            index += self.len;
        }

        if(index >= 0 && index < self.len)
        {
            if(isheap(T)) {
                delete self.items[index];
            }

            self.items[index] = value;

            return true;
        }

        return false;
    }

    int find(vector<T>* self, T& item, int default_value) {
        int it2 = 0;
        foreach(it, self) {
            if(it.equals(item)) {
                return it2;
            }
            it2++;
        }

        return default_value;
    }

    int length(vector<T>* self)
    {
        return self.len;
    }

    void reset(vector<T>* self) {
        self.len = 0;
    }

    T& begin(vector<T>* self) {
        self.it = 0;

        return self.item(0, NULL);
    }

    T& next(vector<T>* self) {
        self.it++;

        return self.item(self.it, NULL);
    }

    bool end(vector<T>* self) {
        return self.it >= self.len;
    }

    list<T>*% to_list(vector<T>* self) {
        auto result = new list<T>.initialize();
        
        foreach(it, self) {
            if(isheap(T)) {
                result.push_back(clone it);
            }
            else {
                result.push_back(dummy_heap it);
            }
        }
        
        return result;
    }
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
struct list_item<T>
{
    T& item;
    list_item<T>* prev;
    list_item<T>* next;
};

struct list<T>
{
    list_item<T>* head;
    list_item<T>* tail;
    int len;

    list_item<T>* it;
};

/// list ///
impl list <T>
{
    list<T>*% initialize(list<T>*% self) {
        self.head = null;
        self.tail = null;
        self.len = 0;

        return self;
    }

    void finalize(list<T>* self) {
        list_item<T>* it = self->head;
        while(it != null) {
            if(isheap(T)) {
                delete it.item;
            }
            auto prev_it = it;
            it = it.next;
            delete prev_it;
        }
    }
    list<T>*% clone(list<T>* self) {
        auto result = new list<T>.initialize();

        list_item<T>* it = self.head;
        while(it != null) {
            if(isheap(T)) {
                result.push_back(clone it.item);
            }
            else {
                result.push_back(dummy_heap it.item);
            }

            it = it.next;
        }

        return result;
    }

    int length(list<T>* self)
    {
        return self.len;
    }
    void push_back(list<T>* self, T item) 
    {
        managed item;

        if(self.len == 0) {
            list_item<T>* litem = borrow new list_item<T>;

            litem.prev = null;
            litem.next = null;
            litem.item = item;
            
            self.tail = litem;
            self.head = litem;
        }
        else if(self.len == 1) {
            list_item<T>* litem = borrow new list_item<T>;

            litem.prev = self.head;
            litem.next = null;
            litem.item = item;
            
            self.tail = litem;
            self.head.next = litem;
        }
        else {
            list_item<T>* litem = borrow new list_item<T>;

            litem.prev = self.tail;
            litem.next = null;
            litem.item = item;
            
            self.tail.next = litem;
            self.tail = litem;
        }

        self.len++;
    }
    
    T& item(list<T>* self, int position, T& default_value) 
    {
        if(position < 0) {
            position += self.len;
        }

        list_item<T>* it = self.head;
        auto i = 0;
        while(it != null) {
            if(position == i) {
                return it.item;
            }
            it = it.next;
            i++;
        };

        return default_value;
    }

    void insert(list<T>* self, int position, T item)
    {
        if(position < 0) {
            position += self.len + 1;
        }
        if(position < 0) {
            position = 0;
        }
        if(self.len == 0 || position >= self.len) 
        {
            self.push_back(item);
            return;
        }

        managed item;

        if(position == 0) {
            list_item<T>* litem = borrow new list_item<T>;

            litem.prev = null;
            litem.next = self.head;
            litem.item = item;
            
            self.head.prev = litem;
            self.head = litem;

            self.len++;
        }
        else if(self.len == 1) {
            auto litem = borrow new list_item<T>;

            litem.prev = self.head;
            litem.next = self.tail;
            litem.item = item;
            
            self.tail.prev = litem;
            self.head.next = litem;

            self.len++;
        }
        else {
            list_item<T>* it = self.head;
            auto i = 0;
            while(it != null) {
                if(position == i) {
                    list_item<T>* litem = borrow new list_item<T>;

                    litem.prev = it.prev;
                    litem.next = it;
                    litem.item = item;

                    it.prev.next = litem;
                    it.prev = litem;

                    self.len++;
                }

                it = it.next;
                i++;
            }
        }
    }

    void reset(list<T>* self) {
        list_item<T>* it = self.head;
        while(it != null) {
            if(isheap(T)) {
                delete it.item;
            }
            auto prev_it = it;
            it = it.next;
            delete prev_it;
        }

        self.head = null;
        self.tail = null;

        self.len = 0;
    }

    void delete(list<T>* self, int head, int tail)
    {
        if(head < 0) {
            head += self.len;
        }
        if(tail < 0) {
            tail += self.len + 1;
        }

        if(head > tail) {
            int tmp = tail;
            tail = head;
            head = tmp;
        }

        if(head < 0) {
            head = 0;
        }

        if(tail > self.len) {
            tail = self.len;
        }

        if(head == tail) {
            return;
        }

        if(head == 0 && tail == self.len) 
        {
            self.reset();
        }
        else if(head == 0) {
            list_item<T>* it = self.head;
            auto i = 0;
            while(it != null) {
                if(i < tail) {
                    if(isheap(T)) {
                        delete it.item;
                    }
                    list_item<T>* prev_it = it;

                    it = it.next;
                    i++;

                    delete prev_it;

                    self.len--;
                }
                else if(i == tail) {
                    self.head = it;
                    self.head.prev = null;
                    break;
                }
                else {
                    it = it.next;
                    i++;
                }
            }
        }
        else if(tail == self.len) {
            list_item<T>* it = self.head;
            auto i = 0;
            while(it != null) {
                if(i == head) {
                    self.tail = it.prev;
                    self.tail.next = null;
                }

                if(i >= head) {
                    if(isheap(T)) {
                        delete it.item;
                    }
                    list_item<T>* prev_it = it;

                    it = it.next;
                    i++;

                    delete prev_it;

                    self.len--;
                }
                else {
                    it = it.next;
                    i++;
                }
            }
        }
        else {
            list_item<T>* it = self.head;

            list_item<T>* head_prev_it = null;
            list_item<T>* tail_it = null;


            auto i = 0;
            while(it != null) {
                if(i == head) {
                    head_prev_it = it.prev;
                }
                if(i == tail) {
                    tail_it = it;
                }

                if(i >= head && i < tail) 
                {
                    if(isheap(T)) {
                        delete it.item;
                    }
                    list_item<T>* prev_it = it;

                    it = it.next;
                    i++;

                    delete prev_it;

                    self.len--;
                }
                else {
                    it = it.next;
                    i++;
                }
            }

            if(head_prev_it != null) {
                head_prev_it.next = tail_it;
            }
            if(tail_it != null) {
                tail_it.prev = head_prev_it;
            }
        }
    }

    void replace(list<T>* self, int position, T item)
    {
        managed item;

        if(position < 0) {
            position += self.len;
        }

        list_item<T>* it = self.head;
        auto i = 0;
        while(it != null) {
            if(position == i) {
                if(isheap(T)) {
                    delete it.item;
                }

                it.item = item;
                break;
            }
            it = it.next;
            i++;
        }
    }

    int find(list<T>* self, T& item, int default_value) {
        int it2 = 0;
        foreach(it, self) {
            if(it.equals(item)) {
                return it2;
            }
            it2++;
        }

        return default_value;
    }

    list<T>*% sublist(list<T>* self, int begin, int tail) {
        list<T>%* result = new list<T>.initialize();

        if(begin < 0) {
            begin += self.len;
        }

        if(tail < 0) {
            tail += self.len + 1;
        }

        if(begin < 0) {
            begin = 0;
        }

        if(tail >= self.len) {
            tail = self.len;
        }

        list_item<T>* it = self.head;
        auto i = 0;
        while(it != null) {
            if(i >= begin && i < tail) {
                if(isheap(T)) {
                    result.push_back(clone it.item);
                }
                else {
                    result.push_back(dummy_heap it.item);
                }
            }
            it = it.next;
            i++;
        };

        return result;
    }

    list<T>*% reverse(list<T>* self) {
        list<T>%* result = new list<T>.initialize();

        list_item<T>* it = self.tail;
        while(it != null) {
            if(isheap(T)) {
                result.push_back(clone it.item);
            }
            else {
                result.push_back(dummy_heap it.item);
            }
            it = it.prev;
        };

        return result;
    }

    list<T>*% merge_list(list<T>* left, list<T>* right, int (*compare)(T&,T&)) {
        auto result = new list<T>.initialize();

        list_item<T>*? it = left.head;
        list_item<T>*? it2= right.head;

        while(true) {
            if(it && it2) {
                if(it.item == null) {
                    it = it.next;
                }
                else if(it2.item == null) {
                    it2 = it2.next;
                }
                else if(compare(it.item, it2.item) <= 0) 
                {
                    if(isheap(T)) {
                        result.push_back(clone it.item);
                    }
                    else {
                        result.push_back(dummy_heap it.item);
                    }

                    it = it.next;
                }
                else {
                    if(isheap(T)) {
                        result.push_back(clone it2.item);
                    }
                    else {
                        result.push_back(dummy_heap it2.item);
                    }


                    it2 = it2.next;
                }
            }

            if(it == null) {
                if(it2 != null) {
                    while(it2 != null) {
                        if(isheap(T)) {
                            result.push_back(clone it2.item);
                        }
                        else {
                            result.push_back(dummy_heap it2.item);
                        }

                        it2 = it2.next;
                    }
                }
                break;
            }
            else if(it2 == null) {
                if(it != null) {
                    while(it != null) {
                        if(isheap(T)) {
                            result.push_back(clone it.item);
                        }
                        else {
                            result.push_back(dummy_heap it.item);
                        }

                        it = it.next;
                    }
                }
                break;
            }
        }

        return result;
    }
    list<T>*% merge_sort(list<T>* self, int (*compare)(T&,T&)) {
        if(self.head == null) {
            return clone self;
        }
        if(self.head.next == null) {
            return clone self;
        }

        auto list1 = new list<T>.initialize();
        auto list2 = new list<T>.initialize();

        list_item<T>* it = self.head;

        while(true) {
            if(isheap(T)) {
                list1.push_back(clone it.item);
            }
            else {
                list1.push_back(dummy_heap it.item);
            }

            if(isheap(T)) {
                list2.push_back(clone it.next.item);
            }
            else {
                list2.push_back(dummy_heap it.next.item);
            }

            if(it.next.next == null) {
                break;
            }

            it = it.next.next;

            if(it.next == null) {
                if(isheap(T)) {
                    list1.push_back(clone it.item);
                }
                else {
                    list1.push_back(dummy_heap it.item);
                }
                break;
            }
        }

        return list1.merge_sort(compare).merge_list( list2.merge_sort(compare), compare);
    }
    list<T>*% sort(list<T>* self, int (*compare)(T&,T&)) {
        return self.merge_sort(compare);
    }

    list<T>*% uniq(list<T>* self) {
        list<T>*% result = new list<T>.initialize();

        if(self.length() > 0) {
            T& item_before = self.item(0, null);

            if(isheap(T)) {
                result.push_back(clone item_before);
            }
            else {
                result.push_back(dummy_heap item_before);
            }

            foearch(it, self.sublist(1,-1)) {
                if(!it.equals(item_before)) {
                    if(isheap(T)) {
                        result.push_back(clone it);
                    }
                    else {
                        result.push_back(dummy_heap it);
                    }
                }

                item_before = it;
            }
        }


    bool equals(list<T>* left, list<T>* right)
    {
        if(left.len != right.len) {
            return false;
        }

        list_item<T>* it = left.head;
        list_item<T>* it2 = right.head;

        while(it != null) {
            if(!it.item.equals(it2.item)) {
                return false;
            }

            it = it.next;
            it2 = it2.next;
        }

        return true;
    }

    T& begin(list<T>* self) {
        self.it = self.head;

        if(self.it) {
            return self.it.item;
        }
        else {
            return NULL;
        }

    }

    T& next(list<T>* self) {
        self.it = self.it.next;

        if(self.it) {
            return self.it.item;
        }
        else {
            return NULL;
        }
    }

    bool end(list<T>* self) {
        return self.it == null;
    }
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
struct map<T, T2>
{
    T&* keys;
    bool* item_existance;
    T2&* items;
    int size;
    int len;

    int it;
};

#define MAP_TABLE_DEFAULT_SIZE 128

impl map <T, T2>
{
    map<T,T2>*% initialize(map<T,T2>*% self) {
        self.keys = borrow new T[MAP_TABLE_DEFAULT_SIZE];
        self.items = borrow new T2[MAP_TABLE_DEFAULT_SIZE];
        self.item_existance = borrow new bool[MAP_TABLE_DEFAULT_SIZE];

        for(int i=0; i<MAP_TABLE_DEFAULT_SIZE; i++)
        {
            self.item_existance[i] = false;
        }

        self.size = MAP_TABLE_DEFAULT_SIZE;
        self.len = 0;

        self.it = 0;

        return self;
    }

    void finalize(map<T,T2>* self) {
        for(int i=0; i<self.size; i++) {
            if(self.item_existance[i]) {
                if(isheap(T2)) {
                    delete self.items[i];
                }
            }
        }
        delete self.items;

        for(int i=0; i<self.size; i++) {
            if(self.item_existance[i]) {
                if(isheap(T)) {
                    delete self.keys[i];
                }
            }
        }
        delete self.keys;

        delete self.item_existance;
    }

    T2& at(map<T, T2>* self, T& key, T2& default_value) 
    {
        int hash = ((T)key).get_hash_key() % self.size;
        int it = hash;

        while(true) {
            if(self.item_existance[it])
            {
                if(self.keys[it].equals(key))
                {
                    return self.items[it];
                }

                it++;

                if(it >= self.size) {
                    it = 0;
                }
                else if(it == hash) {
                    return default_value;
                }
            }
            else {
                return default_value;
            }
        }

        return default_value;
    }

    void rehash(map<T,T2>* self) {
        int size = self.size * 3;
        T&* keys = borrow new T[size];
        T2&* items = borrow new T2[size];
        bool* item_existance = borrow new bool[size];

        int len = 0;

        for(auto it = self.begin(); !self.end(); it = self.next()) {
            T2& it2 = self.at(it, null);
            int hash = it.get_hash_key() % size;
            int n = hash;

            while(true) {
                if(item_existance[n])
                {
                    n++;

                    if(n >= size) {
                        n = 0;
                    }
                    else if(n == hash) {
                        fprintf(stderr, "unexpected error in map.rehash(1)\n");
                        exit(2);
                    }
                }
                else {
                    item_existance[n] = true;
                    keys[n] = it;
                    items[n] = self.at(it, null);

                    len++;
                    break;
                }
            }
        }

        delete self.items;
        delete self.item_existance;
        delete self.keys;

        self.keys = keys;
        self.items = items;
        self.item_existance = item_existance;

        self.size = size;
        self.len = len;
    }

    void insert(map<T,T2>* self, T key, T2 item) 
    {
        managed key;
        managed item;

        if(self.len*2 >= self.size) {
            self.rehash();
        }

        int hash = key.get_hash_key() % self.size;
        int it = hash;

        while(true) {
            if(self.item_existance[it])
            {
                if(self.keys[it].equals(key)) 
                {
                    if(isheap(T)) {
                        delete dummy_heap self.keys[it];
                    }
                    if(isheap(T2)) {
                        delete dummy_heap self.items[it];
                    }
                    self.keys[it] = key;
                    self.items[it] = item;

                    break;
                }

                it++;

                if(it >= self.size) {
                    it = 0;
                }
                else if(it == hash) {
                    fprintf(stderr, "unexpected error in map.insert\n");
                    exit(2);
                }
            }
            else {
                self.item_existance[it] = true;
                self.keys[it] = key;
                self.items[it] = item;

                self.len++;

                break;
            }
        }
    }

    map<T, T2>*% clone(map<T, T2>* self)
    {
        auto result = new map<T,T2>.initialize();

        for(auto it = self.begin(); !self.end(); it = self.next()) {
            T2& default_value;
            auto it2 = self.at(it, default_value);

            if(isheap(T)) {
                if(isheap(T2)) {
                    result.insert(clone it, clone it2);
                }
                else {
                    result.insert(clone it, dummy_heap it2);
                }
            }
            else {
                if(isheap(T2)) {
                    result.insert(dummy_heap it, clone it2);
                }
                else {
                    result.insert(dummy_heap it, dummy_heap it2);
                }
            }
        }

        return result;
    }

    bool find(map<T, T2>* self, T& key) {
        int hash = ((T)key).get_hash_key() % self.size;
        int it = hash;

        while(true) {
            if(self.item_existance[it])
            {
                if(self.keys[it].equals(key))
                {
                    return true;
                }

                it++;

                if(it >= self.size) {
                    it = 0;
                }
                else if(it == hash) {
                    return false;
                }
            }
            else {
                return false;
            }
        }

        return false;
    }

    bool equals(map<T, T2>* left, map<T, T2>* right)
    {
        if(left.len != right.len) {
            return false;
        }

        bool result = true;
        foreach(it, left) {
            T2& it2 = left.at(it, null);

            if(right.find(it)) {
                T2& default_value;
                T2& item = right.at(it, default_value);
                if(!it2.equals(item)) {
                    result = false;
                }
            }
            else {
                result = false;
            }
        }

        return result;
    }

    int length(map<T, T2>* self) {
        return self.len;
    }

    T& begin(map<T, T2>* self) {
        self.it = 0;
        while(self.it < self.size) {
            if(self.item_existance[self.it]) {
                return self.keys[self.it++];
            }
            self.it++;
        }

        return null;
    }

    T& next(map<T, T2>* self) {
        while(self.it < self.size) {
            if(self.item_existance[self.it]) {
                return self.keys[self.it++];
            }
            self.it++;
        }

        return null;
    }

    bool end(map<T, T2>* self) {
        int count = 0;
        for(int i=self.it-1; i<self.size; i++) {
            if(self.item_existance[i]) {
                count ++;
            }
        }

        if(count == 0) {
            return true;
        }
        else {
            return false;
        }
    }
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
    tuple1<T>*% clone(tuple1<T>* self)
    {
        tuple1<T>*% result = new tuple1<T>;

        result.v1 = clone self.v1;

        return result;
    }

    void finalize(tuple1<T>* self)
    {
        if(isheap(T)) {
            delete self.v1;
        }
    }
    bool equals(tuple1<T>* left, tuple1<T>* right)
    {
        if(!left.v1.equals(right.v1)) {
            return false;
        }

        return true;
    }
}

struct tuple2<T, T2>
{
    T v1;
    T2 v2;
};

impl tuple2 <T, T2>
{
    tuple2<T,T2>*% clone(tuple2<T, T2>* self)
    {
        tuple2<T,T2>*% result = new tuple2<T, T2>;

        result.v1 = clone self.v1;
        result.v2 = clone self.v2;

        return result;
    }

    void finalize(tuple2<T, T2>* self)
    {
        if(isheap(T)) {
            delete self.v1;
        }
        if(isheap(T2)) {
            delete self.v2;
        }
    }
    bool equals(tuple2<T, T2>* left, tuple2<T, T2>* right)
    {
        if(!left.v1.equals(right.v1)) {
            return false;
        }
        if(!left.v2.equals(right.v2)) {
            return false;
        }

        return true;
    }
}

struct tuple3<T, T2, T3>
{
    T v1;
    T2 v2;
    T3 v3;
};

impl tuple3 <T, T2, T3>
{
    tuple3<T,T2, T3>*% clone(tuple3<T, T2, T3>* self)
    {
        tuple3<T,T2,T3>*% result = new tuple3<T, T2, T3>;

        result.v1 = clone self.v1;
        result.v2 = clone self.v2;
        result.v3 = clone self.v3;

        return result;
    }

    void finalize(tuple3<T, T2, T3>* self)
    {
        if(isheap(T)) {
            delete self.v1;
        }
        if(isheap(T2)) {
            delete self.v2;
        }
        if(isheap(T3)) {
            delete self.v3;
        }
    }
    bool equals(tuple3<T, T2, T3>* left, tuple3<T, T2, T3>* right)
    {
        if(!left.v1.equals(right.v1)) {
            return false;
        }
        if(!left.v2.equals(right.v2)) {
            return false;
        }
        if(!left.v3.equals(right.v3)) {
            return false;
        }

        return true;
    }
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
    tuple4<T,T2, T3, T4>*% clone(tuple4<T, T2, T3, T4>* self)
    {
        tuple4<T,T2,T3,T4>*% result = new tuple4<T, T2, T3, T4>;

        result.v1 = clone self.v1;
        result.v2 = clone self.v2;
        result.v3 = clone self.v3;
        result.v4 = clone self.v4;

        return result;
    }

    void finalize(tuple4<T, T2, T3, T4>* self)
    {
        if(isheap(T)) {
            delete self.v1;
        }
        if(isheap(T2)) {
            delete self.v2;
        }
        if(isheap(T3)) {
            delete self.v3;
        }
        if(isheap(T4)) {
            delete self.v4;
        }
    }
    bool equals(tuple4<T, T2, T3, T4>* left, tuple4<T, T2, T3, T4>* right)
    {
        if(!left.v1.equals(right.v1)) {
            return false;
        }
        if(!left.v2.equals(right.v2)) {
            return false;
        }
        if(!left.v3.equals(right.v3)) {
            return false;
        }
        if(!left.v4.equals(right.v4)) {
            return false;
        }

        return true;
    }
}
```
5. Collection and heap system

All the elements added to the Collection are also released from memory and cloned on the collection side. When adding elements, do not add the heap managed by the variable table. This is because the heap managed by the variable table becomes double free because automatic free occurs when it exits the block and free also occurs on the collection side. For example:

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


7. buffer

The definition is as follows.

定義は以下です。

```
struct buffer {
    char* buf;
    int len;
    int size;
};

static buffer*% buffer_initialize(buffer*% self) 
{
    self.size = 128;
    self.buf = calloc(1, self.size);
    self.buf[0] = '\0'
    self.len = 0;

    return self;
}

static void buffer_finalize(buffer* self)
{
    free(self.buf);
}

static int buffer_length(buffer* self) 
{
    return self.len;
}

static void buffer_append(buffer* self, char* mem, size_t size)
{
    if(self.len + size + 1 + 1 >= self.size) {
        int new_size = (self.size + size + 1) * 2;
        self.buf = realloc(self.buf, new_size);
        self.size = new_size;
    }

    memcpy(self.buf + self.len, mem, size);
    self.len += size;

    self.buf[self.len] = '\0';
}

static void buffer_append_char(buffer* self, char c)
{
    if(self.len + 1 + 1 + 1 >= self.size) {
        int new_size = (self.size + 10 + 1) * 2;
        self.buf = realloc(self.buf, new_size);
        self.size = new_size;
    }

    self.buf[self.len] = c;
    self.len++;

    self.buf[self.len] = '\0';
}

static void buffer_append_str(buffer* self, char* str)
{
    self.append(str, strlen(str));
}

static void buffer_append_nullterminated_str(buffer* self, char* str)
{
    self.append(str, strlen(str));
    self.append_char('\0');
}

static string buffer_to_string(buffer* self)
{
    return (string(self.buf));
}

static void buffer_append_int(buffer* self, int value) 
{
    self.append((char*)&value, sizeof(int));
}

static void buffer_append_long(buffer* self, long value) 
{
    self.append((char*)&value, sizeof(long));
}

static void buffer_append_short(buffer* self, short value) 
{
    self.append((char*)&value, sizeof(short));
}

static void buffer_alignment(buffer* self) 
{
    int len = self.len;
    len = (len + 3) & ~3;

    for(int i=self.len; i<len; i++) {
        self.append_char('\0');
    }
}

static int buffer_compare(buffer* left, buffer* right) 
{
    return strcmp(left.buf, right.buf);
}
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

@m is blocked until @ n = 123 of fun is executed. $
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
        select {
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

# CHANGELOG

addition from version 1.0.9

version 1.0.9からの追加の仕様

```
void int_show(int self)
{
    printf("%d\n", self);
}

```

equals below:

は

```
void int::show(int self)
{
    printf("%d\n", self);
}
```

とも書けます。

addition from version 1.1.0

The debug info line number has been corrected.

ソースファイルの行番号のエラーを修正しています。

addition from version 1.1.2

Added to parallel processing like Go

Goのような並列処理を入れました。
