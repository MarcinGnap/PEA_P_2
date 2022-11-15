#pragma once
#include "Graph.h"
#include <iostream>
class BXB
{
	//brut force data
	int matrixSize, startVert, minCostResult, activeCostOfPermut, currentSize;
	Graph* myGraph;
	int* resultPermut, *permuTab;
	bool* visited;

	int* minimusFrom;
	int upperBound;
	int lowerBound;

public:
	~BXB();
	void brutForce(int v);
	void startAlgorithm(Graph* newGraphData);
	void printResult();

	int findMinimumFor(int verticle);//zawsze sprawdza OD
	void startMinimus();//do tablicy wpisuje minimalne wyjscia(OD) danego wierzcholka
	int sumMinimus();//sumuje wszystkie wartosci z tablicy
};