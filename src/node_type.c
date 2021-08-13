#include "common.h"

static sNodeType** gNodeTypes = NULL;
static int gUsedPageNodeTypes = 0;
static int gSizePageNodeTypes = 0;
static int gUsedNodeTypes = 0;

#define NODE_TYPE_PAGE_SIZE 64

void init_node_types()
{
    const int size_page_node_types = 4;

    if(gSizePageNodeTypes == 0) {
        gNodeTypes = xcalloc(1, sizeof(sNodeType*)*size_page_node_types);

        int i;
        for(i=0; i<size_page_node_types; i++) {
            gNodeTypes[i] = xcalloc(1, sizeof(sNodeType)*NODE_TYPE_PAGE_SIZE);
        }

        gSizePageNodeTypes = size_page_node_types;
        gUsedPageNodeTypes = 0;
        gUsedNodeTypes = 0;
    }
}

void free_node_types()
{
    if(gSizePageNodeTypes > 0) {
        int i;
        for(i=0; i<gSizePageNodeTypes; i++) {
            free(gNodeTypes[i]);
        }
        free(gNodeTypes);

        gSizePageNodeTypes = 0;
        gUsedPageNodeTypes = 0;
        gUsedNodeTypes = 0;
    }
}

static sNodeType* alloc_node_type()
{
    if(gUsedNodeTypes == NODE_TYPE_PAGE_SIZE) {
        gUsedNodeTypes = 0;
        gUsedPageNodeTypes++;

        if(gUsedPageNodeTypes == gSizePageNodeTypes) {
            int new_size = (gSizePageNodeTypes+1) * 2;
            gNodeTypes = xrealloc(gNodeTypes, sizeof(sNodeType*)*new_size);
            memset(gNodeTypes + gSizePageNodeTypes, 0, sizeof(sNodeType*)*(new_size - gSizePageNodeTypes));

            int i;
            for(i=gSizePageNodeTypes; i<new_size; i++) {
                gNodeTypes[i] = xcalloc(1, sizeof(sNodeType)*NODE_TYPE_PAGE_SIZE);
            }

            gSizePageNodeTypes = new_size;
        }
    }

    return gNodeTypes[gUsedPageNodeTypes] + gUsedNodeTypes++;
}

sNodeType* clone_node_type(sNodeType* node_type)
{
    sNodeType* node_type2 = alloc_node_type();

    node_type2->mClass = node_type->mClass;
    node_type2->mNumGenericsTypes = node_type->mNumGenericsTypes;

    int i;
    for(i=0; i<node_type->mNumGenericsTypes; i++) {
        node_type2->mGenericsTypes[i] = ALLOC clone_node_type(node_type->mGenericsTypes[i]);
    }

    node_type2->mArrayDimentionNum = node_type->mArrayDimentionNum;
    for(i=0; i<node_type->mArrayDimentionNum; i++) {
        node_type2->mArrayNum[i] = node_type->mArrayNum[i];
    }
    node_type2->mSizeNum = node_type->mSizeNum;
    node_type2->mNullable = node_type->mNullable;
    node_type2->mChannel = node_type->mChannel;
    node_type2->mPointerNum = node_type->mPointerNum;
    node_type2->mHeap = node_type->mHeap;
    node_type2->mNoHeap = node_type->mNoHeap;
    node_type2->mUnsigned = node_type->mUnsigned;
    node_type2->mRegister = node_type->mRegister;
    node_type2->mVolatile = node_type->mVolatile;
    node_type2->mStatic = node_type->mStatic;
    node_type2->mOverride = node_type->mOverride;
    node_type2->mUniq = node_type->mUniq;
    node_type2->mDummyHeap = node_type->mDummyHeap;
    node_type2->mDynamicArrayNum = node_type->mDynamicArrayNum;
    node_type2->mArrayInitializeNum = node_type->mArrayInitializeNum;
    node_type2->mTypeOfExpression = node_type->mTypeOfExpression;
    node_type2->mConstant = node_type->mConstant;

    xstrncpy(node_type2->mOriginalTypeName, node_type->mOriginalTypeName, VAR_NAME_MAX);

    if(node_type->mResultType) {
        node_type2->mResultType = clone_node_type(node_type->mResultType);
    }
    else {
        node_type2->mResultType = NULL;
    }

    node_type2->mNumParams = node_type->mNumParams;
    for(i=0; i<node_type->mNumParams; i++) {
        node_type2->mParamTypes[i] = clone_node_type(node_type->mParamTypes[i]);
    }
    node_type2->mVarArgs = node_type->mVarArgs;

    node_type2->mNumFields = node_type->mNumFields;

    xstrncpy(node_type2->mTypeName, node_type->mTypeName, VAR_NAME_MAX);
    node_type2->mTypePointerNum = node_type->mTypePointerNum;

    return node_type2;
}

