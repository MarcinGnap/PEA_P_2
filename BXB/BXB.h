#pragma once
#include "Graph.h"
#include <iostream>
class BXB
{
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

	int findMinimumFor(int verticle);//zawsze sprawdza od
	void startMinimus();//do tablicy wpisuje minimalne wyjscia(od) danego wierzcholka
	int sumMinimus();//sumuje wszystkie wartosci z tablicy
};