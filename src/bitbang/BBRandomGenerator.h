/*!
 * 
 * Copyright (c) 2011 by Tiago Baptista. All rights reserved.
 */

#ifndef BBRANDOMGENERATOR_H
#define BBRANDOMGENERATOR_H

namespace bitbang
{	
class BBRandomGenerator 
{
public:
	BBRandomGenerator();
	BBRandomGenerator(int n_seed_index);
	
	void SetSeedbyIndex(int n_seed_index);
	int GetSeedbyIndex(int n_seed_index);
	int RandInt();
	int RandInt(unsigned int n_max);
	double RandProb();
	double RandDecimal(double n_max);
	
private:
	static int RandomSeeds[];
};

extern BBRandomGenerator g_RandomGenerator;
}

#endif //BBRANDOMGENERATOR_H

