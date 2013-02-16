#include "HMMNode.h"
#include "HiddenMarkovModel.h"
#include "HMMProbabilities.h"

const char HMMNode::startNodeChar = '&';


HMMNode::HMMNode(){
	// Initialize as start node
	state = 0;
	residue = startNodeChar;
	highestWeight = 0; // set to zero only on start node
	highestWeightPreviousNode = NULL;
}

HMMNode::HMMNode(int aState, char aResidue, HiddenMarkovModel* aModel) {
	state = aState;
	residue = aResidue;
	model = aModel;
	highestWeightPreviousNode = NULL;
}

HMMNode::~HMMNode(void)
{
}

void HMMNode::addInTransition(HMMTransition* aTransition) {
	inTransitions.push_back(aTransition);
}

void HMMNode::addOutTransition(HMMTransition* aTransition) {
	outTransitions.push_back(aTransition);
}

double HMMNode::logEmissionProbability() {
	return model->probabilities->logEmissionProbability(state, residue);
}
