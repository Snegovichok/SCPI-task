// Example.cpp
//
// VISA Header: visa.h (must be included)
// VISA Library: visa32.lib (must be linked with)
// check "how to link visa library.txt" for how to link

// The VNA application must be launched.
// The server socket 5025 on the VNA software must be on(System > Misc Setup > Network Setup > Socket Server = ON).
// The library visa32.dll must be installed on the system.

// Make sure the VNA software displays "Ready" in the lower right - hand corner of the VNA application window.


#include "stdafx.h"
#include "visa.h"

// Time test
/*
#include <chrono>
*/

int main(int argc, char* argv[])
{
	ViStatus status;                        // Error checking
	ViSession defaultRM, instr;             // Communication channels
	ViUInt32 retCount;                      // Return count from string I/O
	ViByte buffer[255];                     // Buffer for string I/O
	const int NOP = 201;                    // Number of measurement points
	double Data[NOP * 2];					// Measurement data array
	double Freq[NOP];						// Frequency array

	// Time test
	/*
	auto start = std::chrono::high_resolution_clock::now();
	*/

	status = viOpenDefaultRM(&defaultRM);

	if (status < VI_SUCCESS)
	{
		printf("Can't initialize VISA\n");
		return -1;
	}

	status = viOpen(defaultRM, "TCPIP::127.0.0.1::5025::SOCKET", VI_NULL, VI_NULL, &instr);

	if (status < VI_SUCCESS)
	{
		printf("Can't open VISA address: %s\n", argv[1]);
		return -1;
	}
	//
	// Set timeout
	//
	viSetAttribute(instr, VI_ATTR_TMO_VALUE, 5000);
	//
	// Enable terminal character
	//
	viSetAttribute(instr, VI_ATTR_TERMCHAR_EN, VI_TRUE);
	viSetAttribute(instr, VI_ATTR_TERMCHAR, '\n');
	//
	// Read ID string from Analyzer
	//
	viPrintf(instr, "*IDN?\n");
	viRead(instr, buffer, sizeof(buffer), &retCount);
	printf("*IDN? Returned %d bytes: %.*s\n\n", retCount, retCount, buffer);
	//
	// Set up the Analyzer
	//
	viPrintf(instr, "SYST:PRES\n");
	viPrintf(instr, "SENS:SWE:POIN %d\n", NOP);
	viPrintf(instr, "CALC:PAR1:DEF S11\n");
	viPrintf(instr, "CALC:PAR1:SEL\n");
	viPrintf(instr, "CALC:FORM MLOG\n");
	viPrintf(instr, "SENS:BAND 100\n");
	//
	// Trigger measurement and wait for completion
	//
	viPrintf(instr, "TRIG:SOUR BUS\n");
	viPrintf(instr, "TRIG:SING\n");
	viQueryf(instr, "*OPC?\n", "%*t");
	//
	// Read out measurement data
	//
	retCount = NOP * 2;
	viQueryf(instr, "CALC:DATA:SDAT?\n", "%,#lf", &retCount, Data);
	retCount = NOP;
	viQueryf(instr, "SENS:FREQ:DATA?\n", "%,#lf", &retCount, Freq);
	//
	// Display measurement data
	//
	printf("%20s %20s %20s %20s\n", "Frequency", "Real", "Imag", "Loss");
	for (int i = 0; i < NOP; i++)
	{
		// Code modification
		double Loss = calculate_loss(Data[i * 2], Data[i * 2 + 1]);
		// ...
		printf("%20f %20f %20f %20f\n", Freq[i], Data[i * 2], Data[i * 2 + 1], Loss);
	}

	// Time test
	/*
	printf("\n");
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	printf("Time taken: %lld ms\n", duration);
	*/

	printf("Press ENTER to close...");
	getc(stdin);
	viPrintf(instr, "TRIG:SOUR INT\n"); // change trigger source back to internal
	status = viClose(instr);
	status = viClose(defaultRM);
	return 0;
}