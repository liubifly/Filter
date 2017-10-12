#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include "Butterworth.h"
#include "EEGFilter.h"

using namespace std;

double Gain = 0.00926729;
double Coeffs[8][5] =
{
	{ 1,-2,1,1.7452,-0.890833 },
	{ 1,-2,1,1.55266,-0.696583 },
	{ 1,-2,1,1.35827,-0.516359 },
	{ 1,-2,1,1.14706,-0.341502 },
	{ 1,2,1,-0.662803,-0.756049 },
	{ 1,2,1,-0.470264,-0.410148 },
	{ 1,2,1,-0.275881,-0.178208 },
	{ 1,2,1,-0.0646641,-0.0284055 },
};

void parameterGenerate(int sampleRate)
{
	int filterOrder = 8;
	double overallGain = 1;
	vector <Biquad> coeffs;
	Butterworth butterworth;
	ofstream paramFile("parameters.txt");

	bool designedCorrectly = butterworth.bandPass(sampleRate,  // fs
		10,    // freq1
		50,      // freq2. N/A for lowpass
		filterOrder,
		coeffs,
		overallGain);
		
	if (designedCorrectly = true)
	{
		paramFile << "double Gain = " << overallGain <<";"<< endl;
		paramFile << "double Coeffs[" << coeffs.size() << "][5] = " << endl;
		paramFile << "{" << endl;
		for (int i = 0; i < coeffs.size(); i++)
		{
			paramFile << "{" << coeffs[i].b0 << "," << coeffs[i].b1 << "," <<
				coeffs[i].b2 << "," << coeffs[i].a1 << "," << coeffs[i].a2 << "}" << "," << endl;
		}
		paramFile << "};" << endl;
	}
	else 
	{
		cout << "Designed not correctly!" << endl;
	}
}


int main()
{
	ofstream outputFile("bandpass.txt");
	ifstream inputFile("sinsignalmulti.txt");

	parameterGenerate(160);

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
	
	EEGFilter filter;
	filter.initCoeffs(8, Coeffs, Gain);
	filter.filter(data, data, 160);
	for (int i = 0; i < 160; i++)
	{
		outputFile << data[i] << endl;
	}

	return 0;
}