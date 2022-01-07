struct sData {
    float a;
    double b;
    double* c;
    double* d;
    int* e;
};

int main()
{
    struct sData data;
    
    data.a = 111.1f;
    data.b = 11.1;
    data.c = &data.b;
    data.d = &data.b;
    data.e = (int*)0;
    
    *data.e = 1;
    
    return 0;
}

