/*
 * HMMTransition.h
 *
 *	This is the header file for the WDAGraph object. WDAGraph is an implementation

 *
 *  Created on: 2-15-13
 *      Author: tomkolar
 */

#ifndef HMMTRANSITION_H
#define HMMTRANSITION_H
#include "HMMNode.h"
using namespace std;

class HMMTransition
{
public:
	HMMTransition();
	HMMTransition(HMMNode* aStartNode, HMMNode* anEndNode, HiddenMarkovModel* aModel);
	~HMMTransition();

	double logProbability();

	HMMNode* startNode;
	HMMNode* endNode;
	HiddenMarkovModel* model;
};

#endif // HMMTRANSITION_H
