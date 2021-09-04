
int xcomp(int a, int b) {
    return 1;
}

void xsort(int (*compare)(int,int)) {
}

int main()
{
    xsort(xcomp);
    return 0;
}
