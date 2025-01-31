#define _GNU_SOURCE

#define __attribute__(x)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __DARWIN__
#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif

#include <gc.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/select.h>

#define foreach(o1, o2) for(auto _obj = (o2), auto o1 = _obj.begin(); !_obj.end(); o1 = _obj.next())

typedef char* string;

void* ncmemdup(void* block);

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
    char* result = (char*)GC_malloc(sizeof(char)*len);

    strncpy(result, str, len);

    return result;
}

string xsprintf(char* msg, ...);
string char::reverse(char* str);
string char::substring(char* str, int head, int tail);
int char::length(char* str);

/// int methods ///
int int::get_hash_key(int value);

/// char methods ///
int char::get_hash_key(char* value);
bool char::equals(string left, string right);
int char::compare(int left, int right);

/// vector ///
struct vector<T> 
{
    T* items;
    int len;
    int size;

    int it;
};

impl vector<T> 
{
    vector<T>* initialize(vector<T>* self) 
    {
        self.size = 16;
        self.len = 0;
        self.items = new T[self.size];

        return self;
    }

    vector<T>* clone(vector<T>* self)
    {
        vector<T>* result = new vector<T>;

        result.len = self.len;
        result.size = self.size;
        result.it = 0;
        result.items = new T[result.size];

        for(int i=0; i<self.len; i++) 
        {
            if(is_gc_heap(self.items[i])) {
                result.items[i] = clone self.items[i];
            }
            else {
                result.items[i] = self.items[i];
            }
        }

        return result;
    }
    
    void push_back(vector<T>* self, T item) {
        if(self.len == self.size) {
            auto new_size = self.size * 2;
            auto items = self.items;

            self.items = GC_malloc(sizeof(T)*new_size);

            int i;
            for(i=0; i<self.size; i++) {
                self.items[i] = items[i];
            }

            self.size = new_size;
        }

        self.items[self.len] = item;
        self.len++;
    }

    T item(vector<T>* self, int index, T default_value) 
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
            self.items[index] = value;

            return true;
        }

        return false;
    }

    int find(vector<T>* self, T item, int default_value) {
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

    T begin(vector<T>* self) {
        self.it = 0;

        T default_value;
        return self.item(0, default_value);
    }

    T next(vector<T>* self) {
        self.it++;

        T default_value
        return self.item(self.it, default_value);
    }

    bool end(vector<T>* self) {
        return self.it >= self.len;
    }
}

/// list ///
struct list_item<T>
{
    T item;
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
    list<T>* initialize(list<T>* self) {
        self.head = null;
        self.tail = null;
        self.len = 0;

        return self;
    }

