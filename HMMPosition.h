/*
 * HMMPosition.h
 *
 *	This is the header file for the WDAGraph object. WDAGraph is an implementation

 *
 *  Created on: 2-15-13
 *      Author: tomkolar
 */

#ifndef HMMPOSITION_H
#define HMMPOSITION_H
#include "HMMNode.h"
using namespace std;

class HiddenMarkovModel;

class HMMPosition
{
public:
	HMMPosition();
	HMMPosition(int anId, char residue, int numStates, HiddenMarkovModel* model);
	~HMMPosition();

	vector<HMMNode*> nodes;
	int id;
	HMMNode* highestScoringNode();
};

#endif // HMMPOSITION_H
