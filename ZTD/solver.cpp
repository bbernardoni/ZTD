#include "StdAfx.h"
#include "solver.h"

// make vaildBoard()
// simplify constraints
// throw away invalid solutions [2..4]+[2..4]=5 (3,3) is not vaild

solver::solver(unsigned char* pCellColors)
{
	cellColors = pCellColors;
}

bool solver::vaildBoard(){
	return true;
}

void solver::solve(){
	// build constraints
	badHoles = 0;
	emptyHoles = 0;
	bool trivialHoles = false;
	cons8V.clear();
	//safe.clear();
	//bomb.clear();
	for(int i=0; i<40; ++i){
		if(cellColors[i] > 5)
			badHoles++;
		else if(cellColors[i] == 0)
			emptyHoles++;
		else{
			constraint_t cons8;
			cons8.base = i;
			cons8.spacesLeft = 0;
			cons8.minesLeft = 2*(cellColors[i]-1);
			if(i%8 == 0){
				if(i>=8){
					modConstraint(&cons8, i-8);
					modConstraint(&cons8, i-7);
				}
				modConstraint(&cons8, i+1);
				if(i<32){
					modConstraint(&cons8, i+8);
					modConstraint(&cons8, i+9);
				}
			}else if(i%8 == 7){
				if(i>=8){
					modConstraint(&cons8, i-9);
					modConstraint(&cons8, i-8);
				}
				modConstraint(&cons8, i-1);
				if(i<32){
					modConstraint(&cons8, i+7);
					modConstraint(&cons8, i+8);
				}
			}else{
				if(i>=8){
					modConstraint(&cons8, i-9);
					modConstraint(&cons8, i-8);
					modConstraint(&cons8, i-7);
				}
				modConstraint(&cons8, i-1);
				modConstraint(&cons8, i+1);
				if(i<32){
					modConstraint(&cons8, i+7);
					modConstraint(&cons8, i+8);
					modConstraint(&cons8, i+9);
				}
			}
			// test for empty constraint
			if(cons8.spacesLeft != 0){
				cons8V.push_back(cons8);
				/*if(cons8.minesLeft == 0){
					trivialHoles = true;
					for(int j=0; j<cons8.spacesLeft; ++j)
						safe.push_back(cons8.spaces[j]);
				}else if(cons8.spacesLeft >= cons8.minesLeft){
					cons8V.push_back(cons8);
				}else{
					trivialHoles = true;
					for(int j=0; j<cons8.spacesLeft; ++j)
						bomb.push_back(cons8.spaces[j]);
				}*/
			}
		}
	}
	//unsigned char basePercent = (unsigned char)((100.0*(16-badHoles))/emptyHoles);
	for(int i=0; i<40; i++){
		percents[i] = -1;
	}
	//if(trivialHoles)
		//return;

	//simplify constraints
	/*for(int i=0; i<cons8V.size(); ++i){
		for(int j=0; j<cons8V.size(); ++j){
			if(i==j)
				continue;
			if(isSubset(i,j)){
				constraint_t cons8i = cons8V.at(i);
				constraint_t cons8j = cons8V.at(j);
				int l=0;
				int m=0;
				for(int k=0; k < cons8i.spacesLeft; ++k, ++l){
					while(cons8j.spaces[l] != cons8i.spaces[k]){
						cons8j.spaces[m++] = cons8j.spaces[l++];
					}
				}
				cons8j.spacesLeft -= cons8i.spacesLeft;
				if(cons8j.spacesLeft != 0){
				if(cons8.minesLeft == 0){
			}
		}
	}*/
	avgMines = 0.0;
	for(int i=0; i<40; ++i){
		cons8Done[i] = false;
		spaceBad[i] = 0;
	}
	for(int i=0; i<17; ++i)
		for(int j=0; j<46; ++j)
			solutions[i][j] = 0;
	int subsetIndex = 0;
	for(unsigned int i=0; i<cons8V.size(); ++i){
		if(cons8Done[i])
			continue;
		// build coupled subset of constraints
		cons8cupV.clear();
		cons8spacesV.clear();
		addConstraintToCup(i);
		for(unsigned int j=0; j<cons8cupV.size(); ++j){
			for(unsigned int k=0; k<cons8V.size(); ++k){
				if(cons8Done[k])
					continue;
				if(isSharing(j,k)){
					addConstraintToCup(k);
				}
			}
		}
		// find all possible solutions to subset
		coupledSubsetSolver(0, subsetIndex);
		for(unsigned char j=0; j<cons8spacesV.size(); ++j){
			spacesForSubset[subsetIndex][j] = cons8spacesV.at(j);
		}
		spacesForSubset[subsetIndex][39] = (unsigned char)cons8spacesV.size();
		subsetIndex++;
	}
	// remove invalid solution sets
	int minMines = badHoles;
	for(int i=0; i<subsetIndex; ++i){
		int lowestSolution = 0;
		for(int j=0; j<17; ++j){
			if(solutions[j][40+i] != 0){
				lowestSolution = j;
				break;
			}
		}
		minMines += lowestSolution;
	}
	for(int i=0; i<subsetIndex; ++i){
		int lowestSolution = 0;
		for(int j=0; j<17; ++j){
			if(solutions[j][40+i] != 0){
				lowestSolution = j;
				break;
			}
		}
		for(int j=16; j>0; --j){
			if(solutions[j][40+i] != 0){
				if(minMines-lowestSolution+j > 16){
					int badToRemove = minMines-lowestSolution+j-16;
					for(int k=j; k>j-badToRemove; --k){
						solutions[k][40+i] = 0;
					}
				}
				break;
			}
		}
	}
	// calculate percents
	for(int i=0; i<subsetIndex; ++i){
		int totalSln = 0;
		int weightedMines = 0;
		for(int k=0; k<17; ++k){
			if(solutions[k][40+i] == 0)
				continue;
			totalSln += solutions[k][40+i];
			weightedMines += k*solutions[k][40+i];
		}
		avgMines += ((double)weightedMines)/totalSln;
		for(unsigned char j=0; j<spacesForSubset[i][39]; ++j){
			unsigned char space = spacesForSubset[i][j];
			int spaceSln = 0;
			for(int k=0; k<17; ++k)
				if(solutions[k][40+i] != 0)
					spaceSln += solutions[k][space];
			percents[space] = (unsigned char)((100.0*spaceSln)/totalSln);
		}
	}

	emptyHoles = 0;
	for(int i=0; i<40; i++){
		if(percents[i] == -1 && cellColors[i] == 0)
			emptyHoles++;
	}
	unsigned char basePercent = (unsigned char)((100.0*(16-badHoles-avgMines))/emptyHoles);
	for(int i=0; i<40; i++){
		if(percents[i] == -1 && cellColors[i] == 0)
			percents[i] = basePercent;
	}
}

