/*
 * HMMPosition.h
 *
 *	This is the header file for the WDAGraph object. WDAGraph is an implementation

 *
 *  Created on: 2-15-13
 *      Author: tomkolar
 */

#ifndef HMMPROBABILITIES_H
#define HMMPROBABILITIES_H
#include <map>
using namespace std;

class HMMProbabilities
{
public:
	HMMProbabilities(void);
	~HMMProbabilities(void);

	static HMMProbabilities* initialProbabilities();
	static HMMProbabilities* testProbabilities();

	double emissionProbability(int state, char residue);
	double initiationProbability(int state);
	double transitionProbability(int beginState, int endState);

	double logEmissionProbability(int state, char residue);
	double logInitiationProbability(int state);
	double logTransitionProbability(int beginState, int endState);
	
	void setEmissionProbability(int state, char residue, double value);
	void setInitiationProbability(int state, double value);
	void setTransitionProbability(int beginState, int endState, double value);

private:

	map<int, map<char, double>> emissionProbabilities;
	map<int, map<char, double>> logEmissionProbabilities;
	double transitionProbabilities[2][2];
	double logTransitionProbabilities[2][2];
	double initiationProbabilities[2];
	double logInitiationProbabilities[2];

};

#endif // HMMPROBABILITIES_H
