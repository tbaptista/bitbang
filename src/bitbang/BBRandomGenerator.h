/*!
 * 
 * Copyright (c) 2011-2017 by Tiago Baptista. All rights reserved.
 */

#ifndef BBRANDOMGENERATOR_H
#define BBRANDOMGENERATOR_H

struct SFMT_T;
typedef struct SFMT_T sfmt_t;

namespace bitbang
{	
class BBRandomGenerator 
{
public:
	BBRandomGenerator();
	BBRandomGenerator(int n_seed_index);
	
	void SetSeedbyIndex(int n_seed_index);
	unsigned int GetSeedbyIndex(int n_seed_index);
    unsigned int GetUsedSeed() {return m_nUsedSeed;};
	unsigned int RandInt();
	unsigned int RandInt(unsigned int n_max);
	double RandProb();
	
private:
    void SetSeed(unsigned int n_seed);
    
	static unsigned int RandomSeeds[];
    sfmt_t* m_pState;
    unsigned int m_nUsedSeed;
};

extern BBRandomGenerator g_RandomGenerator;
}

#endif //BBRANDOMGENERATOR_H

