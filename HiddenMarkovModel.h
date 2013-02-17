/*
 * HiddenMarkovModel.h
 *
 *	This is the header file for the WDAGraph object. WDAGraph is an implementation
 *
 *  Created on: 2-13-13
 *      Author: tomkolar
 */

#ifndef HIDDENMARKOVMODEL_H
#define HIDDENMARKOVMODEL_H
#include "FastaFile.h"
#include "HMMPosition.h"
#include "HMMProbabilities.h"
#include "HMMViterbiResults.h"
#include <vector>
#include <map>
using namespace std;

class HiddenMarkovModel
{
public:
	HiddenMarkovModel();
	HiddenMarkovModel(FastaFile* aFastaFile);
	~HiddenMarkovModel();

	HMMProbabilities* probabilities;
	vector<HMMViterbiResults*> viterbiResults;
	void viterbiTraining(int numIterations);

	string allScoresResultsString();
	string pathStatesResultsString();
	string viterbiResultsString();

private:

	static const int numStates;
	FastaFile* fastaFile;
	vector<HMMPosition*> model;
	bool modelBuilt;

	void buildAndCalculateModel();
	void createTransitionsFor(HMMPosition* currentPosition, HMMPosition* previousPosition);
	void calculateHighestWeightPath(HMMPosition* currentPosition);
	HMMViterbiResults* gatherViterbiResults(int iteration);
};

#endif // HIDDENMARKOVMODEL_H