    list<T>* clone(list<T>* self) {
        auto result = new list<T>.initialize();

        list_item<T>* it = self.head;
        while(it != null) {
            if(is_gc_heap(it.item)) {
                result.push_back(clone it.item);
            }
            else {
                result.push_back(it.item);
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
        if(self.len == 0) {
            list_item<T>* litem = new list_item<T>;

            litem.prev = null;
            litem.next = null;
            litem.item = item;
            
            self.tail = litem;
            self.head = litem;
        }
        else if(self.len == 1) {
            list_item<T>* litem = new list_item<T>;

            litem.prev = self.head;
            litem.next = null;
            litem.item = item;
            
            self.tail = litem;
            self.head.next = litem;
        }
        else {
            list_item<T>* litem = new list_item<T>;

            litem.prev = self.tail;
            litem.next = null;
            litem.item = item;
            
            self.tail.next = litem;
            self.tail = litem;
        }

        self.len++;
    }
    
    T item(list<T>* self, int position, T default_value) 
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

        if(position == 0) {
            list_item<T>* litem = new list_item<T>;

            litem.prev = null;
            litem.next = self.head;
            litem.item = item;
            
            self.head.prev = litem;
            self.head = litem;

            self.len++;
        }
        else if(self.len == 1) {
            auto litem = new list_item<T>;

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
                    list_item<T>* litem = new list_item<T>;

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
            auto prev_it = it;
            it = it.next;
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
                    list_item<T>* prev_it = it;

                    it = it.next;
                    i++;

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
                    list_item<T>* prev_it = it;

                    it = it.next;
                    i++;

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
                    list_item<T>* prev_it = it;

                    it = it.next;
                    i++;

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
        if(position < 0) {
            position += self.len;
        }

        list_item<T>* it = self.head;
        int i = 0;
        while(it != null) {
            if(position == i) {
                it.item = item;
                break;
            }
            it = it.next;
            i++;
        }
    }

    int find(list<T>* self, T item, int default_value) {
        int it2 = 0;
        foreach(it, self) {
            if(it.equals(item)) {
                return it2;
            }
            it2++;
        }

        return default_value;
    }

    list<T>* sublist(list<T>* self, int begin, int tail) {
        list<T>* result = new list<T>.initialize();

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
        int i = 0;
        while(it != null) {
            if(i >= begin && i < tail) {
                if(is_gc_heap(it.item)) {
                    result.push_back(clone it.item);
                }
                else {
                    result.push_back(it.item);
                }
            }
            it = it.next;
            i++;
        };

        return result;
    }

    list<T>* reverse(list<T>* self) {
        list<T>* result = new list<T>.initialize();

        list_item<T>* it = self.tail;
        while(it != null) {
            if(is_gc_heap(it.item)) {
                result.push_back(clone it.item);
            }
            else {
                result.push_back(it.item);
            }
            it = it.prev;
        };

        return result;
    }

    list<T>* merge_list(list<T>* left, list<T>* right, int (*compare)(T,T)) {
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
                    if(is_gc_heap(it.item)) {
                        result.push_back(clone it.item);
                    }
                    else {
                        result.push_back(it.item);
                    }

                    it = it.next;
                }
                else {
                    if(is_gc_heap(it.item)) {
                        result.push_back(clone it2.item);
                    }
                    else {
                        result.push_back(it2.item);
                    }

                    it2 = it2.next;
                }
            }

            if(it == null) {
                if(it2 != null) {
                    while(it2 != null) {
                        if(is_gc_heap(it2.item)) {
                            result.push_back(clone it2.item);
                        }
                        else {
                            result.push_back(it2.item);
                        }

                        it2 = it2.next;
                    }
                }
                break;
            }
            else if(it2 == null) {
                if(it != null) {
                    while(it != null) {
                        if(is_gc_heap(it.item)) {
                            result.push_back(clone it.item);
                        }
                        else {
                            result.push_back(it.item);
                        }

                        it = it.next;
                    }
                }
                break;
            }
        }

        return result;
    }
    list<T>* merge_sort(list<T>* self, int (*compare)(T,T)) {
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
            if(is_gc_heap(it.item)) {
                list1.push_back(clone it.item);
            }
            else {
                list1.push_back(it.item);
            }

            if(is_gc_heap(it.next.item)) {
                list2.push_back(clone it.next.item);
            }
            else {
                list2.push_back(it.next.item);
            }

            if(it.next.next == null) {
                break;
            }

            it = it.next.next;

            if(it.next == null) {
                if(is_gc_heap(it.item)) {
                    list1.push_back(clone it.item);
                }
                else {
                    list1.push_back(it.item);
                }
                break;
            }
        }

        return list1.merge_sort(compare).merge_list( list2.merge_sort(compare), compare);
    }
    list<T>* sort(list<T>* self, int (*compare)(T,T)) {
        return self.merge_sort(compare);
    }

    list<T>* uniq(list<T>* self) {
        list<T>* result = new list<T>.initialize();

        if(self.length() > 0) {
            T default_value;
            T item_before = self.item(0, default_value);

            if(is_gc_heap(item_before)) {
                result.push_back(clone item_before);
            }
            else {
                result.push_back(item_before);
            }

            foreach(it, self.sublist(1,-1)) {
                if(!it.equals(item_before)) {
                    if(is_gc_heap(it)) {
                        result.push_back(clone it);
                    }
                    else {
                        result.push_back(it);
                    }
                }

                item_before = it;
            }
        }

        return result;
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

    T begin(list<T>* self) {
        self.it = self.head;

        if(self.it) {
            return self.it.item;
        }
        
        T null_object;
        memset(&null_object, 0, sizeof(T));
        
        return null_object;
    }

    T next(list<T>* self) {
        self.it = self.it.next;

        if(self.it) {
            return self.it.item;
        }
        
        T null_object;
        memset(&null_object, 0, sizeof(T));
        return null_object;
    }

    bool end(list<T>* self) {
        T null_object;
        memset(&null_object, 0, sizeof(T));
        
        return memcmp(&self.it, &null_object, sizeof(T)) == 0;
    }
    
    string join(list<string>* self, char* sep) {
        buffer* buf = new buffer.initialize();
        
        int n = 0;
        foreach(it , self) {
            buf.append_str(it);
            
            if(n < self.length()-1) {
                buf.append_str(sep);
            }
            
            n++;
        }
        
        return buf.to_string();
    }
}

