#pragma once
#include "Graph.h"
#include <iostream>
class BXB
{
	//brut force data
	int matrixSize, minCostResult, activeCostOfPermut, currentSize;
	Graph* myGraph;
	int* permuTab;
	bool* visited;

	int* minimusFrom;
	int upperBound;
	int lowerBound;

public:
	int* resultPermut;
	int startVert;

	~BXB();
	void brutForce(int v);
	void startAlgorithm(Graph* newGraphData);
	void printResult();

	int findMinimumFor(int verticle);//zawsze sprawdza OD
	void startMinimus();//do tablicy wpisuje minimalne wyjscia(OD) danego wierzcholka
	int sumMinimus();//sumuje wszystkie wartosci z tablicy
};