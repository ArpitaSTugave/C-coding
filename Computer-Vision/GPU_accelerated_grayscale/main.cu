#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <string>
#include <cuda.h>
#include <stdio.h>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <iostream>

__global__ void rgb_2_grey(unsigned char* greyImage, unsigned char* rgbImage, int rows, int cols)
{
    int rgb_x = blockIdx.x * blockDim.x + threadIdx.x; //x coordinate of pixel
    int rgb_y = blockIdx.y * blockDim.y + threadIdx.y; //y coordinate of pixel

    if ((rgb_x >= cols) && (rgb_y >= rows)) {
        return;
    }

	int gray_adr = rgb_y*cols + rgb_x; //absolute pixel position
	int clr_adr = 3 * gray_adr;       // calculating address for reading RGB values

	if (gray_adr < (rows * cols))
	{
		double gray_val = 0.144*rgbImage[clr_adr] + 0.587*rgbImage[clr_adr + 1] + 0.299*rgbImage[clr_adr + 2];
		greyImage[gray_adr] = (unsigned char)gray_val;
	}
}

//   Kernel Calling Function

extern "C" void gray_parallel(unsigned char* h_in, unsigned char* h_out, int elems, int rows, int cols){

	unsigned char* d_in;
	unsigned char* d_out;
	const int BS = 16;
	const dim3 blockSize(BS, BS);
	const dim3 gridSize((cols / BS) + 1, (rows / BS) + 1);
	cudaMalloc((void**)&d_in, elems);
	cudaMalloc((void**)&d_out, rows*cols);

	cudaMemcpy(d_in, h_in, elems*sizeof(unsigned char), cudaMemcpyHostToDevice);
	rgb_2_grey << < gridSize, blockSize >> >(d_out, d_in, rows, cols);

	cudaMemcpy(h_out, d_out, rows*cols*sizeof(unsigned char), cudaMemcpyDeviceToHost);
	cudaFree(d_in);
	cudaFree(d_out);
}