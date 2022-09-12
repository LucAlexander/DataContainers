CC=gcc
CCWIN=x86_64-w64-mingw32-gcc

build:
	mkdir object
	$(CC) -c ./src/vector/vector.c -o ./object/vector.o
	$(CC) -c ./src/hashMap/hashMap.c -o ./object/hashMap.o
	ar rcs libDataContainers.a ./object/*.o

build-win:
	mkdir object
	$(CCWIN) -c ./src/vector/vector.c -o ./object/vector.o
	$(CCWIN) -c ./src/hashMap/hashMap.c -o ./object/hashMap.o
	ar rcs libDataContainers.dll ./object/*.o

clean:
	rm -rf ./object
	rm -rf libDataContainers.a
	rm -rf libDataContainers.dll

rebuild:
	make clean
	make build
