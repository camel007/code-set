	int otsuThreshold(int * pIn, int W, int H, int stride)
	{
		int th = 0;
		float w0, w1;
		int sz = W*H;
		float sum0 = 0.0f,  sum1 = 0.0f;
		float mu0 = 0.0f, mu1 = 0.0f;
		int N0 = 0, N1 = 0;
		float var = 0.0f;
		int bestthreshold = th;

		std::vector<float> pixelProb(256, 0);

		int i, j;
		for(i = 0; i < 256; i++)
		{
			pixelProb[i] = (float)pIn[i]/sz;
		}

		for(th = 0; th <= 255; th++)
		{
			w0 = 0.0f, w1 = 0.0f, mu0 = 0.0f, mu1 = 0.0f, N0 = 0, N1 = 0;
			for(j = 0; j < 256; j++)
			{
				if(j <= th) //foreground
				{
					w0 += pixelProb[j];
					mu0 += j*pIn[j];
					N0 += pIn[j];
				}
				else//background
				{
					w1 += pixelProb[j];
					mu1 += j*pIn[j];
					N1 += pIn[j];
				}
			}
			mu0 = mu0/N0, mu1 = mu1/N1;
			float tmp = w0*w1*(mu0 - mu1)*(mu0 - mu1);
			if(var < tmp)
			{
				var = tmp;
				bestthreshold = th;
			}
		}

	return bestthreshold;
	}
