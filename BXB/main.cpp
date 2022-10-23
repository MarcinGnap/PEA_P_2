#include "Reader.h"
#include "timeMeasurement.h"
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

int main() {
	Reader reader;
	timeMeasurement tM;
	fstream outputFile;
	long long llAvgTime = 0;
	long long llAvgTimefloat = 0;

	outputFile.open("results.csv", ios::out);

	cout << "Starting...\n";

	reader.OpenIni();
	cout << "\nNazwa pliku: " << reader.sFilename << endl;
	cout << "Ilosc wykonan: " << reader.iRNumber << endl;
	cout << "Optymalny koszt: " << reader.iOCost << endl << endl;

	/*for (int i = 0; i < reader.iOptimalRouteSize; i++) {
		outputFile << reader.iOptimalRoute[i] << " ";
	}
	outputFile << ", ";
	delete[] reader.iOptimalRoute;*/


	reader.OpenTxt(reader.sFilename);

	outputFile << "Nazwa pliku: " << reader.sFilename << endl;
	outputFile << "Powtórzenia algorytmu: " << reader.iRNumber << endl;
	outputFile << "Optymalny koszt: " << reader.iOCost << endl;
	outputFile << "Optymalna œcie¿ka: " << endl;
	outputFile << "Otrzymany koszt: " << endl;

	cout << "Calculating...\n";

	for (int n = 0; n < reader.iRNumber; ++n) {
		long long llTempTime = 0;
		auto o1 = chrono::high_resolution_clock::now();

		//BF.calculate(menu.iVertices, menu.iNOfVertices);

		auto o2 = chrono::high_resolution_clock::now();
		tM.tMOutcome(o1, o2);
		llTempTime = tM.tMTest(o1, o2);
		outputFile << llTempTime << endl;
		llAvgTime = llAvgTime + llTempTime;
	}
	llAvgTimefloat = llAvgTime / reader.iRNumber;
	//outputFile << BF.iLowestCost + 1 << ", ";
	outputFile << "Œredni czas wykonywania algorytmu [ms]: " << llAvgTimefloat;
	outputFile << "\nKoniec";
	cout << "Sredni czas wykonywania algorytmu: " << llAvgTimefloat << endl;
	cout << "Done...\n";

	getchar();
	return 0;
}