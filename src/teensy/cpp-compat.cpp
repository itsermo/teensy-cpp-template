// The functions contained in this file are to provide some
// tieing of loose ends to support C++ compiling on gcc-arm-none-eabi
// which does not provide implementations of these necessary C++ constructs
#include <stdlib.h>

void __cxa_exit (void) { }

void __cxa_pure_virtual (void) { }

void * operator new(size_t size)
{
	return malloc(size);
}

void * operator new[](size_t size)
{
	return malloc(size);
}

void operator delete(void * ptr)
{
	free(ptr);
}

void operator delete[](void * ptr)
{
	free(ptr);
}

void operator delete(void * ptr, size_t size)
{
	free(ptr);
}

void operator delete[](void * ptr, size_t size)
{
	free(ptr);
}

extern "C" {
__attribute__((weak))
int _write(int file, char *ptr, int len)
{
	// TODO: for iostreams cout
	return 0;
}
}