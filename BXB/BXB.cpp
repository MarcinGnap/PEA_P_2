#include "BXB.h"
#include <iostream>

BXB::BXB() {
	iCost = 0;
	iMax = INT_MAX;
	iMinCost = iMax;
}

BXB::~BXB() {

}

void BXB::calculate(int iRSize, int **iMatrix) {
	iSize = iRSize;
	bVisited = new bool[iSize];

	//	Dodanie wszystkich wierzcho³ków do kolejki.
	for (int i = 0; i < iSize; i++) {
		vQueue.push_back({ i, 1 });
	}

	//	Dodanie wierzcho³ka pocz¹tkowego do rozwarzanej trasy.
	vPath.push_back(vQueue.back().iValue);
	vQueue.pop_back();
	bVisited[vPath.back()] = true;

	do {
		//	Jeœli nie odwiedziliœmy tego wierzcho³ka.
		if (bVisited[vQueue.back().iValue] != true) {
			if (!vQueue.empty() && vQueue.back().iImp == vPath.size()) {
				//	Sprawdzenie czy jesteœmy w dobrym poddrzewie.
				vPath.push_back(vQueue.back().iValue);
				vQueue.pop_back();
				bVisited[vPath.back()] = true;

				iCost += iMatrix[vPath.at(vPath.size() - 2)][vPath.at(vPath.size() - 1)];

				if (iCost >= iMinCost) {
					//	Je¿eli koszt obliczanej trasy dorónuje obecnemu najni¿szemu kosztowi, cofamy siê do poprzedniego wierzcho³ka.
					iCost -= iMatrix[vPath.at(vPath.size() - 2)][vPath.at(vPath.size() - 1)];
					bVisited[vPath.back()] = false;
					vPath.pop_back();
				}
				else{
					for (int j = 0; j < iSize; j++) {
						if(bVisited[j] != true){
							vQueue.push_back({ j, int(vPath.size()) });
						}
					}
				}
				if (vPath.size() == iSize) {
					//	Jeœli cykl jest ca³kowity to dodajemy wagi przejœcia od ostatniego wierzcho³ka do pierwszego i sprawdzamy czy waga jest aktualnie najmniejsza.
					iCost += iMatrix[vPath.back()][vPath.at(0)];
					if (iCost < iMinCost){
						iMinCost = iCost;
						vMinPath = vPath;
					}
					iCost -= iMatrix[vPath.back()][vPath.at(0)];
				}
			}
			else if(!vQueue.empty() && vQueue.back().iImp < vPath.size() && vPath.size() > 1){
				//	Jeœli nie ma wiêcej wierzcho³ków do odwiedzenia musimy siê cofn¹æ.
				iCost -= iMatrix[vPath.at(vPath.size() - 2)][vPath.at(vPath.size() - 1)];
				bVisited[vPath.back()] = false;
				vPath.pop_back();
			}
			else if (!vQueue.empty() && vQueue.back().iImp > vPath.size()) {
				vQueue.pop_back();
			}
		}
		else if (!vPath.empty()) {
			//	Jeœli z jakiegoœ powodu wierzcho³ek jest zawarty w danym cyklu to cofamy siê.
			bVisited[vPath.back()] = false;
			iCost -= iMatrix[vPath.at(vPath.size() - 2)][vPath.back()];
			vPath.pop_back();
		}
	} while (vQueue.empty());
	//	Dzia³a.
}