#include <intx/intx.h>

#include <stdlib.h>

#define _intxMin(a,b) (a>b?b:a)

static uint8_t mask[8] = {
	1,
	3,
	7,
	15,
	31,
	63,
	127,
	255
};

int intxBufferAllocate(intxBuffer *buffer, unsigned int nBits)
{
	buffer->position.byte = 0;
	buffer->position.bit = 0;
	buffer->bytes = (nBits + 7) >> 3;

	return (buffer->data = calloc(buffer->bytes, 1)) != NULL;
}

void intxBufferFree(intxBuffer *buffer)
{
	free(buffer->data);
}

void intxBufferWriteUint(intxBuffer *buffer, uint32_t integer, unsigned int nBits)
{
	unsigned int bufferSize = nBits;
	unsigned int writeBits;

	while(bufferSize) {
		writeBits = _intxMin((unsigned int)(8 - buffer->position.bit), bufferSize);
		printf("Write %d bits\n", writeBits);

		buffer->data[buffer->position.byte] <<= writeBits;
		buffer->data[buffer->position.byte] |= (integer >> (bufferSize - writeBits)) & mask[writeBits - 1];

		buffer->position.bit += writeBits;
		if(buffer->position.bit == 8) {
			buffer->position.bit = 0;
			buffer->position.byte++;
		}

		for(int i = writeBits - 1; i >= 0; i--) {
			printf("%d", ((integer >> (bufferSize - writeBits)) >> i) & 1);
		}
		printf("\n");

		bufferSize -= writeBits;
	}
}

uint32_t intxBufferReadUint(intxBuffer *buffer, unsigned int nBits)
{
	uint32_t integer = 0;
	unsigned int bufferSize = nBits;
	unsigned int readBits;

	while(bufferSize) {
		readBits = _intxMin((unsigned int)(8 - buffer->position.bit), bufferSize);
		//printf("Rshift %d\n", (8 - buffer->position.bit - readBits));
		integer <<= readBits;
		integer |= (buffer->data[buffer->position.byte] >> (8 - buffer->position.bit - readBits)) & mask[readBits - 1];
		/*
		for(int i = nBits - 1; i >= 0; i--) {
			printf("%d",(integer >> i) & 1);
		}
		printf("\n");
		*/
		buffer->position.bit += readBits;
		if(buffer->position.bit == 8) {
			buffer->position.bit = 0;
			buffer->position.byte++;
		}

		bufferSize -= readBits;
	}

	return integer;
}

#undef _intxMin