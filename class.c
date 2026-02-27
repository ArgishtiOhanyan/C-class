#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

typedef struct 
{
    char **key; 
    int  *offsets; 
    int  count; 
}HiddenClass;

typedef char* JSValue;

typedef struct 
{
    HiddenClass *shape; 
    char **slots; 
}JSObject;

HiddenClass *createHiddenClass(){  
    HiddenClass *a = malloc(sizeof(HiddenClass));
    a->key = NULL; 
    a->offsets = NULL;
    a->count = 0;
    return a; 
}

JSObject *createObject(){ 
    JSObject *obj = malloc(sizeof(JSObject));
    if(obj != NULL){
    obj->shape = createHiddenClass();   
    obj->slots = NULL;
    }
    return obj;
}

void addpropertyShape(HiddenClass *shape, const char *key){
    shape->count++;  //avelacnum em qanak@
    shape->key = realloc(shape->key,shape->count * sizeof (char *));  
    shape->offsets = realloc(shape->offsets, shape->count * sizeof (int));

    if(shape->key != NULL && shape->offsets != NULL){
        shape->key[shape->count - 1] = malloc(strlen(key) + 1);
        strcpy(shape->key[shape->count - 1], key); 
        shape->offsets[shape->count - 1] = shape->count - 1; 
    }
}

void js_setproperty(JSObject *obj,const char *key,JSValue value){ 
    int found = -1;
    for(int i = 0; i < obj->shape->count; i++){         
        if(strcmp(obj->shape->key[i],key) == 0){
            found = i;
            break;
        }
    }
    if(found != -1){ 
        obj->slots[found] = value;
        return;
    }
    addpropertyShape (obj->shape, key);
    obj->slots = realloc(obj->slots, obj->shape->count * sizeof(JSValue)); 

    int offset = obj->shape->count - 1;
    obj->slots[offset] = value;
}

JSValue js_getproperty(JSObject *obj, const char *key){ 
    for(int i = 0; i < obj->shape->count; i++){
        if(strcmp(obj->shape->key[i],key) == 0){
            int offset = obj->shape->offsets[i];
            return obj->slots[offset];
        }
    }

    JSValue empty = NULL;
    return empty;
}

int main (void) {
    JSObject *person = createObject();

    js_setproperty(person, "name","Poxos");
    js_setproperty(person, "surname","Poxosyan");
    js_setproperty(person, "position", "Director");
    js_setproperty(person, "age", "20");

    printf("name : %s\n", js_getproperty(person,"name"));
    printf("surname : %s\n", js_getproperty(person,"surname"));
    printf("position : %s\n", js_getproperty(person,"position"));
    printf("age: %s\n", js_getproperty(person, "age"));
    return 0;
}
