#pragma once
#include <cv.h>

class integralGraph{
public:
	integralGraph()			{}
	~integralGraph()		{}

	//oW = iW + 2*extBorder + 1, oH = iH + 2*extBorder + 1
	void create(float *pSum, int oW, int oH, int oStride, unsigned char *pIm, int iW, int iH, int iStride, int top, int bottom, int left, int right)
	{
		float *pS = pSum;
		unsigned char *pI = pIm;
		
		
		//first line set 0
		memset(pS, 0, sizeof(float)*oStride);
		pS+=oStride;
		int i;
		for(i = 0; i < top; i++, pS+=oStride)
		{
			sumRow(iW, pS, oStride, pI, left, right);
		}
		for(i = 0; i < iH; i++, pS+=oStride, pI+=iStride)
		{
			sumRow(iW, pS, oStride, pI, left, right);
		}
		for(pI-=iStride, i = 0; i < bottom; i++, pS+=oStride)
		{
			sumRow(iW, pS, oStride, pI, left, right);
		}
	}

private:
	void sumRow(int W, float *pOut, int oStride, unsigned char *pIn, int left, int right)
	{
		float *po = pOut;
		unsigned char *pi = pIn;
		int i, j;
		*po++ = 0;
		float sum = 0.0f;
		for(i = 0; i < left; i++, po++)
		{
			sum+=*pi;
			*po = float(po[-oStride] + sum);
		}
		for(i = 0; i < W; i++, po++, pi++)
		{
			sum+=*pi;
			*po = float(po[-oStride] + sum);
		}
		for(pi--, i = 0; i < right; i++, po++)
		{
			sum+=*pi;
			*po = float(po[-oStride] + sum);
		}
	}
};