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

	//	Dodanie wszystkich wierzcho�k�w do kolejki.
	for (int i = 0; i < iSize; i++) {
		vQueue.push_back({ i, 1 });
	}

	//	Dodanie wierzcho�ka pocz�tkowego do rozwarzanej trasy.
	vPath.push_back(vQueue.back().iValue);
	vQueue.pop_back();
	bVisited[vPath.back()] = true;

	do {
		//	Je�li nie odwiedzili�my tego wierzcho�ka.
		if (bVisited[vQueue.back().iValue] != true) {
			if (!vQueue.empty() && vQueue.back().iImp == vPath.size()) {
				//	Sprawdzenie czy jeste�my w dobrym poddrzewie.
				vPath.push_back(vQueue.back().iValue);
				vQueue.pop_back();
				bVisited[vPath.back()] = true;

				iCost += iMatrix[vPath.at(vPath.size() - 2)][vPath.at(vPath.size() - 1)];

				if (iCost >= iMinCost) {
					//	Je�eli koszt obliczanej trasy dor�nuje obecnemu najni�szemu kosztowi, cofamy si� do poprzedniego wierzcho�ka.
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
					//	Je�li cykl jest ca�kowity to dodajemy wagi przej�cia od ostatniego wierzcho�ka do pierwszego i sprawdzamy czy waga jest aktualnie najmniejsza.
					iCost += iMatrix[vPath.back()][vPath.at(0)];
					if (iCost < iMinCost){
						iMinCost = iCost;
						vMinPath = vPath;
					}
					iCost -= iMatrix[vPath.back()][vPath.at(0)];
				}
			}
			else if(!vQueue.empty() && vQueue.back().iImp < vPath.size() && vPath.size() > 1){
				//	Je�li nie ma wi�cej wierzcho�k�w do odwiedzenia musimy si� cofn��.
				iCost -= iMatrix[vPath.at(vPath.size() - 2)][vPath.at(vPath.size() - 1)];
				bVisited[vPath.back()] = false;
				vPath.pop_back();
			}
			else if (!vQueue.empty() && vQueue.back().iImp > vPath.size()) {
				vQueue.pop_back();
			}
		}
		else if (!vPath.empty()) {
			//	Je�li z jakiego� powodu wierzcho�ek jest zawarty w danym cyklu to cofamy si�.
			bVisited[vPath.back()] = false;
			iCost -= iMatrix[vPath.at(vPath.size() - 2)][vPath.back()];
			vPath.pop_back();
		}
	} while (vQueue.empty());
	//	Dzia�a.
}