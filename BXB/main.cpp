#include "Reader.h"
#include "timeMeasurement.h"
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

int main() {
	Reader reader;
	timeMeasurement tM;
	std::fstream outputFile;
	int iAvgTime = 0;
	float fAvgTimefloat = 0;

	outputFile.open("results.csv", std::ios::out);

	outputFile << "Nazwa pliku" << ", ";
	outputFile << "Powtórzenia algorytmu" << ", ";
	outputFile << "Optymalny koszt" << ", ";
	outputFile << "Optymalna œcie¿ka" << ", ";
	outputFile << "Otrzymany koszt" << ", ";
	outputFile << "Œredni czas wykonania [ms]" << "\n";

	cout << "Starting...\n";

	reader.OpenIni();
	cout << "Nazwa pliku: " << reader.sFilename << endl;
	cout << "Ilosc wykonan: " << reader.iRNumber << endl;
	cout << "Optymalny koszt: " << reader.iOCost << endl;

	outputFile << reader.sFilename << ", ";
	outputFile << reader.iRNumber << ", ";
	outputFile << reader.iOCost << ", ";
	for (int i = 0; i < reader.iOptimalRouteSize; i++) {
		outputFile << reader.iOptimalRoute[i] << " ";
	}
	outputFile << ", ";
	delete[] reader.iOptimalRoute;


	reader.OpenTxt(reader.sFilename);

	cout << "\t Calculating...\n";

	for (int n = 0; n < reader.iRNumber; ++n) {
		auto o1 = chrono::high_resolution_clock::now();

		//BF.calculate(menu.iVertices, menu.iNOfVertices);

		auto o2 = chrono::high_resolution_clock::now();
		tM.tMOutcome(o1, o2);
		iAvgTime = iAvgTime + tM.tMTest(o1, o2);
	}
	fAvgTimefloat = iAvgTime / reader.iRNumber;
	//outputFile << BF.iLowestCost + 1 << ", ";
	//outputFile << fAvgTimefloat << "\n";
	cout << "Sredni czas wykonywania algorytmu: " << fAvgTimefloat << endl;
	cout << "\t Done...\n";

	getchar();
	return 0;
}