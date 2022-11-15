#include "Reader.h"
#include "timeMeasurement.h"
#include "Graph.h"
#include "BXB.h"
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
	outputFile << "Otrzymany koszt: " << endl;


	cout << "\n \nChecking input file...\n";
	cout << reader.iNOfVertices << endl << endl;
	for (size_t n = 0; n < reader.iNOfVertices; n++){
		for (size_t m = 0; m < reader.iNOfVertices; m++) {
			cout << reader.iVertices[n][m] << " ";
		}
		cout << endl;
	}

	cout << "Calculating...\n";
	long long llMinTime = INT_MAX;
	long long llMaxTime = 0;
	for (int n = 0; n < reader.iRNumber; ++n) {
		long long llTempTime = 0;
		cout << "\nLoading Graph...\n";
		Graph* myGraph = new Graph(reader.iNOfVertices);
		myGraph->loadGraphFromFile(reader.iNOfVertices, reader.iVertices);
		BXB* test = new BXB();

		auto o1 = chrono::high_resolution_clock::now();

		test->startAlgorithm(myGraph);

		auto o2 = chrono::high_resolution_clock::now();
		test->printResult();

		tM.tMOutcome(o1, o2);
		llTempTime = tM.tMTest(o1, o2);
		if (llTempTime < llMinTime) {
			llMinTime = llTempTime;
		}
		else if(llTempTime > llMaxTime){
			llMaxTime = llTempTime;
		}
		outputFile << llTempTime << endl;
		llAvgTime = llAvgTime + llTempTime;

		cout << endl;
		cout << endl;

	}
	llAvgTimefloat = llAvgTime / reader.iRNumber;
	outputFile << "Œredni czas wykonywania algorytmu [ns]: " << llAvgTimefloat << endl;
	outputFile << "Optymalna œcie¿ka: ";
	Graph* myGraph = new Graph(reader.iNOfVertices);
	myGraph->loadGraphFromFile(reader.iNOfVertices, reader.iVertices);
	BXB* test = new BXB();
	test->startAlgorithm(myGraph);
	for (int i = 0; i < reader.iNOfVertices+1; i++) {
		outputFile << test->resultPermut[i] << "-->";
	}
	outputFile << test->startVert << std::endl;
	cout << "Maksymalny czas wykonywania algorytmu: " << llMaxTime << endl;
	cout << "Minimalny czas wykonywania algorytmu: " << llMinTime << endl;
	cout << "Sredni czas wykonywania algorytmu: " << llAvgTimefloat << endl;
	cout << "Done...\n";

	getchar();
	return 0;
}