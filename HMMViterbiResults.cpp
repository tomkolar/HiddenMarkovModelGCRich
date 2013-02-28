/*
 * HMMViterbiResults.cpp
 *
 *	This is the cpp file for the HMMViterbiResults object. 
 *  HMMViterbiResults contains the rsults for one iteration of viterbi
 *  training for a hidden markov model.
 *
 *  Important Attributes
 *
 *		stateCounts - how many times a state occurs in the viterbi path
 *		segmentCounts - how many segments (i.e., continuos occurencee of
 *						one state) of each state occurs
 *		segments - collection of start and stop values for each segment
 *		transitionCounts - counts for how many time states transition (both
 *						   from one state to another and from one state to 
 *						   the stame state)
 *		probabilities - the probabilites that are calculated from the above 
 *						results
 *
 *	resultsWithoutSegments() - returns a string of all results except segments
 *	allResults() - returns a string of all results (including segements)
 *
 *  Created on: 2-15-13
 *      Author: tomkolar
 */
#include "HMMViterbiResults.h"
#include "StringUtilities.h"
#include <sstream>

// Constuctors
// ==============================================
HMMViterbiResults::HMMViterbiResults() {
}

HMMViterbiResults::HMMViterbiResults(int anIteration, int numberOfStates) {

	iteration = anIteration;
	numStates = numberOfStates;

	// initialize counts vectors
	for (int i = 0; i < numStates; i++) {
		stateCounts.push_back(0);
		segmentCounts.push_back(0);
		transitionCounts.push_back(vector<int>());
		for (int j = 0; j < numStates; j++) {
			transitionCounts[i].push_back(0);
		}
		segments[i] = vector<pair<int,int>>();
	}
}

// Destructor
// =============================================
HMMViterbiResults::~HMMViterbiResults(){
}

// Public Methods
// =============================================

// string resultsWithoutSegments()
//  Purpose:
//		Returns a string representing the viterbi results for 
//		a particular iteration
//
//		format:
//			<result type="viterbi_iteration" iteration="<< iteration >>">
//				<<stateHistogramResultsString>>
//				<<segmentHistogramResultsString>>
//				<<probabiltiesResultsString>>
//			</result>
string HMMViterbiResults::resultsWithoutSegments() {
	stringstream ss;

	// Header
	ss << "    <result type=\"viterbi_iteration\" iteration=\"" << iteration << "\">\n";

	// Results
	ss 
		<< stateHistogramResultsString()
		<< segmentHistogramResultsString()
		<< probabilitiesResultsString();

//	ss 	<< transitionCountsResultsString();

	// Footer
	ss << "    </result>\n";

	return ss.str();
}

// string allResults()
//  Purpose:
//		Returns a string representing the viterbi results for 
//		a particular iteration
//
//		format:
//			<result type="viterbi_iteration" iteration="<< iteration >>">
//				<<stateHistogramResultsString>>
//				<<segmentHistogramResultsString>>
//				<<probabiltiesResultsString>>
//			</result>
//			<<segmentResultsString>>
string HMMViterbiResults::allResults() {
	stringstream ss;

	// Results
	ss 
		<< resultsWithoutSegments()
		<< segmentResultsString();

	return ss.str();
}

// calculateProbabilities(HMMProbabilities* previousProbs)
//  Purpose:
//		Calculates the probabilties using the information stored in
//		this object as well as the probabilites from the previous
//		iteration of the viterbi training.
//
//		For now, only the transistion probabilties are being recalculated
//		from the data in this object.  The initaition and emission
//		probabilties are being held steady and are set to the values
//		from the previous iteration
//	Postconditions:
//		probabilites - will be populated
void HMMViterbiResults::calculateProbabilities(HMMProbabilities* previousProbs) {
	probabilities = new HMMProbabilities();

	// Use initation and emission from previous probabilites
	// initiation probabilties
	probabilities->setInitiationProbability(0, previousProbs->initiationProbability(0));
	probabilities->setInitiationProbability(1, previousProbs->initiationProbability(1));

	// emission probabilities
	probabilities->setEmissionProbability(0, 'A', previousProbs->emissionProbability(0, 'A'));
	probabilities->setEmissionProbability(0, 'T', previousProbs->emissionProbability(0, 'T'));
	probabilities->setEmissionProbability(0, 'C', previousProbs->emissionProbability(0, 'C'));
	probabilities->setEmissionProbability(0, 'G', previousProbs->emissionProbability(0, 'G'));
	probabilities->setEmissionProbability(1, 'A', previousProbs->emissionProbability(1, 'A'));
	probabilities->setEmissionProbability(1, 'T', previousProbs->emissionProbability(1, 'T'));
	probabilities->setEmissionProbability(1, 'C', previousProbs->emissionProbability(1, 'C'));
	probabilities->setEmissionProbability(1, 'G', previousProbs->emissionProbability(1, 'G'));

	// transition probabilites
	// Set from result counts
	probabilities->setTransitionProbability(0, 0, transitionCounts[0][0]/ (double) stateCounts[0]);
	probabilities->setTransitionProbability(0, 1, transitionCounts[0][1]/ (double) stateCounts[0]);
	probabilities->setTransitionProbability(1, 0, transitionCounts[1][0]/ (double) stateCounts[1]);
	probabilities->setTransitionProbability(1, 1, transitionCounts[1][1]/ (double) stateCounts[1]);
}

