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

/*	// Check that file name was  entered as argument
	if (argc < 4) {
		cout << "Invalid # of arguments\n";
		cout << "usage: align fastaFile1 fastaFile2 fastaFile3\n";
		return -1;
	}

	cout << "Starting\n";

	// Get Fasta File names
	string fastaFileName1 = argv[1];
	string fastaFileName2 = argv[2];
	string fastaFileName3 = argv[3];
*/
	// Set Fasta File names
	string fastaFileName = "c:/Users/kolart/Documents/Genome540/Assignment5/testfile1.fna";

	// Create the fasta file object
	FastaFile* fastaFile = new FastaFile(fastaFileName);

	cout << "Fasta's done\n";

	// Create the Hidden Markov Model
	HiddenMarkovModel hmm(fastaFile);
	hmm.viterbiTraining(1);
	cout << hmm.allScoresResultsString();
	cout << hmm.pathStatesResultsString();
	cout << hmm.viterbiResultsString();
	hmm.allScoresResultsString();

}
