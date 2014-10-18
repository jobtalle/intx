intx
====

A small library to store and read integers whose bit count is not a multiple of 8. Intx is demonstrated in the example code below.

```C
#include <stdio.h>
#include <intx/intx.h>

int main(int argc, char **argv)
{
	int i;
	
	// 10 values will be stored, each represented by 5 bits, starting with 16
	int valueAmount = 10;
	int bitsPerInt = 5;
	unsigned int value = 16;
	
	// The buffer that will be used for reading and writing
	intxBuffer buffer;

	// The buffer is allocated with enough space to store all numbers
	intxBufferAllocate(&buffer, valueAmount * bitsPerInt);

	// value is written to the buffer 10 times, every time incremented by one
	for(i = 0; i < valueAmount; i++) {
		intxBufferWriteUint(&buffer, value, bitsPerInt);
		value++;
	}

	// The buffer position is set to zero again, so we can read from the beginning
	buffer.position.bit = 0;
	buffer.position.word = 0;

	// The numbers 16 to 25 were stored in the buffer and will be printed
	for(i = 0; i < valueAmount; i++) {
		printf("%d\n", intxBufferReadUint(&buffer, bitsPerInt));
	}

	// The buffer is freed
	intxBufferFree(&buffer);
	
	return 0;
}
```
