#include "HMMPosition.h"


HMMPosition::HMMPosition() {
	// 
	id = 0;
	HMMNode* startNode = new HMMNode();
	nodes.push_back(startNode);
}

HMMPosition::HMMPosition(int anId, char residue, int numStates, HiddenMarkovModel* model) {
	id = anId;
	for (int state = 0; state < numStates; state++) {
		HMMNode* node = new HMMNode(state, residue, model);
		nodes.push_back(node);
	}
}

HMMPosition::~HMMPosition(void)
{
}

HMMNode* HMMPosition::highestScoringNode() {
	HMMNode* highestScorer = NULL;
	for (HMMNode* node : nodes) {
		if (highestScorer == NULL)
			highestScorer = node;
		else {
			if (node->highestWeight > highestScorer->highestWeight) 
				highestScorer = node;
		}
	}

	return highestScorer;
}
