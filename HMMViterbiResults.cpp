#include "HMMViterbiResults.h"
#include "StringUtilities.h"
#include <sstream>

HMMViterbiResults::HMMViterbiResults() {
}

HMMViterbiResults::HMMViterbiResults(int numberOfStates) {
	numStates = numberOfStates;
}


HMMViterbiResults::~HMMViterbiResults(){
}

string HMMViterbiResults::resultsWithoutSegments() {
	stringstream ss;

	ss << stateHistogramResultsString()
	   << segmentHistogramResultsString()
	   << probabilitiesResultsString();

	return ss.str();
}

string HMMViterbiResults::allResults() {
	stringstream ss;

	ss << resultsWithoutSegments()
	   << segmentResultsString();

	return ss.str();
}

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
	ss << "      </model>";

	return ss.str();
}

string HMMViterbiResults::segmentResultsString() {
	stringstream ss;

	vector<pair<int, int>>& gcSegments = segments[1];

	vector<pair<int, int>>::reverse_iterator rit = gcSegments.rbegin();

	for (rit = gcSegments.rbegin(); rit!= gcSegments.rend(); ++rit) {
		ss << rit->second << ",";	
	}

	return StringUtilities::xmlResult("segment_list", ss.str());

}

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
	ss << "        </states>\n";

	return ss.str();
}

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
	ss << "        </initial_state_probabilities>\n";

	return ss.str();
}

string HMMViterbiResults::transitionProbablitiesResultsString(int state) {
	stringstream ss;

	// Header 
	ss << "        <transition_probabilities state=\"" << state + 1 << "\>";

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
	ss << "        </transition_probabilities>\n";

	return ss.str();
}

string HMMViterbiResults::emissionProbablitiesResultsString(int state) {
	stringstream ss;

	// Header 
	ss << "        <emission_probabilities state=\"" << state + 1 << "\>";

	// Residues
	ss 
		<< "A=" << probabilities->emissionProbability(state, 'A') << ","
		<< "C=" << probabilities->emissionProbability(state, 'C') << ","
		<< "G=" << probabilities->emissionProbability(state, 'G') << ","
		<< "T=" << probabilities->emissionProbability(state, 'T');

	// Footer
	ss << "        </emission_probabilities>\n";

	return ss.str();
}
