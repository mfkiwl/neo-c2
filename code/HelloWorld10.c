#include <come.h>

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

    vector!(v);

    xassert("macro test", v.item(0, -1) == 1 && v.item(1, -1) == 2 && v.item(2, -1) == 3);

puts("before fun");
    fun();

puts("before fun2");
    fun2();
puts("after fun2");

    return 0;
}
