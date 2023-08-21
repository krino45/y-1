all:
	gcc -c PlayKey.c -fPIC
	gcc PlayKey.o -shared -o libPlayKey.so
	gcc -c main.c
	gcc -o PlayKey main.o -L. -lPlayKey -Wl,-rpath,.