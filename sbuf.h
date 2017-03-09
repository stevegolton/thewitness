#ifndef SBUF_H_
#define SBUF_H_

typedef struct
{
	char *pachBuf;
	int iWidth;
	int iHeight;

} stSBUF_instance_t;

stSBUF_instance_t *SBUF_New(const int x, const int y);
void SBUF_Delete(stSBUF_instance_t *pstInstance);
void SBUF_Print(stSBUF_instance_t *pstInstance);
void SBUF_SetChar(stSBUF_instance_t *pstInstance, int x, int y, char val);
char SBUF_GetChar(stSBUF_instance_t *pstInstance, int x, int y);
void SBUF_Clear(stSBUF_instance_t *pstInstance);

#endif /* SBUF_H_ */
