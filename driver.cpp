/*
 * driver.cpp
 *
 *	This is the driver file for creating an alignment for 3 fasta
 *  files using a weighted directed acyclic edit graph.
 *
 *	Typical use:
 *		align fastaFile1 fastaFile2 fastaFile3
 *
 *  Created on: 1-29-13
 *      Author: tomkolar
 */
#include "FastaFile.h"
#include "HiddenMarkovModel.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

int main( int argc, char *argv[] ) {

	// Check that file name and iterations were entered as arguments
	if (argc < 3) {
		cout << "Invalid # of arguments\n";
		cout << "usage: hmm fastaFile iterations\n";
		return -1;
	}

	cout << "Starting\n";

	// Get Parameters
	string fastaFileName = argv[1];
	int iterations = atoi(argv[2]);

	// Set Fasta File names
//	string fastaFileName = "c:/Users/kolart/Documents/Genome540/Assignment5/testfile1.fna";
//	int iterations = 2;

	// Create the fasta file object
	FastaFile* fastaFile = new FastaFile(fastaFileName);

	cout << "Fasta's done\n";

	// Create the Hidden Markov Model
	HiddenMarkovModel hmm(fastaFile);
	hmm.viterbiTraining(iterations);
//	cout << hmm.allScoresResultsString();
//	cout << hmm.pathStatesResultsString() << "\n";
	cout << hmm.viterbiResultsString();

}