void show_type_core(sNodeType* type, int num_classes, char** classes, BOOL no_output_fields) 
{
    sCLClass* klass = type->mClass;
    char* class_name = CLASS_NAME(klass);

    int i;
    for(i=0; i<num_classes; i++) {
        char* class_name2 = classes[num_classes];

        if(strcmp(class_name, class_name2) == 0) {
            return;
        }
    }

    xstrncpy(classes[num_classes], class_name, VAR_NAME_MAX);
    num_classes++;

    if(type->mConstant) {
        printf("const ");
    }
    if(type->mResultType) {
        show_type_core(type->mResultType, num_classes, classes, no_output_fields);
        printf(" ");
    }
    if(klass->mFlags & CLASS_FLAGS_UNION) {
        printf("union ");
    }
    if(klass->mFlags & CLASS_FLAGS_ENUM) {
        printf("enum ");
    }
    if(klass->mFlags & CLASS_FLAGS_STRUCT) {
        printf("struct ");
    }
    printf("%s", CLASS_NAME(klass));

    if(strcmp(type->mOriginalTypeName, "") != 0) {
        printf(" typedef %s", type->mOriginalTypeName);
    }
    for(i=0; i<type->mPointerNum; i++) {
        printf("*");
    }
    for(i=0; i<type->mArrayDimentionNum; i++) {
        printf("[%d]", type->mArrayNum[i]);
    }
    if(type->mHeap) {
        printf("%%");
    }
    if(type->mNumGenericsTypes > 0) {
        printf("<");
        int i;
        for(i=0; i<type->mNumGenericsTypes; i++) {
            show_type_core(type->mGenericsTypes[i], num_classes, classes, no_output_fields);
        }
        printf(">");
    }
    if(type->mNullable) {
        printf("?");
    }
    if(type->mChannel) {
        printf("@");
    }
    
    if(type->mNumParams > 0) printf("(");
    for(i=0; i<type->mNumParams; i++)
    {
        show_node_type(type->mParamTypes[i]);
        puts(" ");
    }
    if(type->mNumParams > 0) printf(")");
    if(!no_output_fields && ((klass->mFlags & CLASS_FLAGS_STRUCT) || (klass->mFlags & CLASS_FLAGS_UNION))) {
        puts("");
        int i;
        for(i=0; i<klass->mNumFields; i++) {
            char* field_name = klass->mFieldName[i];
            sNodeType* field_type = klass->mFields[i];

            char* class_name = CLASS_NAME(field_type->mClass);

            int j;
            BOOL nest = FALSE;
            for(j=0; j<num_classes; j++) {
                char* class_name2 = classes[j];

                if(strcmp(class_name, class_name2) == 0) {
                    nest = TRUE;
                }
            }

            xstrncpy(classes[num_classes], class_name, VAR_NAME_MAX);
            num_classes++;

            if(num_classes >= 128) {
                fprintf(stderr, "overflow class\n");
                exit(2);
            }

            printf("#%d ", i);
            if(nest) {
                BOOL no_output_fields = TRUE;
                show_type_core(field_type, num_classes, classes, no_output_fields);
            }
            else {
                show_type_core(field_type, num_classes, classes, no_output_fields);

                printf(" ");
                if(i == klass->mNumFields -1) {
                    printf("%s", field_name);
                }
                else {
                    puts(field_name);
                }
            }
        }
    }
    if(klass->mFlags & CLASS_FLAGS_ENUM) {
        puts("");
        int i;
        for(i=0; i<klass->mNumElementNum; i++) {
            printf("%s %d", klass->mEnumElementNames[i], klass->mEnumElementValues[i]);

            if(i != klass->mNumElementNum -1) {
                puts("");
            }
        }
    }
}


