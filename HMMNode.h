/*
 * HMMNode.h
 *
 *	This is the header file for the WDAGraph object. WDAGraph is an implementation

 *
 *  Created on: 2-15-13
 *      Author: tomkolar
 */

#ifndef HMMNODE_H
#define HMMNODE_H
#include <vector>
#include <map>
using namespace std;

class HMMTransition;
class HiddenMarkovModel;

class HMMNode
{
public:
	HMMNode();
	HMMNode(int anId, int aState, char aResidue, HiddenMarkovModel* aModel);
	~HMMNode();

	void addInTransition(HMMTransition* aTranstion);
	void addOutTransition(HMMTransition* aTranstion);
	double logEmissionProbability();

	int id;
	int state;
	char residue;
	vector<HMMTransition*> inTransitions;
	vector<HMMTransition*> outTransitions;
	double highestWeight;
	HMMNode* highestWeightPreviousNode;
	HiddenMarkovModel* model;

	static const char startNodeChar;

private:

};

#endif // HMMNODE_H