#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char*% string;

inline void xassert(const char* msg, bool exp)
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

inline string string(char* str)
{
    int len = strlen(str) + 1;
    char* result = (char*)calloc(len, sizeof(char));

    strncpy(result, str, len);

    return dummy_heap result;
}

inline string xsprintf(char* msg, ...)
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

/*
/// vector ///
struct vector<T> 
{
    T&* items;
    int len;
    int size;
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
    vector<T>%* initialize_with_values(vector<T>%* self, int len, T& value) 
    {
        self.size = len;
        self.len = len;
        self.items = borrow new T[self.size];

        for(int i=0; i<len; i++) {
            if(isheap(T)) {
                self.items[i] = borrow clone value;
            }
            else {
                self.items[i] = value;
            }
        }

        return self;
    }

    vector<T>%* clone(vector<T>* self) {
        var result = new vector<T>.initialize();

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

    finalize()
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
            var new_size = self.size * 2;
            var items = self.items;

            self.items = borrow new T[new_size];

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

    T pop_back(vector<T>* self, T& default_value)
    {
        if(self.len == 0) {
            return dummy_heap default_value;
        }

        T result = (T)self.items[self.len-1];

        self.len--;

        return result;
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
    T clone_item(vector<T>* self, int index, T& default_value) 
    {
        if(index < 0) {
            index += self.len;
        }

        if(index >= 0 && index < self.len)
        {
            if(isheap(T)) {
                return clone self.items[index];
            }
            else {
                return dummy_heap self.items[index];
            }
        }

        return dummy_heap default_value;
    }
    void each(vector<T>* self, void (*block_)(T&,int,bool*)) {
        for(int i_=0; i_<self.len; i_++) {
            bool end_flag_ = false;
            block_(self.items[i_], i_, &end_flag_);
            if(end_flag_ == true) {
                break;
            }
        };
    }

    int find(vector<T>* self, T& item, int default_value) {
        int result = default_value;
        self.each {
            if(it.equals(item)) {
                result = it2;
                *it3 = true;
                return;
            }
        }

        return result;
    }

    template <R> vector<R>*% map(vector<T>* self, R (*block_)(T&))
    {
        var result_ = new vector<R>.initialize();

        for(int i_=0; i_<self.len; i_++) {
            result_.push_back(block_(self.items[i_]));
        }

        result_
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

    int length(vector<T>* self)
    {
        return self.len;
    }

    void reset(vector<T>* self) {
        self.len = 0;
    }
    
    list<T>*% to_list(vector<T>* self) {
        var result = new vector<T>.initialize();
        
        self.each {
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
*/
