#include <neo-c2.h>

bool fun()
{
    map<string, int>*% params = new map<string, int>.initialize();
    
    if(true) {
        return true;
    }
    
    return true;
}

int main()
{
    vector<string>*% param_names = new vector<string>.initialize();
    
    param_names.push_back(string("AAA"));
    param_names.push_back(string("BBB"));
    param_names.push_back(string("CCC"));
    
    fun();
    
    return 0;
}
