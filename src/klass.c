#include "common.h"

sCLClass* gClasses;
int gNumClasses;
int gSizeClasses;

BOOL gInhibitsRehashClasses;

unsigned int get_hash_key(char* name, unsigned int max)
{
    unsigned int result = 0;
    char* p = name;
    while(*p) {
        result += *p;
        p++;
    }

    return result % max;
}

static sCLClass* alloc_class(char* class_name_, BOOL primitive_, BOOL struct_, BOOL number_type, BOOL unsigned_number, int generics_number, int method_generics_number, BOOL union_, BOOL anonymous, BOOL enum_, BOOL anonymous_var_name);

void class_init()
{
    gSizeClasses = CLASS_NUM_MAX;
    gClasses = calloc(1, sizeof(sCLClass)*gSizeClasses);
    gNumClasses = 0;

    gInhibitsRehashClasses = FALSE;

    alloc_class("bool", TRUE, FALSE, TRUE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("char", TRUE, FALSE, TRUE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("short", TRUE, FALSE, TRUE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("int", TRUE, FALSE, TRUE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("long", TRUE, FALSE, TRUE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("__uint128_t", TRUE, FALSE, TRUE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("void", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("float", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("double", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("long_double", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("any", FALSE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("TYPEOF", FALSE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("lambda", FALSE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("generics0", FALSE, FALSE, FALSE, FALSE, 0, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("generics1", FALSE, FALSE, FALSE, FALSE, 1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("generics2", FALSE, FALSE, FALSE, FALSE, 2, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("generics3", FALSE, FALSE, FALSE, FALSE, 3, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("generics4", FALSE, FALSE, FALSE, FALSE, 4, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("generics5", FALSE, FALSE, FALSE, FALSE, 5, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("generics6", FALSE, FALSE, FALSE, FALSE, 6, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("generics7", FALSE, FALSE, FALSE, FALSE, 7, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("generics8", FALSE, FALSE, FALSE, FALSE, 8, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("generics9", FALSE, FALSE, FALSE, FALSE, 9, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("mgenerics0", FALSE, FALSE, FALSE, FALSE, -1, 0, FALSE, FALSE, FALSE, FALSE);
    alloc_class("mgenerics1", FALSE, FALSE, FALSE, FALSE, -1, 1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("mgenerics2", FALSE, FALSE, FALSE, FALSE, -1, 2, FALSE, FALSE, FALSE, FALSE);
    alloc_class("mgenerics3", FALSE, FALSE, FALSE, FALSE, -1, 3, FALSE, FALSE, FALSE, FALSE);
    alloc_class("mgenerics4", FALSE, FALSE, FALSE, FALSE, -1, 4, FALSE, FALSE, FALSE, FALSE);
    alloc_class("mgenerics5", FALSE, FALSE, FALSE, FALSE, -1, 5, FALSE, FALSE, FALSE, FALSE);
    alloc_class("mgenerics6", FALSE, FALSE, FALSE, FALSE, -1, 6, FALSE, FALSE, FALSE, FALSE);
    alloc_class("mgenerics7", FALSE, FALSE, FALSE, FALSE, -1, 7, FALSE, FALSE, FALSE, FALSE);
    alloc_class("mgenerics8", FALSE, FALSE, FALSE, FALSE, -1, 8, FALSE, FALSE, FALSE, FALSE);
    alloc_class("mgenerics9", FALSE, FALSE, FALSE, FALSE, -1, 9, FALSE, FALSE, FALSE, FALSE);
    alloc_class("_Float16", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("_Float16x", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("_Float32", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("_Float32x", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("_Float64", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("_Float64x", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("_Float128", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);
    alloc_class("_Float128x", TRUE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, FALSE, FALSE);

    if(sizeof(size_t) == 4) {
        add_typedef("size_t", create_node_type_with_class_name("int"));
    }
    else {
        add_typedef("size_t", create_node_type_with_class_name("long"));
    }
    add_typedef("_Bool", create_node_type_with_class_name("bool"));
}

void classes_free()
{
    int i;
    for(i=0; i<gSizeClasses; i++) {
        if(gClasses[i].mName) {
            free(gClasses[i].mName);

            int j;
            for(j=0; j<gClasses[i].mNumFields; j++) {
                free(gClasses[i].mFieldName[j]);
            }

            if(gClasses[i].mFieldName) {
                free(gClasses[i].mFieldName);
            }
            if(gClasses[i].mFields) {
                free(gClasses[i].mFields);
            }
        }
    }

    free(gClasses);
}

void class_final()
{
    classes_free();
}

void rehash_classes()
{
    int new_size_classes = gSizeClasses * 2;
    sCLClass* new_classes = calloc(1, sizeof(sCLClass)*new_size_classes);

    int i;
    for(i=0; i<gSizeClasses; i++) {
        if(gClasses[i].mName) {
            int hash_value = get_hash_key(gClasses[i].mName, new_size_classes);
            sCLClass* p = new_classes + hash_value;

            while(1) {
                if(p->mName == NULL) {
                    p->mName = strdup(gClasses[i].mName);

                    p->mFlags = gClasses[i].mFlags;
                    p->mGenericsNum = gClasses[i].mGenericsNum;
                    p->mMethodGenericsNum = gClasses[i].mMethodGenericsNum;
                    p->mUndefinedStructType = gClasses[i].mUndefinedStructType;

                    p->mVersion = gClasses[i].mVersion;

                    p->mNumFields = gClasses[i].mNumFields;

                    p->mFieldName = calloc(1, sizeof(char*)*gClasses[i].mNumFields);
                    p->mFields = calloc(1, sizeof(sNodeType*)*gClasses[i].mNumFields);

                    int j;
                    for(j=0; j<gClasses[i].mNumFields; j++) {
                        p->mFieldName[j] = strdup(gClasses[i].mFieldName[j]);
                        p->mFields[j] = gClasses[i].mFields[j];
                    }
                    break;
                }
                else {
                    p++;

                    if(p == new_classes + new_size_classes) {
                        p = new_classes;
                    }
                    else if(p == new_classes + hash_value) {
                        fprintf(stderr, "overflow classes\n");
                        exit(2);
                    }
                }
            }
            
        }
    }

    classes_free();

    gClasses = new_classes;
    gSizeClasses = new_size_classes;
}

static sCLClass* alloc_class(char* class_name_, BOOL primitive_, BOOL struct_, BOOL number_type, BOOL unsigned_number, int generics_number, int method_generics_number, BOOL union_, BOOL anonymous, BOOL enum_, BOOL anonymous_var_name)
{
    if(gNumClasses >= gSizeClasses/3 && !gInhibitsRehashClasses) {
        //rehash_classes();
        // class pointer can't move the address(statically contained)
    }

    if(gNumClasses >= gSizeClasses) {
        fprintf(stderr, "overflow class number\n");
        exit(2);
    }

    int hash_value = get_hash_key(class_name_, gSizeClasses);
    sCLClass* p = gClasses + hash_value;

    while(1) {
        if(p->mName == NULL) {
            p->mName = strdup(class_name_);

            p->mFlags = 0;

            p->mFlags |= (primitive_ ? CLASS_FLAGS_PRIMITIVE:0) | (struct_ ? CLASS_FLAGS_STRUCT:0) | (number_type ? CLASS_FLAGS_NUMBER:0) | (unsigned_number ? CLASS_FLAGS_UNSIGNED_NUMBER:0) | (union_ ? CLASS_FLAGS_UNION:0) | (anonymous ? CLASS_FLAGS_ANONYMOUS:0) | (enum_ ? CLASS_FLAGS_ENUM:0) | (anonymous_var_name ? CLASS_FLAGS_ANONYMOUS_VAR_NAME:0);

            if(generics_number >= 0) {
                p->mFlags |= CLASS_FLAGS_GENERICS;
            }
            if(method_generics_number >= 0) {
                p->mFlags |= CLASS_FLAGS_METHOD_GENERICS;
            }
            p->mGenericsNum = generics_number;
            p->mMethodGenericsNum = method_generics_number;
            p->mUndefinedStructType = NULL;

            p->mVersion = 0;

            p->mFieldName = NULL;
            p->mFields = NULL;

            p->mNumFields = 0;

            gNumClasses++;

            return p;
        }
        else {
            if(strcmp(p->mName, class_name_) == 0) {
                p->mFlags = 0;
                p->mFlags |= (primitive_ ? CLASS_FLAGS_PRIMITIVE:0) | (struct_ ? CLASS_FLAGS_STRUCT:0) | (number_type ? CLASS_FLAGS_NUMBER:0) | (unsigned_number ? CLASS_FLAGS_UNSIGNED_NUMBER:0) | (union_ ? CLASS_FLAGS_UNION:0) | (anonymous ? CLASS_FLAGS_ANONYMOUS:0) | (enum_ ? CLASS_FLAGS_ENUM:0) | (anonymous_var_name ? CLASS_FLAGS_ANONYMOUS_VAR_NAME:0);

                if(generics_number >= 0) {
                    p->mFlags |= CLASS_FLAGS_GENERICS;
                }
                if(method_generics_number >= 0) {
                    p->mFlags |= CLASS_FLAGS_METHOD_GENERICS;
                }
                p->mGenericsNum = generics_number;
                p->mMethodGenericsNum = method_generics_number;
                p->mUndefinedStructType = NULL;

                p->mVersion = 0;

                int i;
                for(i=0; i<p->mNumFields; p++) {
                    free(p->mFieldName[i]);
                }
                free(p->mFieldName);
                free(p->mFields);

                p->mFieldName = NULL;
                p->mFields = NULL;

                p->mNumFields = 0;

                return p;
            }
            else {
                p++;

                if(p == gClasses + gSizeClasses) {
                    p = gClasses;
                }
                else if(p == gClasses + hash_value) {
                    fprintf(stderr, "overflow classes\n");
                    exit(2);
                }
            }
        }
    }
}

sCLClass* get_class(char* class_name_)
{
    unsigned int hash_key = get_hash_key(class_name_, gSizeClasses);
    sCLClass* p = gClasses + hash_key;

    while(1) {
        if(p->mName) {
            if(strcmp(p->mName, class_name_) == 0) {
                return p;
            }
            else {
                p++;

                if(p == gClasses + gSizeClasses) {
                    p = gClasses;
                }
                else if(p == gClasses + hash_key) {
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    return NULL;
}

sCLClass* alloc_struct(char* class_name_, BOOL anonymous)
{
    sCLClass* klass = alloc_class(class_name_, FALSE, TRUE, FALSE, FALSE, -1, -1, FALSE, anonymous, FALSE, FALSE);

    return klass;
}

sCLClass* alloc_enum(char* class_name_)
{
    sCLClass* klass = alloc_class(class_name_, FALSE, FALSE, FALSE, FALSE, -1, -1, FALSE, FALSE, TRUE, FALSE);

    return klass;
}

sCLClass* alloc_union(char* class_name_, BOOL anonymous, BOOL anonymous_var_name)
{
    sCLClass* klass = alloc_class(class_name_, FALSE, FALSE, FALSE, FALSE, -1, -1, TRUE, anonymous, FALSE, anonymous_var_name);

    return klass;
}

void add_fields_to_struct(sCLClass* klass, int num_fields, char** field_name, struct sNodeTypeStruct** fields)
{
    if(klass->mNumFields > 0) {
        int i;
        for(i=0; i<klass->mNumFields; i++) {
            free(klass->mFieldName[i]);
        }
        free(klass->mFieldName);
        free(klass->mFields);

        klass->mNumFields = 0;
    }

    klass->mFieldName = calloc(1, sizeof(char*)*num_fields);
    klass->mFields = calloc(1, sizeof(sNodeType*)*num_fields);

    int i;
    for(i=0; i<num_fields; i++) {
        klass->mFieldName[i] = strdup(field_name[i]);
        klass->mFields[i] = clone_node_type(fields[i]);
    }

    klass->mNumFields = num_fields;
}

void add_fields_to_union(sCLClass* klass, int num_fields, char** field_name, struct sNodeTypeStruct** fields)
{
    if(klass->mNumFields > 0) {
        int i;
        for(i=0; i<klass->mNumFields; i++) {
            free(klass->mFieldName[i]);
        }
        free(klass->mFieldName);
        free(klass->mFields);

        klass->mNumFields = 0;
    }

    klass->mFieldName = calloc(1, sizeof(char*)*num_fields);
    klass->mFields = calloc(1, sizeof(sNodeType*)*num_fields);

    int i;
    for(i=0; i<num_fields; i++) {
        klass->mFieldName[i] = strdup(field_name[i]);
        klass->mFields[i] = clone_node_type(fields[i]);
    }

    klass->mNumFields = num_fields;
}

int get_field_index(sCLClass* klass, char* var_name, int* parent_field_index)
{
    if((klass->mFlags & CLASS_FLAGS_STRUCT) || (klass->mFlags & CLASS_FLAGS_UNION)) 
    {
        int i;
        for(i=0; i<klass->mNumFields; i++) {
            if(parent_field_index) {
                sNodeType* field_type = clone_node_type(klass->mFields[i]);

                sCLClass* field_class = field_type->mClass;

                if(field_class->mFlags & CLASS_FLAGS_ANONYMOUS_VAR_NAME)
                {
                    int result = get_field_index(field_class, var_name, NULL);

                    if(result != -1) {
                        *parent_field_index = i;
                        return result;
                    }
                }
            }

            char* field_name = klass->mFieldName[i];

            if(strcmp(field_name, var_name) == 0) {
                return i;
            }
        }
    }

    return -1;
}

