#include <intx/intx.h>

#include <stdlib.h>

int intxBufferAllocate(intxBuffer *buffer, int nBits)
{
	buffer->position.byte = 0;
	buffer->position.bit = 0;

	return (buffer->data = malloc((nBits + 7) / 8)) != NULL;
}

void intxBufferFree(intxBuffer *buffer)
{
	free(buffer->data);
}

int intxBufferWriteUint(intxBuffer *buffer, unsigned int integer, int nBits)
{

}

unsigned int intxBufferReadUint(intxBuffer *buffer, int nBits)
{

}