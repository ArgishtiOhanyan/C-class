#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

typedef struct 
{
    char **key; //yuraqanchur property-ii anun
    int  *offsets; // hamapatasxan indexner
    int  count; // property-neri qanak
}HiddenClass;

typedef char* JSValue;

typedef struct 
{
    HiddenClass *shape; // hxum depi hiden cllas, inch dashter uni u te vortex en  slots um
    char **slots;  //arjeqneri zangvac 
}JSObject;

HiddenClass *createHiddenClass(){    // functia vor uni hxum depi HiddenClass struct
    HiddenClass *a = malloc(sizeof(HiddenClass));
    a->key = NULL;   // ays mi qani toxum maqrum em malloci tvac hishoxutyun@ axbic
    a->offsets = NULL;
    a->count = 0;
    return a; 
}

JSObject *createObject(){ // datarka obyekts la der
    JSObject *obj = malloc(sizeof(JSObject));
    if(obj != NULL){
    obj->shape = createHiddenClass();   // nakaragrum e propert-ineri anunner@
    obj->slots = NULL;  // arjeqneri zangvac e vortex pahvum en propertyner@
    }
    return obj;
}

void addpropertyShape(HiddenClass *shape, const char *key){ //avelacnm em property i shape i mech
    shape->count++;  //avelacnum em qanak@
    shape->key = realloc(shape->key,shape->count * sizeof (char *));    // obshi mecacrel em zangvacner@ 
    shape->offsets = realloc(shape->offsets, shape->count * sizeof (int));

    if(shape->key != NULL && shape->offsets != NULL){
        shape->key[shape->count - 1] = malloc(strlen(key) + 1);  //hatkacnem tex
        strcpy(shape->key[shape->count - 1], key); // copy em anum teqst@
        shape->offsets[shape->count - 1] = shape->count - 1;  // talis em property i dirq@ zangvacum slots
    }
}

void js_setproperty(JSObject *obj,const char *key,JSValue value){   //avelacnm em property i objecti mech
    int found = -1;
    for(int i = 0; i < obj->shape->count; i++){         //stugum em ardyoq key arden ka shape um
        if(strcmp(obj->shape->key[i],key) == 0){
            found = i;
            break;
        }
    }
    if(found != -1){    // ete key ka taza arjeq em dnum slots um
        obj->slots[found] = value;
        return;
    }
    addpropertyShape (obj->shape, key);     // es nor property e
    obj->slots = realloc(obj->slots, obj->shape->count * sizeof(JSValue));   //mecacnum em slots zangvac@ arjeqner pahelu hamar

    int offset = obj->shape->count - 1;  // taza property arjeq@ dnum em ir offset um
    obj->slots[offset] = value;
}

JSValue js_getproperty(JSObject *obj, const char *key){  //het em talis property i arjeq@ shape i offset ov
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