void show_node_type(sNodeType* type)
{
    char classes[128][VAR_NAME_MAX];
    char* classes2[128];
    int j;
    for(j=0; j<128; j++) {
        classes2[j] = classes[j];
    }
    int num_classes = 0;

    char* class_name = CLASS_NAME(type->mClass);

    if(type->mClass->mFlags & CLASS_FLAGS_STRUCT || type->mClass->mFlags & CLASS_FLAGS_UNION) {
        xstrncpy(classes2[num_classes], class_name, VAR_NAME_MAX);
        num_classes++;
    }

    BOOL no_output_fields = FALSE;
    show_type_core(type, num_classes, classes2, no_output_fields);
    puts("");
}

static void skip_spaces_for_parse_class_name(char** p) 
{
    while(**p == ' ' || **p == '\t') {
        (*p)++;
    }
}

static sNodeType* parse_class_name(char** p, char** p2, char* buf)
{
    sNodeType* node_type = alloc_node_type();

    node_type->mClass = NULL;
    node_type->mNumGenericsTypes = 0;
    node_type->mArrayDimentionNum = 0;
    node_type->mNullable = FALSE;
    node_type->mChannel = FALSE;

    *p2 = buf;

    while(**p) {
        if(**p == '<') {
            (*p)++;
            skip_spaces_for_parse_class_name(p);

            char* pp = *p2;

            *pp = '\0';

            node_type->mClass = get_class(buf);

            if(node_type->mClass == NULL) {
                return NULL;
            }

            while(1) {
                node_type->mGenericsTypes[node_type->mNumGenericsTypes] = parse_class_name(p, p2, buf);
                node_type->mNumGenericsTypes++;

                if(node_type->mNumGenericsTypes >= GENERICS_TYPES_MAX) 
                {
                    return NULL;
                }

                if(**p == ',') {
                    (*p)++;
                    skip_spaces_for_parse_class_name(p);
                }
                else if(**p == '>') {
                    (*p)++;
                    skip_spaces_for_parse_class_name(p);
                    return node_type;
                }
                else {
                    return NULL;
                }
            }
        }
        else if(**p == '[') {
            node_type->mArrayDimentionNum = 0;
            while(**p == '[') {
                (*p)++;

                int n = 0;
                while(xisdigit(**p)) {
                    n = n * 10 + (**p - '0');
                    (*p)++;
                }

                node_type->mArrayNum[node_type->mArrayDimentionNum++] = n;

                if(**p == ']') {
                    (*p)++;
                }
                else {
                    return NULL;
                }
            }
        }
        else if(**p == '?') {
            (*p)++;
            skip_spaces_for_parse_class_name(p);

            node_type->mNullable = TRUE;
        }
        else if(**p == '~') {
            (*p)++;
            skip_spaces_for_parse_class_name(p);

            node_type->mChannel = TRUE;
        }
        else if(**p == '*') {
            (*p)++;
            skip_spaces_for_parse_class_name(p);

            node_type->mPointerNum++;
        }
        else if(**p == '>') {
            char* pp = *p2;
            *pp = '\0';

            node_type->mClass = get_class(buf);

            if(node_type->mClass == NULL) {
                return NULL;
            }

            return node_type;
        }
        else {
            char* pp = *p2;
            *pp = **p;

            (*p)++;
            (*p2)++;
        }
    }

    if(*p2 - buf > 0) {
        char* pp = *p2;
        *pp = '\0';

        node_type->mClass = get_class(buf);

        if(node_type->mClass == NULL) {
            return NULL;
        }
    }

    return node_type;
}

