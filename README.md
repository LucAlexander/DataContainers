# Description
This is simple statically linked data container library for C projects. They are type safe, and defined mostly through pre-processor directives.
# Documentation (WIP)
Data containers are not a single struct type in this library, but you can define custom types with any given container data type through a pre-processor function. You define those types at the start of the program, and you can then use them at will.
## Building
To build this project as a static library, call the make target `make build`.
## Hash Map
To define a hash map type call the declaration function `HASHMAP(typename, keyType, valType)`. The first argument will be the data type of your hashmap, the second and third argument are they key and value data types of the hashmap.

Example usage to implement a mapping from c style strings to integers:
```
HASHMAP(myMap, const char*, int)
```

This custom type will be defined in-macro as
```
typedef struct typename{
	typename##TSHM_NODE** data;
	uint32_t capacity;
	uint32_t size;
}typename; \
```

It is reccommended you put this in a header to complement the definition function `HASHMAP_SOURCE(typename, keyType, valType, hashing)`, the final argument in this macro function is a reference to a hashing function which operates on your key type.

Example usage:
```
HASHMAP_SOURCE(myMap, const char*, int, hashS)
```

It is recommended that you put this in some `.c` source file corresponding with the header you put the declaration function in.

You may now use your defined hashmap type like any other data structure, initializing it with `typename typename##Init();`.
```
myMap map = myMapInit();
```

**Function summary**
- `typename typename##Init();`
- `void typename##Free(typename* map);`
- `void typename##Push(typename* map, keyType key, valType val);`
- `typename##Result typename##Get(typename* map, keyType key);`
- `valType* typename##Ref(typename* map, keyType key);`
- `uint8_t typename##Contains(typename* map, keyType key);`
- `typename##Result typename##Pop(typename* map, keyType key);`
- `void typename##Clear(typename* map);`
- `keyType* typename##GetKeySet(typename* map);`
- `typename##Iterator typename##IteratorInit(typename* map);`
- `typename##Result typename##IteratorNext(typename##Iterator* it);`
- `uint8_t typename##IteratorHasNext(typename##Iterator* it);`

Following the example of our `myMap` type, for every `myMap myMapInit();`, you must have a `void myMapFree(myMap*);`.
```
myMap map = myMapInit();

...

myMapFree(&map);
```
To add a mapping to a defined type `myMap`, use `void myMapPush(myMap*, const char*, int);`.
```
myMap map = myMapInit();
myMapPush(&map, "Parrot count", 5);
myMapFree(&map);
```

To access a mapping from a defined type `myMap` use either `myMapResult myMapGet(myMap*, const char*);`, which uses a predefined result type to pack data, or use `int* myMapRef(myMap* const char*)` which returns a raw pointer reference to the value stored in the map.
```
myMap map = myMapInit();
...

// to access copies of mappings
myMapResult data = myMapGet(&map, "Parrot count");

// or to access directly 
*(myMapRef(&map, "Parrot count")) = 6;

...
```

This result type is defined in-macro as
```
typedef struct typename##Result{
	uint8_t error;
	keyType key;
	valType val;
}typename##Result;
```

To check whether some defined type `myMap` contains some mapping key, use `uint8_t myMapContains(myMap*, const char*);`.
```
myMap map = myMapInit();

...


if (myMapContains(&map, "Parrot count")){
	myMapResult data = myMapGet(&map, "Parrot count");
	printf("%s : %d\n", data.key, data.val);
}

...
```

To retrieve, and remove, some mapping of a defined type `myMap`, call `myMapResult myMapPop(myMap*, const char*);`.
```
myMap map = myMapInit();

...


if (myMapContains(&map, "Parrot count")){
	myMapResult data = myMapPop(&map, "Parrot count");
	printf("%s : %d\n", data.key, data.val);
}

...
```

To clear all data from a defined type `myMap`, call `void myMapClear(myMap*);`.
```
myMap map = myMapInit();

...

if (map.size > 0){
	myMapClear(&map);
}

...
```

### Iteration
There are two ways to iterate any hash map. This library implements both. The first is to retrieve some collection of all keys which exist in the mapping. For some defined type `myMap` this can be done with `const char** myMapGetKeySet(myMap*);`.
```
myMap map = myMapInit();

...

const char** keySet = myMapGetKeySet(&map);
int i;
for (i = 0;i<map.size;++i){
	int value = myMapGet(&map, keySet[i]).val;
}
```

The other manner to iterate is with an actual "data generator function" style iterator. For some defined type `myMap`, you can create an iterator of type `myMapIterator` as
```
myMap map = myMapInit();

...

myMapIterator it = myMapIteratorInit(&map);
while(myMapIteratorHasNext(&it)){
	int value = myMapIteratorNext(&it).val;
}
```

## Vector

## Queue

