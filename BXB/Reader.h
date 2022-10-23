#pragma once

#include <string>

class Reader
{
public:
	int iRNumber;
	int iOCost;
	std::string sFilename;

	int iNOfVertices;
	int **iVertices;
	int *bestPath;

	Reader();
	~Reader();
	bool OpenIni();
	int OpenTxt(std::string & sFilename);
};

