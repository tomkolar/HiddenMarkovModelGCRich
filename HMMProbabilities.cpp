#include "HMMProbabilities.h"


HMMProbabilities::HMMProbabilities() {
}


HMMProbabilities::~HMMProbabilities() {
}

HMMProbabilities* HMMProbabilities::initialProbabilities() {

	HMMProbabilities* probs = new HMMProbabilities();

	// initiation probabilties
	probs->setInitiationProbability(0, 0.996);
	probs->setInitiationProbability(1, 0.004);

	// transition probabilities
	probs->setTransitionProbability(0, 0, 0.999);
	probs->setTransitionProbability(0, 1, 0.001);
	probs->setTransitionProbability(1, 0, 0.01);
	probs->setTransitionProbability(1, 1, 0.99);

	// emission probabilities
	probs->setEmissionProbability(0, 'A', 0.291);
	probs->setEmissionProbability(0, 'T', 0.291);
	probs->setEmissionProbability(0, 'C', 0.209);
	probs->setEmissionProbability(0, 'G', 0.209);
	probs->setEmissionProbability(1, 'A', 0.169);
	probs->setEmissionProbability(1, 'T', 0.169);
	probs->setEmissionProbability(1, 'C', 0.331);
	probs->setEmissionProbability(1, 'G', 0.331);

	return probs;

}

HMMProbabilities* HMMProbabilities::testProbabilities() {

	HMMProbabilities* probs = new HMMProbabilities();

	// initiation probabilties
	probs->setInitiationProbability(0, 0.5);
	probs->setInitiationProbability(1, 0.5);

	// transition probabilities
	probs->setTransitionProbability(0, 0, 0.5);
	probs->setTransitionProbability(0, 1, 0.5);
	probs->setTransitionProbability(1, 0, 0.4);
	probs->setTransitionProbability(1, 1, 0.6);

	// emission probabilities
	probs->setEmissionProbability(0, 'A', 0.2);
	probs->setEmissionProbability(0, 'T', 0.2);
	probs->setEmissionProbability(0, 'C', 0.3);
	probs->setEmissionProbability(0, 'G', 0.3);
	probs->setEmissionProbability(1, 'A', 0.3);
	probs->setEmissionProbability(1, 'T', 0.3);
	probs->setEmissionProbability(1, 'C', 0.2);
	probs->setEmissionProbability(1, 'G', 0.2);

	return probs;
}

double HMMProbabilities::emissionProbability(int state, char residue) {
	return emissionProbabilities.at(state).at(residue);
}

double HMMProbabilities::initiationProbability(int state) {
	return initiationProbabilities[state];
}
	
double HMMProbabilities::transitionProbability(int beginState, int endState) {
	return transitionProbabilities[beginState][endState];
}

double HMMProbabilities::logEmissionProbability(int state, char residue) {
	return logEmissionProbabilities.at(state).at(residue);
}

double HMMProbabilities::logInitiationProbability(int state) {
	return logInitiationProbabilities[state];
}
	
double HMMProbabilities::logTransitionProbability(int beginState, int endState) {
	return logTransitionProbabilities[beginState][endState];
}

void HMMProbabilities::setEmissionProbability(int state, char residue, double value) {
	emissionProbabilities[state][residue] = value;
	logEmissionProbabilities[state][residue] = log(value)/log(2);
}

void HMMProbabilities::setInitiationProbability(int state, double value) {
	initiationProbabilities[state] = value;
	logInitiationProbabilities[state] = log(value)/log(2);
}

void HMMProbabilities::setTransitionProbability(int beginState, int endState, double value) {
	transitionProbabilities[beginState][endState] = value;
	logTransitionProbabilities[beginState][endState] = log(value)/log(2);
}
