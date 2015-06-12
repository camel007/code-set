#pragma once
#include <opencv.hpp>
#include "imShow.h"
#include "hAutoBuffer.h"

template<class T>
class boxfilter{
public:
	boxfilter()		{}
	~boxfilter()	{}

public:
	void execute(int W, int H, int step, T *pOut, T *pIn, int kW, int kH)
	{
		if(!pIn || !pOut) return;
		int hor_border = int(kW/2), ver_border = int(kH/2);
		int eW = W+2*hor_border, eH = H+2*ver_border, eStep = eW;

		hAutoBuffer<T> bordered;
		bordered.create(eW*eH);
		T *pBordered = bordered.ptr();
		makeBorder(pBordered, eW, eH, eStep, pIn, W, H, step, hor_border, ver_border);
 		filter(pOut, W, H, step, pBordered, eW, eH, eStep, kW, kH, hor_border, ver_border);
	}

private:
	void makeBorder(T *pOut, int oW, int oH, int oStep, T *pIn, int iW, int iH, int iStep, int hor_border, int ver_border)
	{
		if(!pIn || !pOut) return;
		if(oW != iW+2*hor_border || oH != iH+2*ver_border) return;
		T *pI = pIn, *pO = pOut;
		int i, j;
		T *pi, *po;

		for(j = 0; j < ver_border; j++, pO+=oStep)
		{
			po = pO, pi = pI;
			for(i = 0; i < hor_border; i++, po++)
			{
				*po = *pi;
			}
			for(i = 0; i < iW; i++, pi++, po++)
			{
				*po = *pi;
			}
			pi--;
			for(i = 0; i < hor_border; i++, po++)
			{
				*po = *pi;
			}
		}
		pI = pIn;
		for(j = 0; j < iH; j++, pI+=iStep, pO+=oStep)
		{
			pi=pI, po = pO;
			for(i = 0; i < hor_border; i++, po++)
			{
				*po = *pi;
			}
			for(i = 0; i < iW; i++, po++, pi++)
			{
				*po = *pi;
			}
			pi--;
			for(i = 0; i < hor_border; i++, po++)
			{
				*po = *pi;
			}
		}
		pI-=iStep;
		for(j = 0; j < ver_border; j++, pO+=oStep)
		{
			pi=pI, po = pO;
			for(i = 0; i < hor_border; i++, po++)
			{
				*po = *pi;
			}
			for(i = 0; i < iW; i++, po++, pi++)
			{
				*po = *pi;
			}
			pi--;
			for(i = 0; i < hor_border; i++, po++)
			{
				*po = *pi;
			}
		}
		//hShow(pOut, oW, oH, 1, oW, 0, _T("border"));
		//hWaitKey();
	}
	void filter(T* pOut, int oW, int oH, int oStep, T* pIn, int iW, int iH, int iStep, int kW, int kH, int hor_boder, int ver_bor)
	{
		if(!pOut || !pIn) return;
		T* pO = pOut, *pI = pIn, *pi, *po;
		int i,j;
		float factor = 1.0f/(kW*kH);
		for(j = 0; j < oH; j++, pO+=oStep, pI+=iStep)
		{
			pi = pI, po = pO;
			for(i = 0; i < oW; i++, pi++, po++)
			{
				float s = 0.0f;
				sum(s, pi, kW, kH, iStep);
				*po = (T)(s*factor);
			}
		}
		//hShow(pOut, oW, oH, 1, oStep, 0, _T("filtered"));
		//hWaitKey();
	}
	void sum(float &s, T *pIn, int W, int H, int stride)
	{
		T *pI = pIn, *pi;
		int i,j;
		float su = 0.0f;
		for(j = 0; j < H; j++, pI+=stride)
		{
			for(pi = pI, i = 0; i < W; i++, pi++)
			{
				su += (float)(*pi);
			}
		}
		s = su;
	}
};