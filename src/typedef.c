#include "common.h"

struct sTypeDefTable
{
    char* mName;
    sNodeType* mItem;
};

static struct sTypeDefTable* gTypeDefTable;
int gNumTypeDef;
int gSizeTypeDef;

void init_typedef()
{
    gSizeTypeDef = 128;
    gTypeDefTable = calloc(1, sizeof(struct sTypeDefTable)*gSizeTypeDef);
    gNumTypeDef = 0;
}

void free_typedef()
{
    int i;
    for(i=0; i<gSizeTypeDef; i++) {
        if(gTypeDefTable[i].mName) {
            free(gTypeDefTable[i].mName);
        }
    }
    free(gTypeDefTable);
}

void final_typedef()
{
    free_typedef();
}

void rehash_typedef()
{
    int new_size_typedef_table = gSizeTypeDef * 2;
    struct sTypeDefTable* new_typedef_table = calloc(1, sizeof(struct sTypeDefTable)*new_size_typedef_table);

    int i;
    for(i=0; i<gSizeTypeDef; i++) {
        if(gTypeDefTable[i].mName) {
            unsigned int hash_value = get_hash_key(gTypeDefTable[i].mName, new_size_typedef_table);

            struct sTypeDefTable* p = new_typedef_table + hash_value;

            while(1) {
                if(p->mName == NULL) {
                    p->mName = strdup(gTypeDefTable[i].mName);
                    p->mItem = gTypeDefTable[i].mItem;
                    break;
                }
                else {
                    p++;

                    if(p == new_typedef_table + new_size_typedef_table)
                    {
                        p = new_typedef_table;
                    }
                    else if(p == new_typedef_table + hash_value)
                    {
                        fprintf(stderr, "overflow typedef number\n");
                        exit(2);
                    }
                }
            }
        }
    }

    free_typedef();

    gTypeDefTable = new_typedef_table;
    gSizeTypeDef = new_size_typedef_table;
}

void add_typedef(char* name, sNodeType* node_type)
{
    if(gNumTypeDef >= gSizeTypeDef/3) {
        rehash_typedef();
    }

    unsigned int hash_value = get_hash_key(name, gSizeTypeDef);

    struct sTypeDefTable* p = gTypeDefTable + hash_value;

    while(1) {
        if(p->mName == NULL) {
            p->mName = strdup(name);
            p->mItem = clone_node_type(node_type);

            gNumTypeDef++;
            break;
        }
        else {
            p++;

            if(p == gTypeDefTable + gSizeTypeDef)
            {
                p = gTypeDefTable;
            }
            else if(p == gTypeDefTable + hash_value)
            {
                fprintf(stderr, "overflow typedef number\n");
                exit(2);
            }
        }
    }
}

sNodeType* get_typedef(char* name)
{
    sNodeType* result = NULL;

    if(strcmp(name, "") == 0) {
        return NULL;
    }

    unsigned int hash_value = get_hash_key(name, gSizeTypeDef);

    struct sTypeDefTable* p = gTypeDefTable + hash_value;

    while(1) {
        if(p->mName == NULL) {
            return NULL;
        }
        else if(strcmp(p->mName, name) == 0) {
            result = clone_node_type(p->mItem);
            break;
        }
        else {
            p++;

            if(p == gTypeDefTable + gSizeTypeDef)
            {
                p = gTypeDefTable;
            }
            else if(p == gTypeDefTable + hash_value)
            {
                break;
            }
        }
    }

    return result;
}