// Private Methods
// =============================================

// string stateHistogramResultsString()
//  Purpose:
//		Returns a string representing the state histogram
//
//		format:
//			<result type="state_histogram">
//				<<state>>=<<state count>>,
//			</result>
string HMMViterbiResults::stateHistogramResultsString() {
	stringstream ss;

	for (int i = 0; i < numStates; i++) {
		ss 
			<< i + 1 
			<< "="
			<< stateCounts[i];

		if ( i < numStates -1)
		   ss << ",";
	}

	return StringUtilities::xmlResult("state_histogram", ss.str());
}

// string segmentHistogramResultsString()
//  Purpose:
//		Returns a string representing the segment histogram
//
//		format:
//			<result type="segment_histogram">
//				<<state>>=<<segment count>>,
//			</result>
string HMMViterbiResults::segmentHistogramResultsString() {
	stringstream ss;

	for (int i = 0; i < numStates; i++) {
		ss 
			<< i + 1 
			<< "="
			<< segmentCounts[i];

		if ( i < numStates -1)
		   ss << ",";
	}

	return StringUtilities::xmlResult("segment_histogram", ss.str());
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
string HMMViterbiResults::probabilitiesResultsString() {
	stringstream ss;

	// Begin Model
	ss << "      <model type=\"hmm\">\n";

	// States
	ss << statesResultsString();

	// Probabiltiies
	ss << intitiationProbabiltiesResultsString();
	for (int i = 0; i < numStates; i++)
		ss << transitionProbablitiesResultsString(i);
	for (int i = 0; i < numStates; i++)
		ss << emissionProbablitiesResultsString(i);
	
	// End Model
	ss << "      </model>\n";

	return ss.str();
}

// string segmentResultsString()
//  Purpose:
//		Returns a string representing the segments
//
//		format:
//			<result type="segments">
//				(segment1start, segment1end),(segment2start, segment2end),...
//			</result>
string HMMViterbiResults::segmentResultsString() {
	stringstream ss;

	vector<pair<int, int>>& gcSegments = segments[1];
	
	int counter = 0;
	for (int i = gcSegments.size() - 1; i >= 0; i--) {
		pair<int, int>& segment = gcSegments[i];
		ss 
			<< "("
			<< segment.first
			<< ","
			<< segment.second
			<< ")";
		if (i > 0)
			ss << ",";

		if (counter % 5)
			ss << "\n";
		counter++;
	}

	return StringUtilities::xmlResult("segment_list", ss.str());
}

// string statesResultsString()
//  Purpose:
//		Returns a string representing the states
//
//		format:
//			<result type="states">
//				<<state1>>,<<state2>>,...
//			</result>
string HMMViterbiResults::statesResultsString() {
	stringstream ss;

	// Header 
	ss << "        <states>";

	// States
	for (int i = 0; i < numStates; i++) {
		ss << i + 1;

		if ( i < numStates -1)
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
string HMMViterbiResults::intitiationProbabiltiesResultsString() {
	stringstream ss;

	// Header 
	ss << "        <initial_state_probabilities>";

	// States
	for (int i = 0; i < numStates; i++) {
		ss
			<< i + 1
			<< "="
			<< probabilities->initiationProbability(i);

		if ( i < numStates -1)
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
string HMMViterbiResults::transitionProbablitiesResultsString(int state) {
	stringstream ss;
	ss.precision(4);

	// Header 
	ss << "        <transition_probabilities state=\"" << state + 1 << "\">";

	// States
	for (int i = 0; i < numStates; i++) {
		ss
			<< i + 1
			<< "="
			<< probabilities->transitionProbability(state, i);

		if ( i < numStates - 1)
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
string HMMViterbiResults::emissionProbablitiesResultsString(int state) {
	stringstream ss;

	// Header 
	ss << "        <emission_probabilities state=\"" << state + 1 << "\">";

	// Residues
	ss 
		<< "A=" << probabilities->emissionProbability(state, 'A') << ","
		<< "C=" << probabilities->emissionProbability(state, 'C') << ","
		<< "G=" << probabilities->emissionProbability(state, 'G') << ","
		<< "T=" << probabilities->emissionProbability(state, 'T');

	// Footer
	ss << "</emission_probabilities>\n";

	return ss.str();
}

// transitionCountsResultsString(int state)
//  Purpose:
//		Returns a string representing the transimission counts
//
//		format:
//			<result type="transitionCounts">
//				<<transition>>=<<transition count>>,
//			</result>
string HMMViterbiResults::transitionCountsResultsString() {
	stringstream ss;

	// Header 
	ss << "        <transition_counts>";

	// States
	for (int i = 0; i < numStates; i++) {
		for (int j = 0; j < numStates; j++) {
			ss
				<< i + 1 << j + 1
				<< "="
				<< transitionCounts[i][j];

			if ( i < numStates - 1 || j < numStates - 1)
			   ss << ",";
		}
	}

	// Footer
	ss << "</transition_counts>\n";

	return ss.str();
}
