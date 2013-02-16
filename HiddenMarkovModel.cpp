#include "HiddenMarkovModel.h"
#include "HMMTransition.h"
#include "HMMProbabilities.h"
#include <sstream>

const int HiddenMarkovModel::numStates = 2;

HiddenMarkovModel::HiddenMarkovModel() {
}

HiddenMarkovModel::HiddenMarkovModel(FastaFile* aFastaFile) {
	fastaFile = aFastaFile;
	modelBuilt = false;
	probabilities = HMMProbabilities::testProbabilities();
}

HiddenMarkovModel::~HiddenMarkovModel(void)
{
}

void HiddenMarkovModel::viterbiTraining(int numIterations) {

	for (int iteration = 1; iteration <= numIterations; iteration++) {
		// Build the model and calculate the weights
		buildAndCalculateModel();

		// Gather the viterbi reuslts
		HMMViterbiResults* aViterbiResults = gatherViterbiResults();
		viterbiResults.push_back(aViterbiResults);

		// Reset the probabilities to the viterbi calculated ones for the next
		// iteration
		probabilities = aViterbiResults->probabilities;
	}
}

void HiddenMarkovModel::buildAndCalculateModel() {

	if (modelBuilt) {
		// Model already built so just recalculate the weights using
		// the newly set probabilities
		for (HMMPosition* aPosition : model) {
			calculateHighestWeightPath(aPosition);
		}
	}
	else {
		string& sequence = fastaFile->getSequence();

		// Create Start Position
		HMMPosition* startPosition = new HMMPosition();
		model.push_back(startPosition);

		// Iterate through the sequence and create model on the fly
		HMMPosition* previousPosition = startPosition;
		int seqLength = sequence.length();
		for (int seqPos = 0; seqPos < seqLength; seqPos++) {
			// Create a Position object with one node for each state
			HMMPosition* aPosition = new HMMPosition(seqPos + 1, sequence.at(seqPos), numStates, this);

			// Create the incoming transitions for the curent position
			createTransitionsFor(aPosition, previousPosition);

			// Calculate highest weight path for current position
			calculateHighestWeightPath(aPosition);

			// Add position to the model
			model.push_back(aPosition);

			// Set previous positon to current position so that next iteration cancreate
			// transitions correctly.
			previousPosition = aPosition;
		}

		modelBuilt = true;
	}
}

void HiddenMarkovModel::createTransitionsFor(HMMPosition* currentPosition, HMMPosition* previousPosition) {
	// Create inTransitions for the  current position nodes
	for (HMMNode* currentPositionNode : currentPosition->nodes) {
		// Create one transition for each node from the previous position
		// to this node in the current position
		for (HMMNode* previousPositionNode : previousPosition->nodes) {
			// Create the transition
			HMMTransition* aTransition = new HMMTransition(previousPositionNode, currentPositionNode, this);

			// Add to the transitions collections on nodes
			currentPositionNode->addInTransition(aTransition);
			previousPositionNode->addOutTransition(aTransition);
		}
	}
}

void HiddenMarkovModel::calculateHighestWeightPath(HMMPosition* aPosition) {
	// Calculate hwp for each node
	for (HMMNode* positionNode : aPosition->nodes) {
		// initialize highest weight to negative infinity
		positionNode->highestWeight = -DBL_MAX;

		// Iterater through each of the incoming transitions to find
		// the highest score
		for (HMMTransition* transition : positionNode->inTransitions) {
			// calculate the score
			double score = 
				 transition->startNode->highestWeight  // previous nodes weight
			   + transition->logProbability()          // transition probability 
			   + positionNode->logEmissionProbability(); // emission probablity

			// Replace the highest weight info if this path has the highest score
			if (score > positionNode->highestWeight) {
				positionNode->highestWeight = score;
				positionNode->highestWeightPreviousNode = transition->startNode;
			}
		}
	}
}

string HiddenMarkovModel::allScoresResultsString() {
	stringstream ss;

	for (HMMPosition* aPosition : model) {
		ss << "Position: " << aPosition->id << "\n";
		for (HMMNode* node : aPosition->nodes) {
			ss << "  Node: ("
			   <<  node->state
			   << ", "
			   << node->highestWeight
			   << ")\n";
		}
	}

	return ss.str();
}

string HiddenMarkovModel::pathStatesResultsString() {
	stringstream ss;

	HMMPosition* lastPosition = model.back();
	HMMNode* aNode = lastPosition->highestScoringNode();
	while (aNode->residue != HMMNode::startNodeChar) {
		ss << aNode->state;
		aNode = aNode->highestWeightPreviousNode;
	}

	string reversePath = ss.str();
	return string(reversePath.rbegin(), reversePath.rend());
}

string HiddenMarkovModel::viterbiResultsString() {
	stringstream ss;

	int numResults = viterbiResults.size();
	for (int i = 0; i < numResults; i++) {
		if (i < numResults -1)
			ss << viterbiResults[i]->resultsWithoutSegments();
		else
			ss << viterbiResults[i]->allResults();
	}
	
	return ss.str();
}
