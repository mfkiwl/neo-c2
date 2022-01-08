struct sData {
    float a;
    double b;
    double* c;
    double* d;
    char e;
    char f;
    int* g;
};

int main()
{
    struct sData data;
    
    data.a = 111.1f;
    data.b = 11.1;
    data.c = &data.b;
    data.d = &data.b;
    data.g = (int*)0;
    
    *data.g = 1;
    
    return 0;
}

