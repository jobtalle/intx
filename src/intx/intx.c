#include <intx/intx.h>

#include <stdlib.h>

#define _intxMin(a,b) a<b?a:b

static intxWord mask[INTX_WORDSIZE];

int intxBufferAllocate(intxBuffer *buffer, unsigned int nBits)
{
	if(mask[0] == 0) {
		int i;
		for(i = 0; i < INTX_WORDSIZE; i++) {
			mask[i] = (2 << i) - 1;
		}
	}

	buffer->position.word = 0;
	buffer->position.bit = 0;
	buffer->words = (nBits + INTX_WORDSIZE - 1) / INTX_WORDSIZE;

	return (buffer->data = calloc(buffer->words, sizeof(intxWord))) != NULL;
}

void intxBufferFree(intxBuffer *buffer)
{
	free(buffer->data);
}

void intxBufferWriteUint(intxBuffer *buffer, unsigned int integer, unsigned int nBits)
{
	unsigned int writeBits;

	while(nBits) {
		writeBits = _intxMin((unsigned int)(INTX_WORDSIZE - buffer->position.bit), nBits);

		buffer->data[buffer->position.word] |= ((integer >> (nBits - writeBits)) & mask[writeBits - 1]) << (INTX_WORDSIZE - writeBits - buffer->position.bit);

		buffer->position.bit += writeBits;
		if(buffer->position.bit == INTX_WORDSIZE) {
			buffer->position.bit = 0;
			buffer->position.word++;
		}

		nBits -= writeBits;
	}
}

void intxBufferWriteInt(intxBuffer *buffer, int integer, unsigned int nBits)
{
	if(integer < 0) integer |= 1 << (nBits - 1);

	intxBufferWriteUint(buffer, (unsigned int)integer, nBits);
}

unsigned int intxBufferReadUint(intxBuffer *buffer, unsigned int nBits)
{
	unsigned int integer = 0;
	unsigned int readBits;

	while(nBits) {
		readBits = _intxMin((unsigned int)(INTX_WORDSIZE - buffer->position.bit), nBits);

		integer = (integer << readBits) | ((buffer->data[buffer->position.word] >> (INTX_WORDSIZE - buffer->position.bit - readBits)) & mask[readBits - 1]);

		buffer->position.bit += readBits;
		if(buffer->position.bit == INTX_WORDSIZE) {
			buffer->position.bit = 0;
			buffer->position.word++;
		}

		nBits -= readBits;
	}

	return integer;
}

int intxBufferReadInt(intxBuffer *buffer, int nBits)
{
	int integer = intxBufferReadUint(buffer, nBits);

	if(integer & (1 << (nBits - 1))) integer = (integer & ~(1 << (nBits - 1))) - (1 << (nBits - 1));

	return integer;
}

#undef _intxMin