sNodeType* create_node_type_with_class_name(char* class_name_)
{
    char buf[VAR_NAME_MAX+1];

    char* p = class_name_;
    char* p2 = buf;

    sNodeType* result = parse_class_name(&p, &p2, buf);

    if(strcmp(class_name_, "lambda") == 0) {
        result->mPointerNum++;
    }
    
    return result;
}

sNodeType* create_node_type_with_class_pointer(sCLClass* klass)
{
    sNodeType* result = alloc_node_type();
    result->mClass = klass;
    return result;
}

BOOL is_number_type(sNodeType* node_type)
{
    int n = (node_type->mClass->mFlags & CLASS_FLAGS_NUMBER) == CLASS_FLAGS_NUMBER;
    return n && node_type->mPointerNum == 0;
}

BOOL check_the_same_fields(sNodeType* left_node, sNodeType* right_node)
{
    sCLClass* left_class = left_node->mClass;
    sCLClass* right_class = right_node->mClass;

    if(left_class->mNumFields != right_class->mNumFields)
    {
        return FALSE;
    }

    if(left_class->mNumFields == 0) {
        return FALSE;
    }

    int i;
    for(i=0; i<left_class->mNumFields; i++) {
        sNodeType* left_field = left_class->mFields[i];
        sNodeType* right_field = right_class->mFields[i];

        if(!type_identify(left_field, right_field))
        {
            return FALSE;
        }

    }

    return TRUE;
}

BOOL auto_cast_posibility(sNodeType* left_type, sNodeType* right_type)
{
    sCLClass* left_class = left_type->mClass;
    sCLClass* right_class = right_type->mClass; 

    if(left_type->mSizeNum > 0) {
        return TRUE;
    }
    else if(is_number_type(left_type) && is_number_type(right_type))
    {
        return TRUE;
    }
    else if(type_identify_with_class_name(left_type, "bool") && right_type->mPointerNum > 0) 
    {
        return TRUE;
    }
    else if(type_identify_with_class_name(left_type, "void*") && right_type->mPointerNum > 0) 
    {
        return TRUE;
    }
    else if(left_type->mPointerNum > 0 && type_identify_with_class_name(right_type, "void*")) 
    {
        return TRUE;
    }
    /// NULL in clang is defined int type, so this is required
    else if(left_type->mPointerNum > 0 && is_number_type(right_type))
    {
        return TRUE;
    }
    else if(is_number_type(left_type) && right_type->mPointerNum > 0) 
    {
        return TRUE;
    }
    //else if(left_type->mNullable && type_identify_with_class_name(left_type, "lambda") && type_identify_with_class_name(right_type, "void*")) 
    else if(type_identify_with_class_name(left_type, "lambda") && type_identify_with_class_name(right_type, "void*")) 
    {
        return TRUE;
    }
    else if(type_identify_with_class_name(left_type, "char*") && type_identify_with_class_name(right_type, "__builtin_va_list"))
    {
        return TRUE;
    }
    else if(type_identify_with_class_name(left_type, "__builtin_va_list") && type_identify_with_class_name(right_type, "char*"))
    {
        return TRUE;
    }
    else if(type_identify_with_class_name(left_type, "va_list") && type_identify_with_class_name(right_type, "va_list*"))
    {
        return TRUE;
    }
    else if(type_identify_with_class_name(left_type, "__builtin_va_list") && type_identify_with_class_name(right_type, "__builtin_va_list*"))
    {
        return TRUE;
    }
    else if((left_type->mPointerNum-1 == right_type->mPointerNum) && right_type->mArrayDimentionNum == 1)
    {
        return TRUE;
    }
    else if((left_type->mPointerNum-1 == right_type->mPointerNum) && right_type->mChannel == 1)
    {
        return TRUE;
    }

    return FALSE;
}

