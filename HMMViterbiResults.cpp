#include "HMMViterbiResults.h"
#include "StringUtilities.h"
#include <sstream>

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


HMMViterbiResults::~HMMViterbiResults(){
}

string HMMViterbiResults::resultsWithoutSegments() {
	stringstream ss;

	// Header
	ss << "    <result type=\"viterbi_iteration\" iteration=\"" << iteration << "\">\n";

	// Results
	ss 
		<< stateHistogramResultsString()
		<< segmentHistogramResultsString()
		<< probabilitiesResultsString();

	ss 	<< transitionCountsResultsString();

	// Footer
	ss << "    </result>\n";

	return ss.str();
}

string HMMViterbiResults::allResults() {
	stringstream ss;

	// Results
	ss 
		<< resultsWithoutSegments()
		<< segmentResultsString();

	return ss.str();
}

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
	ss << "      </model>\n";

	return ss.str();
}

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

string HMMViterbiResults::transitionProbablitiesResultsString(int state) {
	stringstream ss;

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
