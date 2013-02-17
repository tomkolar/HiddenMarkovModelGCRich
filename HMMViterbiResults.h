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
#include <string>
using namespace std;

class HMMViterbiResults
{
public:
	HMMViterbiResults();
	HMMViterbiResults(int iteration, int numberOfStates);
	~HMMViterbiResults();

	int iteration;
	int numStates;
	vector<int> stateCounts;
	vector<int> segmentCounts;
	HMMProbabilities* probabilities;
	map<int,vector<pair<int,int>>> segments;
	vector<vector<int>> transitionCounts;

	string resultsWithoutSegments();
	string allResults();
	void calculateProbabilities(HMMProbabilities* previousProbs);

private:

	string stateHistogramResultsString();
	string segmentHistogramResultsString();
	string probabilitiesResultsString();
	string segmentResultsString();
	string statesResultsString();
	string intitiationProbabiltiesResultsString();
	string transitionProbablitiesResultsString(int state);
	string emissionProbablitiesResultsString(int state);
	string transitionCountsResultsString();

};

#endif // HMMVITERBIRESULTS_H