BOOL cast_posibility(sNodeType* left_type, sNodeType* right_type)
{
    sCLClass* left_class = left_type->mClass;
    sCLClass* right_class = right_type->mClass; 

    if(auto_cast_posibility(left_type, right_type))
    {
        return TRUE;
    }
    else if(left_type->mPointerNum > 0 && right_type->mPointerNum > 0)
    {
        return TRUE;
    }

    return TRUE;
    //return FALSE;
}

BOOL substitution_posibility(sNodeType* left_type, sNodeType* right_type, sCompileInfo* info)
{
    sCLClass* left_class = left_type->mClass;
    sCLClass* right_class = right_type->mClass; 

    if(type_identify_with_class_name(left_type, "any")) {
        return TRUE;
    }
    else if(left_type->mPointerNum == 0 && type_identify_with_class_name(left_type, "void")) 
    {
        return FALSE;
    }
    else if((left_class->mFlags & CLASS_FLAGS_ENUM) && type_identify_with_class_name(right_type, "int"))
    {
        return TRUE;
    }
    else if(type_identify_with_class_name(left_type, "void") && left_type->mPointerNum == 1)
    {
        if(right_type->mPointerNum > 0) {
            return TRUE;
        }
    }
    else if(type_identify(left_type, right_type) && (left_type->mNumGenericsTypes > 0 || right_type->mNumGenericsTypes > 0))
    {
        if(left_type->mNumGenericsTypes != right_type->mNumGenericsTypes)
        {
            return FALSE;
        }

        int i;
        for(i=0; i<left_type->mNumGenericsTypes; i++)
        {
            if(!substitution_posibility(left_type->mGenericsTypes[i], right_type->mGenericsTypes[i], info))
            {
                return FALSE;
            }
        }

        return TRUE;
    }
    else if(type_identify(left_type, right_type)) {
        if((left_type->mPointerNum-1 == right_type->mPointerNum) && right_type->mArrayDimentionNum == 1)
        {
            return TRUE;
        }
        else if((left_type->mPointerNum-1 == right_type->mPointerNum) && right_type->mDynamicArrayNum != 0)
        {
            return TRUE;
        }
        else if(left_type->mPointerNum == right_type->mPointerNum) 
        {
            return TRUE;
        }
        else if(left_type->mPointerNum == right_type->mPointerNum+1 && right_type->mArrayDimentionNum == -1)
        {
            return TRUE;
        }
    }

    return FALSE;
}

BOOL type_identify(sNodeType* left, sNodeType* right)
{
    return strcmp(CLASS_NAME(left->mClass), CLASS_NAME(right->mClass)) == 0;
}

BOOL type_identify_with_class_name(sNodeType* left, char* right_class_name)
{
    sNodeType* right = create_node_type_with_class_name(right_class_name);

    if(right == NULL) {
        return FALSE;
    }

    return type_identify(left, right);
}

