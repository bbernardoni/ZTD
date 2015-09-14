#pragma once

#include <vector>
#include <algorithm>

struct constraint_t {
	unsigned char base;
	unsigned char spacesLeft;
	unsigned char minesLeft; // maximum can be minesLeft - 1 as well
	unsigned char spaces[8];
};

public class solver
{
public:
	solver(unsigned char* pCellColors);
	bool vaildBoard();
	void solve();
	char getPecent(int i) { return percents[i]; }

private:
	void modConstraint(constraint_t *cons8, int index);
	bool isSubset(int i, int j);
	void addConstraintToCup(int i);
	bool isSharing(int i, int j);
	void coupledSubsetSolver(unsigned char index, int subsetIndex);
	bool vaildCoupledSubset();

	unsigned char* cellColors;
	bool cons8Done[40];
	unsigned char spaceBad[40];
	unsigned int solutions[17][46];
	unsigned char spacesForSubset[6][40];
	char percents[40];
	int badHoles;
	int emptyHoles;
	double avgMines;
	std::vector<constraint_t> cons8V;
	std::vector<constraint_t> cons8cupV;
	std::vector<unsigned char> cons8spacesV;
	//std::vector<unsigned char> safe;
	//std::vector<unsigned char> bomb;
};