#pragma once
#include <vector>

class BXB
{
public:
	BXB();
	~BXB();
	void calculate(int iRSize, int ** iMatrix);

private:
	struct Node{
		int iValue, iImp;
	};
	int iCost, iMinCost, iMax, iSize;
	bool * bVisited;
	std::vector<int> vPath;
	std::vector<int> vMinPath;
	std::vector<Node> vQueue;

};