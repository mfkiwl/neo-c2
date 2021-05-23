#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef char*% string;

void xassert(const char* msg, bool exp)
{
    printf(msg);
    printf("...");

    if(exp) {
        puts("ok");
    }
    else {
        puts("false");
        exit(2);
    }
}

string string(char* str)
{
    int len = strlen(str) + 1;
    char* result = (char*)calloc(len, sizeof(char));

    strncpy(result, str, len);

    return dummy_heap result;
}

string xsprintf(char* msg, ...)
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

struct vector<T> 
{
    T&* items;
    int len;
    int size;
};

vector<T>*% vector<T>::vector()
{
    vector<T>* self = calloc(1, sizeof(vector<T>);

    self.size = 16;
    self.len = 0;
    self.items = borrow T[self.size]();

    return dummy_heap self;
}

void vector<T>::finalize(vector<T>* self)
{
    if(isheap(T)) {
        for(int i=0; i<self.len; i++) 
        {
            delete self.items[i];
        }
    }
    delete self.items;
}

vector<T>%* vector<T>::clone(vector<T>* self) 
{
    vector<T>*% result = vector<T>();

    for(int i=0; i<self.len; i++) {
        T& it = self.items[i];
        if(isheap(T)) {
            result.push_back(clone it);
        }
        else {
            result.push_back(dummy_heap it);
        }
    }

    return result;
}

void vector<T>::push_back(vector<T>* self, T item) {
    managed item;

    if(self.len == self.size) {
        int new_size = self.size * 2;
        T* items = self.items;

        self.items = borrow T[new_size]();

        for(int i=0; i<self.size; i++) {
            self.items[i] = items[i];
        }

        self.size = new_size;

        delete items;
    }

    self.items[self.len] = item;
    self.len++;
}

T& vector<T>::item(vector<T>* self, int index, T& default_value) 
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

bool vector<T>::replace(vector<T>* self, int index, T value) 
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

int vector<T>::length(vector<T>* self)
{
    return self.len;
}

int main()
{
    vector<int>*% v = vector<int>();

    v.push_back(1);
    v.push_back(2);

    xassert("vector test1", v.length() == 2);
    
    return 0;
}
