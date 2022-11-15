#include "BXB.h"

BXB::~BXB()
{
	delete[] resultPermut;
	delete[] permuTab;
	delete[] visited;
	delete[] minimusFrom;
}

void BXB::brutForce(int v)
{
	int u;
	permuTab[currentSize++] = v;//permuTab jest zawsze tej samej wielkosci, current size to poprwane zapelnienie
	if (currentSize < matrixSize)
	{
		visited[v] = true;
		for (u = 0; u < matrixSize; u++)
			if (!visited[u])
			{
				lowerBound = (lowerBound - minimusFrom[v]) + myGraph->getValueOfEdge(v, u);//aktualizacja lowerBound
				activeCostOfPermut += myGraph->getValueOfEdge(v, u);
				if (lowerBound > upperBound) {
					//pomin bo nic tu nie znajdziesz
					//std::cout << "odcinam\n";
				}
				else {
					if (true) { //activeCostOfPermut <= upperBound
						//jesli znajdujemy sie w przedziale miedzy boundami to szukamy dalej
						//std::cout << "rekurencja" << std::endl;
						brutForce(u);	//rekurencja
					}
				}
				activeCostOfPermut -= myGraph->getValueOfEdge(v, u);
				lowerBound = (lowerBound + minimusFrom[v]) - myGraph->getValueOfEdge(v, u);//aktualizacja lowerBound- przywroc poprzednie
			}
		visited[v] = false;
	}
	else
	{
		//mamy juz wszystkie wierzcholki
		activeCostOfPermut += myGraph->getValueOfEdge(v, startVert);//laczymy kolo
		if (activeCostOfPermut < minCostResult)
		{
			upperBound = activeCostOfPermut;//aktualizacja upperBounda
			minCostResult = activeCostOfPermut;
			for (u = 0; u < currentSize; u++)
				resultPermut[u] = permuTab[u];
		}
		activeCostOfPermut -= myGraph->getValueOfEdge(v, startVert);
	}
	currentSize--;//!!!!!!!!!cofamy siê w tablicy- wracamy poprawiac te ktore do tej pory byly ustalone
}

void BXB::startAlgorithm(Graph* newGraphData)
{
	matrixSize = newGraphData->getNumbOfVerts();
	resultPermut = new int[matrixSize];
	permuTab = new int[matrixSize];
	visited = new bool[matrixSize];
	//W = new int* [n];
	myGraph = newGraphData;
	/*std::cout << "Drukuje dane wczytanego grafu:" << std::endl;
	myGraph->printGraph();*/
	for (int i = 0; i < matrixSize; i++)
	{
		visited[i] = false;
	}
	currentSize = 0;
	minCostResult = 99999;
	activeCostOfPermut = startVert = 0;

	startMinimus();
	upperBound = (1 << 28);//zaczyna zainicjowane jako bardzo duza liczba --nieskonczonosc
	lowerBound = sumMinimus();//zaczyna jako suma najmniejszych wyjsc z kazdego jednego wierzcholka

	brutForce(startVert);

	//here printin
}

void BXB::printResult()
{//sekcja wyswietlania
	for (int i = 0; i < matrixSize; i++) std::cout << resultPermut[i] << "-->";
	std::cout << startVert << std::endl;
	std::cout << " Koszt = " << minCostResult << std::endl;
}

int BXB::findMinimumFor(int verticle)
{
	int tempMin = 99999;
	//dla podanej wartosci wierzcholka wyznacz minimalnš wartosc wychodzšca OD niego
	for (int i = 0; i < matrixSize; i++) {//proste wyznaczanie minimum
		int tempX = myGraph->getValueOfEdge(verticle, i);
		if (tempX < tempMin && i != verticle) {
			tempMin = tempX;
		}
	}
	return tempMin;
}

void BXB::startMinimus()
{
	minimusFrom = new int[matrixSize];
	for (int j = 0; j < matrixSize; j++) {
		minimusFrom[j] = findMinimumFor(j);
	}
}

int BXB::sumMinimus()
{
	int tempSum = 0;
	for (int i = 0; i < matrixSize; i++) {
		tempSum += minimusFrom[i];
	}
	return tempSum;
}