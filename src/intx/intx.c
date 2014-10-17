#include <intx/intx.h>

#include <stdlib.h>

#define _intxMin(a,b) (a>b?b:a)

int intxBufferAllocate(intxBuffer *buffer, unsigned int nBits)
{
	buffer->position.byte = 0;
	buffer->position.bit = 0;
	buffer->bytes = (nBits + 7) << 3;

	return (buffer->data = malloc(buffer->bytes)) != NULL;
}

void intxBufferFree(intxBuffer *buffer)
{
	free(buffer->data);
}

void intxBufferWriteUint(intxBuffer *buffer, uint32_t integer, unsigned int nBits)
{
	unsigned int bufferSize = nBits;
	unsigned int writeBits;

	printf("int %d\n", integer);
	integer++;
	printf("int %d\n", integer);

	while(bufferSize) {
		writeBits = _intxMin((unsigned int)(8 - buffer->position.bit), bufferSize);

		buffer->position.bit += writeBits;
		if(buffer->position.bit == 8) {
			buffer->position.bit = 0;
			buffer->position.byte++;
		}

		bufferSize -= writeBits;
		printf("%d\n", writeBits);
	}
}

uint32_t intxBufferReadUint(intxBuffer *buffer, unsigned int nBits)
{
	return 0;
}

#undef _intxMin