impl vector<T> 
{
    list<T>* to_list(vector<T>* self) {
        auto result = new list<T>.initialize();
        
        foreach(it, self) {
            if(is_gc_heap(it)) {
                result.push_back(clone it);
            }
            else {
                result.push_back(it);
            }
        }
        
        return result;
    }
}

struct map<T, T2>
{
    T* keys;
    bool* item_existance;
    T2* items;
    int size;
    int len;

    int it;
};

#define MAP_TABLE_DEFAULT_SIZE 128

impl map <T, T2>
{
    map<T,T2>* initialize(map<T,T2>* self) {
        self.keys = new T[MAP_TABLE_DEFAULT_SIZE];
        self.items = new T2[MAP_TABLE_DEFAULT_SIZE];
        self.item_existance = new bool[MAP_TABLE_DEFAULT_SIZE];

        for(int i=0; i<MAP_TABLE_DEFAULT_SIZE; i++)
        {
            self.item_existance[i] = false;
        }

        self.size = MAP_TABLE_DEFAULT_SIZE;
        self.len = 0;

        self.it = 0;

        return self;
    }


    T2 at(map<T, T2>* self, T key, T2 default_value) 
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
        T* keys = new T[size];
        T2* items = new T2[size];
        bool* item_existance =  new bool[size];

        int len = 0;

