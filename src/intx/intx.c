#include <intx/intx.h>

#include <stdlib.h>

int intxAllocateBuffer(intxBuffer *buffer, int nBits)
{
	buffer->position.byte = 0;
	buffer->position.bit = 0;

	return (buffer->data = malloc((nBits + 7) / 8)) != NULL;
}

void intxFreeBuffer(intxBuffer *buffer)
{
	free(buffer->data);
}