#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include "sbuf.h"

stSBUF_instance_t *SBUF_New(const int iWidth, const int iHeight)
{
	stSBUF_instance_t *pstInstance = (stSBUF_instance_t*)malloc(sizeof(stSBUF_instance_t));

	if(NULL == pstInstance)
		return NULL;

	pstInstance->pachBuf = (char*)malloc(sizeof(char) * iWidth * iHeight);

	if(NULL == pstInstance->pachBuf)
	{
		free(pstInstance);
		return NULL;
	}

	// Store the width and height
	pstInstance->iWidth = iWidth;
	pstInstance->iHeight = iHeight;

	// Initialize screenbuf
	SBUF_Clear(pstInstance);

	return pstInstance;
}

void SBUF_Delete(stSBUF_instance_t *pstInstance)
{
	if((NULL != pstInstance) && (NULL != pstInstance->pachBuf))
		free(pstInstance->pachBuf);

	if(NULL != pstInstance)
		free(pstInstance);

	return;
}

void SBUF_Print(stSBUF_instance_t *pstInstance)
{
	int x, y;

	// Check for bad input
	if((NULL == pstInstance) || (NULL == pstInstance->pachBuf))
	{
		return;
	}

	// Print the screen buffer to stdout
	for(y=0; y<pstInstance->iHeight; y++)
	{
		for(x=0; x<pstInstance->iWidth; x++)
		{
			printf("%c", SBUF_GetChar(pstInstance, x, y));
		}
		printf("\n");
	}

	return;
}

char SBUF_GetChar(stSBUF_instance_t *pstInstance, int x, int y)
{
	return pstInstance->pachBuf[x + y*pstInstance->iWidth];
}

void SBUF_SetChar(stSBUF_instance_t *pstInstance, int x, int y, char val)
{
	pstInstance->pachBuf[x + y*pstInstance->iWidth] = val;

	return;
}

void SBUF_Clear(stSBUF_instance_t *pstInstance)
{
	// Check for bad input
	if((NULL == pstInstance) || (NULL == pstInstance->pachBuf))
	{
		return;
	}

	// Set all the chars to spaces
	memset(pstInstance->pachBuf, ' ', (sizeof(char) * pstInstance->iWidth * pstInstance->iHeight));

	return;
}