        for(auto it = self.begin(); !self.end(); it = self.next()) {
            T2 default_value;
            T2 it2 = self.at(it, default_value);
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
                    T2 default_value;
                    items[n] = self.at(it, default_value);

                    len++;
                    break;
                }
            }
        }

        self.keys = keys;
        self.items = items;
        self.item_existance = item_existance;

        self.size = size;
        self.len = len;
    }

    void insert(map<T,T2>* self, T key, T2 item) 
    {
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

    map<T, T2>* clone(map<T, T2>* self)
    {
        auto result = new map<T,T2>.initialize();

        for(auto it = self.begin(); !self.end(); it = self.next()) {
            T2 default_value;
            auto it2 = self.at(it, default_value);

            if(is_gc_heap(it)) {
                if(is_gc_heap(it2)) {
                    result.insert(clone it, clone it2);
                }
                else {
                    result.insert(clone it, it2);
                }
            }
            else {
                if(is_gc_heap(it2)) {
                    result.insert(it, clone it2);
                }
                else {
                    result.insert(it, it2);
                }
            }
        }

        return result;
    }

    bool find(map<T, T2>* self, T key) {
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
            T2 default_value;
            T2 it2 = left.at(it, default_value);

            if(right.find(it)) {
                T2 default_value;
                T2 item = right.at(it, default_value);
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

    T begin(map<T, T2>* self) {
        self.it = 0;
        while(self.it < self.size) {
            if(self.item_existance[self.it]) {
                return self.keys[self.it++];
            }
            self.it++;
        }
        
        T null_object;
        memset(&null_object, 0, sizeof(T));

        return null_object;
    }

    T next(map<T, T2>* self) {
        while(self.it < self.size) {
            if(self.item_existance[self.it]) {
                return self.keys[self.it++];
            }
            self.it++;
        }
        
        T null_object;
        memset(&null_object, 0, sizeof(T));

        return null_object;
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

struct tuple1<T>
{
    T v1;
};

impl tuple1 <T>
{
    tuple1<T>* clone(tuple1<T>* self)
    {
        tuple1<T>* result = new tuple1<T>;

        if(is_gc_heap(self.v1)) {
            result.v1 = clone self.v1;
        }
        else {
            result.v1 = self.v1;
        }

        return result;
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
    tuple2<T,T2>* clone(tuple2<T, T2>* self)
    {
        tuple2<T,T2>* result = new tuple2<T, T2>;

        if(is_gc_heap(self.v1)) {
            result.v1 = clone self.v1;
        }
        else {
            result.v1 = self.v1;
        }
        if(is_gc_heap(self.v2)) {
            result.v2 = clone self.v2;
        }
        else {
            result.v2 = self.v2;
        }

        return result;
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
    tuple3<T,T2, T3>* clone(tuple3<T, T2, T3>* self)
    {
        tuple3<T,T2,T3>* result = new tuple3<T, T2, T3>;

        if(is_gc_heap(self.v1)) {
            result.v1 = clone self.v1;
        }
        else {
            result.v1 = self.v1;
        }
        if(is_gc_heap(self.v2)) {
            result.v2 = clone self.v2;
        }
        else {
            result.v2 = self.v2;
        }
        if(is_gc_heap(self.v3)) {
            result.v3 = clone self.v3;
        }
        else {
            result.v3 = self.v3;
        }

        return result;
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
    tuple4<T,T2, T3, T4>* clone(tuple4<T, T2, T3, T4>* self)
    {
        tuple4<T,T2,T3,T4>* result = new tuple4<T, T2, T3, T4>;

        if(is_gc_heap(self.v1)) {
            result.v1 = clone self.v1;
        }
        else {
            result.v1 = self.v1;
        }
        if(is_gc_heap(self.v2)) {
            result.v2 = clone self.v2;
        }
        else {
            result.v2 = self.v2;
        }
        if(is_gc_heap(self.v3)) {
            result.v3 = clone self.v3;
        }
        else {
            result.v3 = self.v3;
        }
        if(is_gc_heap(self.v4)) {
            result.v4 = clone self.v4;
        }
        else {
            result.v4 = self.v4;
        }

        return result;
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

struct buffer {
    char* buf;
    int len;
    int size;
};

buffer* buffer_initialize(buffer* self);
int buffer_length(buffer* self);
buffer* buffer_append(buffer* self, char* mem, size_t size);
buffer* buffer_append_char(buffer* self, char c);
buffer* buffer_append_str(buffer* self, char* str);
buffer* buffer_append_nullterminated_str(buffer* self, char* str);
string buffer_to_string(buffer* self);
buffer* buffer_append_int(buffer* self, int value);
buffer* buffer_append_long(buffer* self, long value);
buffer* buffer_append_short(buffer* self, short value);
void buffer_alignment(buffer* self);
int buffer_compare(buffer* left, buffer* right);
buffer* char::to_buffer(char* self);

/// additional libraries ///
int int::expect(int self, void* parent, void (*block)(void* parent));
bool bool::expect(bool self, void* parent, void (*block)(void* parent));
void int::times(int self, void* parent, void (*block)(void* parent));

impl list<T>
{
    list<T>* filter(list<T>* self, void* parent, bool (*block)(void*, T))
    {
        auto result = new list<T>.initialize();

        list_item<T>?* it = self.head;
        while(it != null) {
            if(block(parent, it.item)) {
                if(is_gc_heap(it.item)) {
                    result.push_back(clone it.item);
                }
                else {
                    result.push_back(it.item);
                }
            }

            it = it.next;
        }

        return result;
    } 
    list<T>* each(list<T>* self, void* parent, void (*block_)(void*, T,int,bool*)) {
        list_item<T>?* it = self.head;
        int i = 0;
        while(it != null) {
            bool end_flag = false;
            block_(parent, it.item, i, &end_flag);

            if(end_flag == true) {
                break;
            }
            it = it.next;
            i++;
        }

        return self;
    }
    template <R> list<R>* map(list<T>* self, void* parent, R (*block)(void*, T))
    {
        auto result = new list<R>.initialize();

        list_item<T>?* it = self.head;
        while(it != null) {
            result.push_back(block(parent, it.item));

            it = it.next;
        }

        return result;
    }
}

bool xiswalpha(wchar_t c);
bool xiswblank(wchar_t c);
bool xiswdigit(wchar_t c);
bool xiswalnum(wchar_t c);
bool xisalpha(char c);
bool xisblank(char c);
bool xisdigit(char c);
bool xisalnum(char c);
string xbasename(char* path);
string xextname(char* path);
string xrealpath(char* path);
void come_fd_zero(fd_set* fds);
void come_fd_set(int fd, fd_set* fds);
int come_fd_isset(int fd, fd_set* fds);

#include <limits.h>
#include <wchar.h>
#include <pcre.h>
#include <sys/ioctl.h>

typedef wchar_t* wstring;

struct regex_struct 
{
    char str[128];
    pcre* regex;

    bool ignore_case;
    bool multiline;
    bool global;
    bool extended;
    bool dotall;
    bool anchored;
    bool dollar_endonly;
    bool ungreedy;

    int options;

    pcre* re;
};

typedef regex_struct* nregex;

regex_struct* regex(char* str, bool ignore_case, bool multiline, bool global, bool extended, bool dotall, bool anchored, bool dollar_endonly, bool ungreedy);
bool char::match(char* self, regex_struct* reg);
bool char::match_count(char* self, regex_struct* reg, int count);
bool char::match_group_strings(char* self, regex_struct* reg, int count, list<string>?* group_strings);
int char::index(char* str, char* search_str, int default_value);
int char::index_count(char* str, char* search_str, int count, int default_value);
int char::rindex(char* str, char* search_str, int default_value);
int char::rindex_count(char* str, char* search_str, int count, int default_value);
int char::index_regex(char* self, regex_struct* reg, int default_value);
int char::index_regex_count(char* self, regex_struct* reg, int count, int default_value);
int char::rindex_regex(char* self, regex_struct* reg, int default_value);
int char::rindex_regex_count(char* self, regex_struct* reg, int count, int default_value);
void char::replace(char* self, int index, char c);
string char::multiply(char* str, int n);
string char::sub(char* self, regex_struct* reg, char* replace);
string char::sub_count(char* self, regex_struct* reg, char* replace, int count);
string char::sub_block(char* self, regex_struct* reg, void* parent, string (*block)(void* parent, string match_string, list<string>* group_strings));
string char::sub_block_count(char* self, regex_struct* reg, int count, void* parent, string (*block)(void* parent, string match_string, list<string>* group_strings));
list<string>* char::scan(char* self, regex_struct* reg);
list<string>* char::scan_block(char* self, regex_struct* reg, void* parent, string (*block)(void* parent, string match_string, list<string>* group_strings));
list<string>* char::scan_block_count(char* self, regex_struct* reg, int count, void* parent, string (*block)(void* parent, string match_string, list<string>* group_strings));
list<string>* char::split(char* self, regex_struct* reg);
list<string>* char::split_maxsplit(char* self, regex_struct* reg, int maxsplit);
list<string>* char::split_char(string self, char c) ;
list<string>* char::split_str(string self, char* str) ;
list<string>* char::split_block(char* self, regex_struct* reg, void* parent, string (*block)(void* parent, string match_string, list<string>* group_strings));
list<string>* char::split_block_count(char* self, regex_struct* reg, int count, void* parent, string (*block)(void* parent, string match_string, list<string>* group_strings));
nregex char::to_regex(char* self) ;
nregex char::to_regex_flags(char* self, bool global, bool ignore_case) ;
string char::printable(char* str);
char* char::delete(char* str, int head, int tail) ;
string int::to_string(wchar_t* wstr);
wstring wstring(char* str);
wstring char::to_wstring(char* str);
wstring int::substring(wchar_t* str, int head, int tail);
int int::length(wchar_t* str);
wchar_t* int::delete(wchar_t* str, int head, int tail) ;
int int::index(wchar_t* str, wchar_t* search_str, int default_value);
int int::rindex(wchar_t* str, wchar_t* search_str, int default_value);
wstring int::reverse(whar_t* str) ;
wstring int::multiply(wchar_t* str, int n);
wstring int::printable(wchar_t* str);
