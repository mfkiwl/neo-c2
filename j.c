#include <come.h>


int main()
{
    auto v = new vector<string>.initialize();

    v.push_back(string("C"));
    v.push_back(string("A"));
    v.push_back(string("B"));

    auto l = v.to_list().sort(int lambda(char* left, char* right) { return strcmp(left, right); });

    return 0;
}