BOOL solve_generics(sNodeType** node_type, sNodeType* generics_type)
{
    if(generics_type == NULL) {
        return TRUE;
    }

    sCLClass* klass = (*node_type)->mClass;


    if(type_identify_with_class_name(*node_type, "lambda")) 
    {
        if(!solve_generics(&(*node_type)->mResultType, generics_type))
        {
            return FALSE;
        }

        int i;
        for(i=0; i<(*node_type)->mNumParams; i++)
        {
            if(!solve_generics(&(*node_type)->mParamTypes[i], generics_type))
            {
                return FALSE;
            }
        }
    }
    else if(klass->mFlags & CLASS_FLAGS_GENERICS) {
        int generics_number = klass->mGenericsNum;

        if(generics_number >= generics_type->mNumGenericsTypes)
        {
            return FALSE;
        }

        sCLClass* klass2 = generics_type->mGenericsTypes[generics_number]->mClass;

        int generics_number2 = klass2->mGenericsNum;

        if(generics_number != generics_number2) 
        {
            int array_dimetion_num = (*node_type)->mArrayDimentionNum;
            int array_num[ARRAY_DIMENTION_MAX];
            int i;
            for(i=0; i<array_dimetion_num; i++) {
                array_num[i] = (*node_type)->mArrayNum[i];
            }
            BOOL nullable = (*node_type)->mNullable;
            BOOL channel = (*node_type)->mChannel;
            int pointer_num = (*node_type)->mPointerNum;
            BOOL heap = (*node_type)->mHeap;

            BOOL no_heap = (*node_type)->mNoHeap;

            *node_type = clone_node_type(generics_type->mGenericsTypes[generics_number]);

            if(heap) {
                (*node_type)->mHeap = heap;
            }
            if(no_heap) {
                (*node_type)->mHeap = FALSE;
            }
            if(nullable) {
                (*node_type)->mNullable = nullable;
            }
            if(channel) {
                (*node_type)->mChannel = channel;
            }
            if(array_dimetion_num > 0) {
                (*node_type)->mArrayDimentionNum = array_dimetion_num;
                int i;
                for(i=0; i<array_dimetion_num; i++) {
                    (*node_type)->mArrayNum[i] = array_num[i];
                }
            }
            if(pointer_num > 0) {
                sNodeType* ppp = *node_type;
                ppp->mPointerNum += pointer_num;
            };
        }
    }
    else {
        if(((klass->mFlags & CLASS_FLAGS_STRUCT) || (klass->mFlags & CLASS_FLAGS_UNION)) && (klass->mFlags & CLASS_FLAGS_ANONYMOUS))
        {
            //(*node_type)->mClass = clone_class(klass);
            klass = (*node_type)->mClass;
            
            int i;
            for(i=0; i<klass->mNumFields; i++) {
                sNodeType* node_type = clone_node_type(klass->mFields[i]);
                if(!solve_generics(&node_type, generics_type))
                {
                    return FALSE;
                }
            }
        }

        int i;
        for(i=0; i<(*node_type)->mNumGenericsTypes; i++)
        {
            if(!solve_generics(&(*node_type)->mGenericsTypes[i], generics_type))
            {
                return FALSE;
            }
        }
    }

    if((*node_type)->mPointerNum == 0) {
        (*node_type)->mHeap = FALSE;
    }

    return TRUE;
}

BOOL solve_method_generics(sNodeType** node_type, int num_method_generics_types, sNodeType* method_generics_types[GENERICS_TYPES_MAX])
{
    sCLClass* klass = (*node_type)->mClass;

    if(type_identify_with_class_name(*node_type, "lambda")) 
    {
        if(!solve_method_generics(&(*node_type)->mResultType, num_method_generics_types, method_generics_types))
        {
            return FALSE;
        }

        int i;
        for(i=0; i<(*node_type)->mNumParams; i++)
        {
            if(!solve_method_generics(&(*node_type)->mParamTypes[i], num_method_generics_types, method_generics_types))
            {
                return FALSE;
            }
        }
    }
    else if(klass->mFlags & CLASS_FLAGS_METHOD_GENERICS)
    {
        int method_generics_number = klass->mMethodGenericsNum;

        if(method_generics_types[method_generics_number])
        {
            int array_dimetion_num = (*node_type)->mArrayDimentionNum;
            int array_num[ARRAY_DIMENTION_MAX];
            int i;
            for(i=0; i<array_dimetion_num; i++) {
                array_num[i] = (*node_type)->mArrayNum[i];
            }
            BOOL nullable = (*node_type)->mNullable;
            int pointer_num = (*node_type)->mPointerNum;
            BOOL heap = (*node_type)->mHeap;
            BOOL channel = (*node_type)->mChannel;

            BOOL no_heap = (*node_type)->mNoHeap;

            *node_type = clone_node_type(method_generics_types[method_generics_number]);

            if(heap) {
                (*node_type)->mHeap = heap;
            }
            if(no_heap) {
                (*node_type)->mHeap = FALSE;
            }
            if(nullable) {
                (*node_type)->mNullable = nullable;
            }
            if(channel) {
                (*node_type)->mChannel = channel;
            }
            if(array_dimetion_num > 0) {
                (*node_type)->mArrayDimentionNum = array_dimetion_num;
                int i;
                for(i=0; i<array_dimetion_num; i++) {
                    (*node_type)->mArrayNum[i] = array_num[i];
                }
            }
            if(pointer_num > 0) {
                (*node_type)->mPointerNum += pointer_num;
            }
        }
        else {
            return FALSE;
        }
    }
    else {
        int i;
        for(i=0; i<(*node_type)->mNumGenericsTypes; i++)
        {
            if(!solve_method_generics(&(*node_type)->mGenericsTypes[i], num_method_generics_types, method_generics_types))
            {
                return FALSE;
            }
        }
    }

    return TRUE;
}

