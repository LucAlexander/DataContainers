# Description
This is simple statically linked data container library for C projects. They are type safe, and defined mostly through pre-processor directives.
# Documentation 
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
### General
To create a custom Vector type call the function `VECTOR(typename, type)`. The first argument deisgnates the typename of your new type, the second argument designates the type it takes.
Example usage to implement a vector of integers:
```
VECTOR(V32, int)
```

The vector struct this generates is in the form
```
typedef struct typename{ \
	type* data; \
	uint32_t capacity; \
	uint32_t size; \
}typename; \

```

It is reccommended you put this in a header file to complement the definition function `VECTOR_SOURCE(typename, type)`, which should be placed in some implementation `.c` file.

```
VECTOR_SOURCE(V32, int)
```

You may now use your defined vector type by calling the `typename typename##Init();` function as
```
V32 vec = V32Init();
```

**Function Summary**
- `typename typename##Init();`
- `void typename##Free(typename* vec);`
- `void typename##PushBack(typename* vec, type item);`
- `void typename##Insert(typename* vec, uint32_t index, type item);`
- `uint32_t typename##PushInOrder(typename* vec, type item, int8_t(*comparator)(type, type));`
- `void typename##Reserve(typename* vec, uint32_t places);`
- `type typename##Get(typename* vec, uint32_t index);`
- `type typename##GetTruested(typename* vec, uint32_t index);`
- `type* typename##Ref(typename* vec, uint32_t index);`
- `type* typename##RefTrusted(typename* vec, uint32_t index);`
- `void typename##Set(typename* vec, uint32_t index, type item);`
- `void typename##SetTrusted(typename* vec, uint32_t index, type item);`
- `type typename##RemoveInOrder(typename* vec, uint32_t index);`
- `type typename##Remove(typename* vec, uint32_t index);`
- `type typename##Pop(typename* vec);`
- `void typename##Clear(typename* vec);`
- `typename##Iterator typename##IteratorInit(typename* vec);`
- `uint8_t typename##IteratorHasNext(typename##Iterator* it);`
- `type typename##IteratorNext(typename##Iterator* it);`

Following the example of our custom vector type `V32`, for every `V32Init();`, you must call a `V32Free(V32*);`.
```
V32 vec = V32Init();

...

V32Free(&vec);
```

To add to a defined vector type `V32` you have three options. If you would simply like to add it to the end, use `V32PushBack(V32*, int data);`. If you would like to insert the element at some other position, use `V32Insert(V32*, uint32_t index, int data);`. And finally if you would like to insert the item with some ordering in mind, use `V32PushInOrder(V32*, int data, int8_t(*comparator)(int, int));`, The final argument in this function represents a pointer to a function which takes two variables of the vectors container type and returns comparison information about the two elements. This is the function it uses to order elements.

**By default you are provided the following build in comparators**
- `int8_t u8Compare(uint8_t a, uint8_t b);`
- `int8_t u16Compare(uint16_t a, uint16_t b);`
- `int8_t u32Compare(uint32_t a, uint32_t b);`
- `int8_t u64Compare(uint64_t a, uint64_t b);`
- `int8_t i8Compare(int8_t a, uint8_t b);`
- `int8_t i16Compare(int16_t a, uint16_t b);`
- `int8_t i32Compare(int32_t a, uint32_t b);`
- `int8_t i64Compare(int64_t a, uint64_t );`

Whatever comparator you end up using should return 0 on equallity, -1 on less than, and 1 on greater than. 

Example usage insert functions:
```
V32 vec = V32Init();

V32PushBack(&vec, 5); // insert 5 at end of list
V32Insert(&vec, 0, 3); // insert 3 at the beginning of the list
V32PushInOrder(&vec, 4, i32Compare); // insert 4 in order in the list

V32Free(&vec);
```

As an optimization strategy with resizing array-like data structures, you may want to reserve some capacity so that extraneous resizes do not have to occur. In order to accomplish this with some predefined `V32` call its reserve function as
```
V32Reserve(V32*, uint32_t places);
```

which will ensure that that many new places are available for future operations without any extraneous resizing.

There are four available functions to reference data within some defined vector type `V32`. To get a copy of the data at a position in the vector use `int V32Get(V32*, uint32_t index);`. To retrieve a reference to the posiiton in the vector where a value is stored use `int* V32Ref(V32*, uint32_t index);`. There also exist "trusted" versions of these two functions which assume that the index you are passing is within the bounds of the vector. The only difference is they have one less conditional statement.
```
V32 vec = V32Init();

...

int a = V32Get(&vec, 0);
int* b = V32Ref(&vec, 8);
*b = 3; // changes the value of vec at position 8 to 3

...
```

Another way to change the value of an item in a vector is to call `void V32Set(V32*, uint32_t index, int item);`, this function also has a trusted version.
```
V32 vec = V32Init();

...

V32Set(&vec, 4, 5); // set index 4 to value 5 

...
```

To remove an item from a `V32` type vector use `int V32Remove(V32*, uint32_t index);`, this returns the value you removed. For efficiency sake, this function does not maintain the order of the function, in order to retain the order, call `int V32RemoveInOrder(V32*, uint32_t index);`
To simply remove the last element in a `V32` typed vector, use `int V32Pop(V32*);`, which similarly returns the element being removed.
```
V32 vec = V32Init();

...

int last = V32Pop(&vec);
int item = V32Remove(&vec, 4);

...
```

Alternatively if you want to clear the whole vector, use `V32Clear(V32*);`

### Iteration
You may use any accessor function mentioned to do manual iteration, however there is a built in data generator function style iterator for each defined vector type.
```
V32 vec = V32Init();

...

V32Iterator it = V32IteratorInit(&vec);
while (V32IteratorHasNext(&it)){
	int value = V32IteratorNext(&it);
}

...
```

### CVector
CVector is a predefined type build separately to work with `void*` as its type. It has a separate definition but has all the same functions and abilities.

## Queue
To define a queue type call the declaration function `QUEUE(typename, type)`, preferably in a header. The struct this will generate will be in the form
```
typedef struct typename{
	typename##TSQ_NODE* head;
	typename##TSQ_NODE* end;
	uint32_t size; 
}typename; 
```

Then call its definition function `QUEUE_SOURCE(typename, type)`.
```
QUEUE(q, char)

...

QUEUE(q, char)

```

To create an instance of this custom defined type, call it initialization function `typename##Init();` as 
```
q myq = qInit();

```

Note that for every `qInit();` there must eventually follow a `qFree(q*);`.
```
q myq = qInit();

...


qFree(&myq);
```

Queues have two simple operations, push and pop. For some type `q`, using `void qPush(q*, char data);`will add an element of type `char` to the end of the queue. Whereas `char qPop(q*);` will remove and return the `char` at the front of the queue.
```
q myq = qInit();

qPush(&myq, 'a');
qPush(&myq, 'b');
qPush(&myq, 'c');
qPush(&myq, 'd');
qPush(&myq, 'e');

qPop(&myq); // pops a
qPop(&myq); // pops b
qPop(&myq); // pops c
qPop(&myq); // pops d
qPop(&myq); // pops e

qFree(&myq);

```


