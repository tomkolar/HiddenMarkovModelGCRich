/*
 * HMMViterbiResults.h
 *
 *	This is the header file for the WDAGraph object. WDAGraph is an implementation

 *
 *  Created on: 2-15-13
 *      Author: tomkolar
 */

#ifndef HMMVITERBIRESULTS_H
#define HMMVITERBIRESULTS_H
#include "HMMProbabilities.h"
#include <map>
#include <vector>
using namespace std;

class HMMViterbiResults
{
public:
	HMMViterbiResults();
	HMMViterbiResults(int numberOfStates);
	~HMMViterbiResults();

	int numStates;
	vector<int> stateCounts;
	vector<int> segmentCounts;
	HMMProbabilities* probabilities;
	map<int,vector<pair<int,int>>> segments;

	string resultsWithoutSegments();
	string allResults();
	string stateHistogramResultsString();
	string segmentHistogramResultsString();
	string probabilitiesResultsString();
	string segmentResultsString();

private:

	string statesResultsString();
	string intitiationProbabiltiesResultsString();
	string transitionProbablitiesResultsString(int state);
	string emissionProbablitiesResultsString(int state);

};

#endif // HMMVITERBIRESULTS_H