BOOL is_typeof_type(sNodeType* node_type)
{
    BOOL result = FALSE;

    int i;
    for(i=0; i<node_type->mNumGenericsTypes; i++)
    {
        if(node_type->mGenericsTypes[i]->mTypeOfExpression) {
            result = TRUE;
        }
    }

    if(node_type->mTypeOfExpression) {
        result = TRUE;
    }

    return result;
}

BOOL solve_typeof(sNodeType** node_type, sCompileInfo* info)
{

    int i;
    for(i=0; i<(*node_type)->mNumGenericsTypes; i++)
    {
        if(!solve_typeof(&(*node_type)->mGenericsTypes[i], info))
        {
            return FALSE;
        }
    }

    unsigned int node = (*node_type)->mTypeOfExpression;

    if(node) {
        BOOL no_output = info->no_output;
        info->no_output = TRUE;
        if(!compile(node, info)) {
            compile_err_msg(info, "can't get type from typedef");
            info->err_num++;
            info->no_output = no_output;
            return TRUE;
        }
        info->no_output = no_output;

        dec_stack_ptr(1, info);

        *node_type = clone_node_type(info->type);
    }

    return TRUE;
}

BOOL get_type_of_method_generics(sNodeType* method_generics_types[GENERICS_TYPES_MAX], sNodeType* fun_param_type, sNodeType* param_type)
{
    sCLClass* klass = fun_param_type->mClass;

    if(klass->mFlags & CLASS_FLAGS_METHOD_GENERICS)
    {
        int method_generics_number = klass->mMethodGenericsNum;

        method_generics_types[method_generics_number] = clone_node_type(param_type);
    }

    if(fun_param_type->mNumGenericsTypes == param_type->mNumGenericsTypes) 
    {
        int i;
        for(i=0; i<fun_param_type->mNumGenericsTypes; i++)
        {
            if(!get_type_of_method_generics(method_generics_types, fun_param_type->mGenericsTypes[i], param_type->mGenericsTypes[i]))
            {
                return FALSE;
            }
        }
    }

    if(type_identify_with_class_name(fun_param_type, "lambda") 
        && type_identify_with_class_name(param_type, "lambda"))
    {
        if(!get_type_of_method_generics(method_generics_types, fun_param_type->mResultType, param_type->mResultType))
        {
            return FALSE;
        }

        int i;
        for(i=0; i<fun_param_type->mNumParams; i++)
        {
            if(!get_type_of_method_generics(method_generics_types, fun_param_type->mParamTypes[i], param_type->mParamTypes[i]))
            {
                return FALSE;
            }
        }
    }

    return TRUE;
}