void solver::modConstraint(constraint_t *cons8, int index){
	if(cellColors[index] > 5){
		cons8->minesLeft--;
	}else if(cellColors[index] == 0){
		cons8->spaces[cons8->spacesLeft++] = index;
	}
}

bool solver::isSubset(int i, int j){
	constraint_t cons8i = cons8V.at(i);
	constraint_t cons8j = cons8V.at(j);
	int l=0;
	for(int k=0; k < cons8i.spacesLeft; ++k){
		while(cons8j.spaces[l] != cons8i.spaces[k]){
			l++;
			if(l >= cons8j.spacesLeft){
				return false;
			}
		}
	}
	return true;
}

void solver::addConstraintToCup(int i){
	constraint_t cons8i = cons8V.at(i);
	cons8cupV.push_back(cons8i);
	for(int l=0; l<cons8i.spacesLeft; ++l){
		unsigned char value = cons8i.spaces[l];
		if(std::find(cons8spacesV.begin(), cons8spacesV.end(), value) == cons8spacesV.end()){
			std::vector<unsigned char>::iterator it = std::lower_bound( cons8spacesV.begin(), cons8spacesV.end(), value);
			cons8spacesV.insert( it, value );
		}
	}
	cons8Done[i] = true;
}

bool solver::isSharing(int i, int j){
	constraint_t cons8i = cons8cupV.at(i);
	constraint_t cons8j = cons8V.at(j);
	int k=0;
	int l=0;
	while((k<cons8i.spacesLeft)&&(l<cons8j.spacesLeft)){
		if(cons8j.spaces[l] == cons8i.spaces[k])
			return true;
		else if(cons8j.spaces[l] > cons8i.spaces[k])
			k++;
		else
			l++;
	}
	return false;
}

void solver::coupledSubsetSolver(unsigned char index, int subsetIndex){
	if(index >= cons8spacesV.size()){
		//output solution
		int minesUsed = 0;
		for(int i=0; i<40; ++i){
			if(spaceBad[i]==1)
				minesUsed++;
		}
		if(minesUsed+badHoles>16){
			return;
		}
		for(int i=0; i<40; ++i){
			if(spaceBad[i]==1)
				solutions[minesUsed][i]++;
		}
		solutions[minesUsed][40+subsetIndex]++;
		return;
	}
	unsigned char space = cons8spacesV.at(index);
	spaceBad[space] = 1;
	if(vaildCoupledSubset())
		coupledSubsetSolver(index+1, subsetIndex);
	spaceBad[space] = -1;
	if(vaildCoupledSubset())
		coupledSubsetSolver(index+1, subsetIndex);
	spaceBad[space] = 0;
}

bool solver::vaildCoupledSubset(){
	constraint_t cons8;
	unsigned char mines;
	unsigned char emptySpaces;
	unsigned char state;
	for(unsigned char i=0; i<cons8cupV.size(); ++i){
		cons8 = cons8cupV.at(i);
		mines = 0;
		emptySpaces = 0;
		for(int j=0; j<cons8.spacesLeft; ++j){
			state = spaceBad[cons8.spaces[j]];
			if(state == 1)
				mines++;
			else if(state == 0)
				emptySpaces++;
		}
		if(mines>cons8.minesLeft)
			return false;
		if(mines+emptySpaces+1<cons8.minesLeft)
			return false;
	}
	return true;
}