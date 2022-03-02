CC=gcc

build:
	mkdir object
	$(CC) -c ./src/vector/vector.c -o ./object/vector.o
	$(CC) -c ./src/hashMap/hashMap.c -o ./object/hashMap.o
	$(CC) -c ./src/queue/queue.c -o ./object/queue.o
	ar rcs libDataContainers.a ./object/*.o

clean:
	rm -rf ./object
	rm -rf libDataContainers.a

rebuild:
	make clean
	make build
