#include "Reader.h"
#include <fstream>
#include <iostream>

Reader::Reader() {
	iRNumber = 0;
	iOCost = 0;
	sFilename = " ";
}

Reader::~Reader() {
	if (iNOfVertices != 0) {
		for (int i = 0; i < iNOfVertices; i++)
			delete iVertices[i];
		delete[] iVertices;
		iVertices = NULL;
		iNOfVertices = 0;
	}
}

bool Reader::OpenIni() {
	std::ifstream ifFileini("config.ini", std::ios::in);
	if (ifFileini.good())
	{
		ifFileini >> sFilename;
		ifFileini >> iRNumber;
		ifFileini >> iOCost;
		ifFileini >> iOptimalRouteSize;

		iOptimalRoute = new int[iOptimalRouteSize];
		for (int i = 0; i < iOptimalRouteSize; i++)
		{
			ifFileini >> iOptimalRoute[i];
		}
		/*
		std::string sTemp;
		std::getline(ifFileini, sFilename);
		std::getline(ifFileini, sTemp);
		iRNumber = std::stoi(sTemp);
		sTemp = " ";
		std::getline(ifFileini, sTemp);
		iOCost = std::stoi(sTemp);
		*/
		ifFileini.close();

		return true;
	}
	return false;
}

int Reader::OpenTxt(std::string & sFilename) {
	std::cout << "\t Loading...\n";

	std::fstream fFiletxt;
	fFiletxt.open(sFilename, std::ios::in);
	if (!fFiletxt.good())
	{
		this->sFilename = "Brak pliku";
		std::cout << "\n Nie mozna wczytac pliku...";
		return 0;
	}

	if (iNOfVertices != 0)
	{
		for (int i = 0; i < iNOfVertices; ++i) {
			delete iVertices[i];
		}
		delete[] iVertices;
		iVertices = NULL;
		iNOfVertices = 0;
	}
	std::cout << "\t TSP file opened...\n";

	this->sFilename = sFilename;
	fFiletxt >> iNOfVertices;
	iVertices = new int *[iNOfVertices];
	int iLine = 0;

	std::cout << "Number of Vertices: " << iNOfVertices << std::endl;

	for (int i = 0; i < iNOfVertices; ++i) {
		iVertices[i] = new int[iNOfVertices];
	}

	while (!fFiletxt.eof()) {
		for (int x = 0; x < iNOfVertices; ++x) {
			for (int j = 0; j < iNOfVertices; ++j) {
				fFiletxt >> iVertices[x][j];
			}
			iLine++;
		}
	}

	std::cout << "\t Instance copied...\n";

	fFiletxt.close();

	if (iLine != iNOfVertices && iLine != iNOfVertices * 2) {
		std::cout << "\nNiepoprawna ilosc danych...";
		this->sFilename = "Brak pliku";
		for (int i = 0; i < iNOfVertices; ++i) {
			delete iVertices[i];
		}
		delete[] iVertices;
		iVertices = NULL;
		iNOfVertices = 0;
		return 1;
	}

	std::cout << "\n Wczytanie pliku przebieglo poprawnie\n";
	return 0;
}