BOOL included_generics_type(sNodeType* node_type, sCLClass* checked_class[], int* num_checked_class)
{
    sCLClass* klass = node_type->mClass;

    checked_class[*num_checked_class] = klass;
    (*num_checked_class)++;

    if(*num_checked_class >= STRUCT_FIELD_MAX) 
    {
        fprintf(stderr, "overflow struct field max at included_generics_type");
        exit(2);
    }

    if(type_identify_with_class_name(node_type, "lambda")) 
    {
        if(included_generics_type(node_type->mResultType, checked_class, num_checked_class))
        {
            return TRUE;
        }

        int i;
        for(i=0; i<node_type->mNumParams; i++)
        {
            if(included_generics_type(node_type->mParamTypes[i], checked_class, num_checked_class))
            {
                return TRUE;
            }
        }
    }
    else if(klass->mFlags & CLASS_FLAGS_GENERICS || klass->mFlags & CLASS_FLAGS_METHOD_GENERICS) 
    {
        return TRUE;
    }
    else {
        if((klass->mFlags & CLASS_FLAGS_STRUCT) || (klass->mFlags & CLASS_FLAGS_UNION))
        {
            int i;

            for(i=0; i<klass->mNumFields; i++) {
                sNodeType* field_type = clone_node_type(klass->mFields[i]);

                BOOL same_class = FALSE;
                int j;
                for(j=0; j<*num_checked_class; j++)
                {
                    if(field_type->mClass == checked_class[j])
                    {
                        if(field_type->mClass->mFlags & CLASS_FLAGS_GENERICS || field_type->mClass->mFlags & CLASS_FLAGS_METHOD_GENERICS) 
                        {
                            return TRUE;
                        }
                        else {
                            return FALSE;
                        }
                    }
                }

                if(included_generics_type(field_type, checked_class, num_checked_class))
                {
                    return TRUE;
                }
            }
        }

        int i;
        for(i=0; i<node_type->mNumGenericsTypes; i++)
        {
            if(node_type->mGenericsTypes[i]->mClass == klass || included_generics_type(node_type->mGenericsTypes[i], checked_class, num_checked_class))
            {
                return TRUE;
            }
        }
    }

    return FALSE;
}

void create_type_name_from_node_type(char* type_name, int type_name_max, sNodeType* node_type, BOOL neo_c)
{
    sCLClass* klass = node_type->mClass;

    xstrncat(type_name, CLASS_NAME(klass), type_name_max);

    if(node_type->mNumParams > 0) {
        xstrncat(type_name, "(", type_name_max);

        int i;
        for(i=0; i<node_type->mNumParams; i++) {
            create_type_name_from_node_type(type_name, type_name_max, node_type->mParamTypes[i], neo_c);
            
            if(i != node_type->mNumParams-1) {
                xstrncat(type_name, ",", type_name_max);
            }
        }
        xstrncat(type_name, ")", type_name_max);

        xstrncat(type_name, ":", type_name_max);

        create_type_name_from_node_type(type_name, type_name_max, node_type->mResultType, neo_c);
    }

    int pointer_num = node_type->mPointerNum;
    if(klass->mFlags & CLASS_FLAGS_STRUCT && neo_c)
    {
        pointer_num--;
    }

    int i;
    for(i=0; i<pointer_num; i++) {
        xstrncat(type_name, "*", type_name_max);
    }
    if(node_type->mNullable) {
        xstrncat(type_name, "?", type_name_max);
    }
    if(node_type->mHeap) {
        xstrncat(type_name, "%", type_name_max);
    }
    if(node_type->mChannel) {
        xstrncat(type_name, "~", type_name_max);
    }
    if(node_type->mNumGenericsTypes > 0) {
        xstrncat(type_name, "<", type_name_max);

        int i;
        for(i=0; i<node_type->mNumGenericsTypes; i++) {
            create_type_name_from_node_type(type_name, type_name_max, node_type->mGenericsTypes[i], neo_c);

            if(i != node_type->mNumGenericsTypes-1) {
                xstrncat(type_name, ",", type_name_max);
            }
        }

        xstrncat(type_name, ">", type_name_max);
    }
}
