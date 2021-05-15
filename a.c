
struct sData {
    int a;
    long b;
    long c;
};

union uData {
    int data1;
    long data2;

    sData data3;
};



int main()
{
    uData udata;

    return 0;
}
