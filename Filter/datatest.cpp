#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include "Butterworth.h"

using namespace std;

int main()
{
	int filterOrder = 8;
	double overallGain = 1.0;

	vector <Biquad> coeffs;
	vector <Biquad> coeffs2;
	Butterworth butterworth;

	ofstream outputFile("bandpass.txt");
	ifstream inputFile("sinsignalmulti.txt");

	float data[160] = { 0.0 };
	char x[256];
	int count = 0;
	while (inputFile)
	{
		inputFile.getline(x, 256);
		if (inputFile)
		{
			data[count] = atof(x);
			count++;
		}
	}
	
	bool designedCorrectly = butterworth.loPass(160,  // fs
		50,    // freq1
		0,      // freq2. N/A for lowpass
		filterOrder,
		coeffs,
		overallGain);
		
	overallGain = 1.0;
	bool hiPassCorrectly = butterworth.hiPass(160, 
		10, 0, filterOrder, coeffs2, overallGain);

	if (designedCorrectly = true && hiPassCorrectly == true)
	{
		BiquadChain biquadCoeffs(filterOrder/2);
		biquadCoeffs.processBiquad(data, data, 1, 160, &coeffs[0]);
		biquadCoeffs.processBiquad(data, data, 1, 160, &coeffs2[0]);
		/*for (int i = 0; i < coeffs.size(); i++)
		{
			outputFile << coeffs[i].b0 << "," << coeffs[i].b1 << "," <<
				coeffs[i].b2 << "," << coeffs[i].a1 << "," << coeffs[i].a2 << endl;
		}*/
		for (int i = 0; i < 160; i++)
		{
			outputFile << data[i] << endl;
		}
	}
	else 
	{
		cout << "Designed not correctly!" << endl;
	}

	return 0;
}