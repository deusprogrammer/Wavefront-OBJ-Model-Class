#include <string.h>
#include <stdio.h>
#include <stdlib.h>

inline void SWAP(char *buff,int n)
{
#ifdef X86_CPU
	return;
#endif
#ifdef WIN32
	return;
#endif
	for(int i=0;i<n/2;i++)
	{
		char c = buff[i];
		buff[i] = buff[n-1-i];
		buff[n-1-i] = c;
	}
}

class CBmp
{
private:
	unsigned char *m_pDibBuffer;
	unsigned char  type[2];
	unsigned int size;
	unsigned short int reserv1, reserv2;
	unsigned int offset;

	unsigned int sizeHeader;		/* Header size in bytes     */
	int width, height;				/* Width and height of image*/
	unsigned short int planes;		/* Number of colour planes  */
	unsigned short int bits;		/* Bits per pixel           */
	unsigned int compression;		/* Compression type         */
	unsigned int imagesize;			/* Image size in bytes      */
	int xres, yres;					/* Pixels per meter         */
	unsigned int ncolours;			/* Number of colours        */
	unsigned int importantcolours;	/* Important colours        */
	unsigned char *pallete;			/* ncolors*4				*/
	double *buffRealGaussian;
	int *buffIEdgeGaussian;
	char fileName[64];
public:
	CBmp(char *filename)
	{
		m_pDibBuffer=NULL;
		strcpy(fileName,filename);
	}
	int getWidth()
	{
		return width;
	}
	int getHeight()
	{
		return height;
	}
	unsigned char *getBuffer(int mode)
	{
		return m_pDibBuffer;
	}
	bool init()
	{
		m_pDibBuffer = NULL;
		width = height = 0;
		FILE *fp;
		fp = fopen(fileName,"rb");
		if(fp==NULL)
			return false ;
#define READ_INT(a) fread(&a,1,4,fp); SWAP((char*)&a,4);
#define READ_SHORT(a) fread(&a,1,2,fp);SWAP((char*)&a,2);
		fread(type,1,2,fp);
		READ_INT(size);
		READ_SHORT(reserv1);
		READ_SHORT(reserv2);
		READ_INT(offset);
		READ_INT(sizeHeader);
		READ_INT(width);
		READ_INT(height);
		READ_SHORT(planes);
		READ_SHORT(bits);
		READ_INT(compression);
		READ_INT(imagesize);
		READ_INT(xres);
		READ_INT(yres);
		READ_INT(ncolours);
		READ_INT(importantcolours);

		int nWidth = 1,
			nHeight = 1;

		while(nWidth<=width)
			nWidth=nWidth<<1;

		while(nHeight<=height)
			nHeight=nHeight<<1;

		if(nWidth>nHeight)
			nHeight=nWidth;
		else
			nWidth=nHeight;

		nWidth=1024;
		nHeight=1024;
		unsigned char *readbuff = NULL;

		m_pDibBuffer = new unsigned char[nWidth*nHeight*3];
		readbuff = new unsigned char[(width+1)*height*3];
		int totalbytes=fread(readbuff,(width+1)*3,height,fp);

		for(int i=nHeight-1;i>=0;i--)
		{
			for(int j=nWidth-1;j>=0;j--)
			{
				int m,n;
				m=height*i/nHeight;
				n=width*j/nWidth;
				unsigned char *p1,*p2,*p3;
				p1 = m_pDibBuffer+(i*nWidth+j)*3;
				p2 = readbuff+(m)*width*3+(n)*3;
				p1[0]=p2[0];
				p1[1]=p2[1];
				p1[2]=p2[2];
			}
		}
		delete readbuff;
		width = nWidth;
		height = nHeight;
#undef READ_INT
#undef READ_SHORT 
	}
	void freeBuffer()
	{
		delete m_pDibBuffer;
	}
};