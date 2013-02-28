/*
 * HMMProbablities.cpp
 *
 *	This is the cpp file for the HMMProbabilties object. HMMProbabilities
 *  is a collection of all probabilties needed for a hidden markov model. This
 *  includes initiation, emission and transition probabilties.  There are 
 *	convenience methods for setting and retriving probabilties as well as
 *  the log value of each probabilty.
 *
 *  Created on: 2-15-13
 *      Author: tomkolar
 */
#include "HMMProbabilities.h"
#include <cmath>
#include <sstream>
#include <string>

// Constuctors
// ==============================================
HMMProbabilities::HMMProbabilities() {
}

// Destructor
// =============================================
HMMProbabilities::~HMMProbabilities() {
}

// Public Class Methods
// =============================================

// HMMProbabilities* initialProbabilities()
//  Purpose: 
//		Returns a probabilites object initialzed to the initial
//		probabilites required by genome540 homework #5	
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

// HMMProbabilities* testProbabilities()
//  Purpose: 
//		Returns a probabilites object initialzed to the probabilites
//		required by the viterbi toy example
//			homepages.ulb.ac.be/~dgonze/TEACHING/viterbi.pdf
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

// Public Methods
// =============================================

// double emissionProbability(int state, char residue)
//  Purpose: 
//		Returns the emission probability for the state and residue
long double HMMProbabilities::emissionProbability(int state, char residue) {
	return emissionProbabilities.at(state).at(residue);
}

// double initiationProbability(int state)
//  Purpose: 
//		Returns the initiation probability for the state
long double HMMProbabilities::initiationProbability(int state) {
	return initiationProbabilities[state];
}
	
// double transitionProbability(int beginState, int endState)
//  Purpose: 
//		Returns the transition probability for transition from beginState
//		to endState
long double HMMProbabilities::transitionProbability(int beginState, int endState) {
	return transitionProbabilities[beginState][endState];
}

// double logEmissionProbability(int state, char residue)
//  Purpose: 
//		Returns the log of the emission probability for the state and residue
long double HMMProbabilities::logEmissionProbability(int state, char residue) {
	return logEmissionProbabilities.at(state).at(residue);
}

// double logInitiationProbability(int state)
//  Purpose: 
//		Returns the log of the initiation probability for the state
long double HMMProbabilities::logInitiationProbability(int state) {
	return logInitiationProbabilities[state];
}
	
// double logTransitionProbability(int beginState, int endState)
//  Purpose: 
//		Returns the log of the transition probability for transition from
//		beginState to endState
long double HMMProbabilities::logTransitionProbability(int beginState, int endState) {
	return logTransitionProbabilities[beginState][endState];
}

// setEmissionProbability(int state, char residue, double value)
//  Purpose: 
//		Sets the emission probability for the state and residue to value
//	Postconditions:
//		emissionProbabilites - value set for state/residue
//		logEmissionProbabilites - value set for state/residue
void HMMProbabilities::setEmissionProbability(int state, char residue, long double value) {
	emissionProbabilities[state][residue] = value;
	logEmissionProbabilities[state][residue] = log(value);
}

// setInitiationProbability(int state, double value)
//  Purpose: 
//		Sets the initiation probability for the state to value
//	Postconditions:
//		initiationProbabilites - value set for state
//		logInitiationProbabilites - value set for state
void HMMProbabilities::setInitiationProbability(int state, long double value) {
	initiationProbabilities[state] = value;
	logInitiationProbabilities[state] = log(value);
}

// setTransitionProbability(int beginState, int endState, double value)
//  Purpose: 
//		Sets the transition probability from the beginState to the endState
//		to value
//	Postconditions:
//		transitionProbabilites - value set for beginState to endState
//		logTransitionProbabilites - value set for beginState to endState
void HMMProbabilities::setTransitionProbability(int beginState, int endState, long double value) {
	transitionProbabilities[beginState][endState] = value;
	logTransitionProbabilities[beginState][endState] = log(value);
}

// string probabilitiesResultsString()
//  Purpose:
//		Returns a string representing the probabilites
//
//		format:
//			<<statesResultsString>>
//			<<initiationProbabilitesResultsString>>
//			<<transmissionProbabilitesResultsString>>
//			...
//			<<emissionProbabilitesResultsString>>
//			...
string HMMProbabilities::probabilitiesResultsString() {
	stringstream ss;

	// Begin Model
	ss << "      <model type=\"hmm\">\n";

	// States
	ss << statesResultsString();

	// Probabiltiies
	ss << intitiationProbabiltiesResultsString();
	for (int i = 0; i < 2; i++)
		ss << transitionProbablitiesResultsString(i);
	for (int i = 0; i < 2; i++)
		ss << emissionProbablitiesResultsString(i);
	
	// End Model
	ss << "      </model>\n";

	return ss.str();
}

// string statesResultsString()
//  Purpose:
//		Returns a string representing the states
//
//		format:
//			<result type="states">
//				<<state1>>,<<state2>>,...
//			</result>
string HMMProbabilities::statesResultsString() {
	stringstream ss;

	// Header 
	ss << "        <states>";

	// States
	for (int i = 0; i < 2; i++) {
		ss << i + 1;

		if ( i < 2 -1)
		   ss << ",";
	}

	// Footer
	ss << "</states>\n";

	return ss.str();
}

// string intitiationProbabiltiesResultsString()
//  Purpose:
//		Returns a string representing the initiation probablities
//
//		format:
//			<result type="initiation_probabilites">
//				<<state>>=<<initiation probability>>,
//			</result>
string HMMProbabilities::intitiationProbabiltiesResultsString() {
	stringstream ss;
	ss.precision(4);
	ss << scientific;

	// Header 
	ss << "        <initial_state_probabilities>";

	// States
	for (int i = 0; i < 2; i++) {
		ss
			<< i + 1
			<< "="
			<< initiationProbability(i);

		if ( i < 1)
		   ss << ",";
	}

	// Footer
	ss << "</initial_state_probabilities>\n";

	return ss.str();
}

// transitionProbablitiesResultsString(int state)
//  Purpose:
//		Returns a string representing the transition probablities for a state
//
//		format:
//			<result type="transition_probabilites" state="<<state>>">
//				<<to state>>=<<transition probability>>,
//			</result>
string HMMProbabilities::transitionProbablitiesResultsString(int state) {
	stringstream ss;
	ss.precision(4);
	ss << scientific;

	// Header 
	ss << "        <transition_probabilities state=\"" << state + 1 << "\">";

	// States
	for (int i = 0; i < 2; i++) {
		ss
			<< i + 1
			<< "="
			<< transitionProbability(state, i);

		if ( i < 1)
		   ss << ",";
	}

	// Footer
	ss << "</transition_probabilities>\n";

	return ss.str();
}

// emissionProbablitiesResultsString(int state)
//  Purpose:
//		Returns a string representing the emission probablities for a state
//
//		format:
//			<result type="emission_probabilites" state="<<state>>">
//				<<residue>>=<<emission probability>>,
//			</result>
string HMMProbabilities::emissionProbablitiesResultsString(int state) {
	stringstream ss;
	ss.precision(4);
	ss << scientific;

	// Header 
	ss << "        <emission_probabilities state=\"" << state + 1 << "\">";

	// Residues
	ss 
		<< "A=" << emissionProbability(state, 'A') << ","
		<< "C=" << emissionProbability(state, 'C') << ","
		<< "G=" << emissionProbability(state, 'G') << ","
		<< "T=" << emissionProbability(state, 'T');

	// Footer
	ss << "</emission_probabilities>\n";

	return ss.str();
}
