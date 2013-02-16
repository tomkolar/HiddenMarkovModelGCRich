#include "HMMTransition.h"
#include "HiddenMarkovModel.h"

HMMTransition::HMMTransition() {
}

HMMTransition::HMMTransition(HMMNode* aStartNode, HMMNode* anEndNode, HiddenMarkovModel* aModel) {
	startNode = aStartNode;
	endNode = anEndNode;
	model = aModel;
}

HMMTransition::~HMMTransition() {
}

double HMMTransition::logProbability() {
	if (startNode->residue == HMMNode::startNodeChar)
		return model->probabilities->logInitiationProbability(endNode->state);
	else
		return model->probabilities->logTransitionProbability(startNode->state, endNode->state);
}
