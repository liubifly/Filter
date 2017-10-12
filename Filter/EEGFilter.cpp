/*
	File: EEGFilter.cpp
	Created on: 2017.10.9
	Author: Bifei Liu

*/

#include "stdafx.h"
#include "EEGFilter.h"

using namespace std;


void EEGFilter::initCoeffs(int numFilters, double inputCoeffs[][5], double gain)
{
	overallGain = gain;
	coeffs.resize(numFilters);
	biquadCoeffs.resize(numFilters);
	for (int ii = 0; ii < numFilters; ii++)
	{
		coeffs[ii].b0 = inputCoeffs[ii][0];
		coeffs[ii].b1 = inputCoeffs[ii][1];
		coeffs[ii].b2 = inputCoeffs[ii][2];
		coeffs[ii].a1 = inputCoeffs[ii][3];
		coeffs[ii].a2 = inputCoeffs[ii][4];
	}
}

void EEGFilter::filter(float* input, float *output, int count)
{
	biquadCoeffs.processBiquad(input, output, 1, count, &coeffs[0]);
	for (int ii = 0; ii < count; ii++)
	{
		output[ii] *= overallGain;
	}
}