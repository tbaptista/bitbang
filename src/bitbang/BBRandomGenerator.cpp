/*!
 * 
 * Copyright (c) 2011-2017 by Tiago Baptista. All rights reserved.
 */

#include "BBRandomGenerator.h"
#include "BBOS.h"

//extern "C" {
#include "SFMT.h"
//}

#include <iostream>
#include <stdlib.h>

namespace bitbang
{
	BBRandomGenerator g_RandomGenerator;
	
	unsigned int BBRandomGenerator::RandomSeeds[] = {181848, 448665, 338504, 829216, 603274, 47467, 616831, 748891, 638596, 197714, 626576, 444912, 330027, 220148, 20420, 461986, 678217, 581420, 50491, 648489, 919368, 833857, 40253, 220575, 661044, 20837, 280229, 394048, 418380, 839148, 939621, 829489, 723296, 114168, 858800, 48482, 17144, 711470, 604037, 397329, 87339, 147167, 962216, 839307, 276066, 171778, 309969, 850716, 651036, 597956, 564033, 411839, 685591, 209376, 682923, 170443, 928322, 852441, 986503, 819470, 712472, 458391, 547641, 237491, 191418, 918405, 210690, 380757, 666394, 502361, 531733, 558282, 744364, 257634, 910264, 99696, 483110, 870569, 662194, 970010, 423372, 802132, 775688, 469673, 47230, 613878, 294379, 721672, 731210, 22513, 769828, 704083, 269689, 301917, 999552, 148337, 116718, 57842, 287398, 108434, 881199, 481404, 98531, 246832, 215169, 773245, 973421, 25679, 936493, 22462, 387696, 415398, 291567, 560798, 564535, 269405, 226096, 849006, 567261, 276838, 208982, 428831, 377881, 406895, 476626, 94206, 740039, 161009, 442493, 338744, 627904, 57197, 769022, 746935, 638508, 353021, 853565, 26029, 398763, 128096, 133774, 876120, 201447, 462706, 465712, 161894, 144333, 965976, 537522, 308379, 106607, 78826, 334214, 330222, 738830, 247277, 882312, 714953, 887808, 792263, 172687, 902296, 543950, 695258, 36997, 861812, 877309, 514767, 900814, 695975, 665994, 456920, 576968, 542248, 998721, 182585, 273058, 982442, 841767, 579131, 692043, 910597, 977185, 665541, 208282, 726343, 30215, 350359, 517044, 24912, 825163, 622791, 237669, 61907, 894515, 843168, 387587, 548901, 434204, 872502};
	
	BBRandomGenerator::BBRandomGenerator()
	{
        m_pState = new sfmt_t;
		SetSeed(BBOS::GetRandomSeed());
	}
	
	BBRandomGenerator::BBRandomGenerator(int n_seed_index)
	{
        BBRandomGenerator();
        
		if ((n_seed_index < 100) && (n_seed_index >= 0))
		{
            SetSeed(RandomSeeds[n_seed_index]);
            
			cout << "Random number generator initialized with index " << n_seed_index << ": " << RandomSeeds[n_seed_index] << endl;
		}
		else
		{
			cerr << "Error setting random seed by index. Index value is invalid: " << n_seed_index << endl;
		}
	}
	
	void BBRandomGenerator::SetSeedbyIndex(int n_seed_index)
	{
		if ((n_seed_index < 100) && (n_seed_index >= 0))
		{
            SetSeed(RandomSeeds[n_seed_index]);
		}
		else
		{
			cerr << "Error setting random seed by index. Index value is invalid: " << n_seed_index << endl;
		}
	}
	
	unsigned int BBRandomGenerator::GetSeedbyIndex(int n_seed_index)
	{
		if ((n_seed_index < 100) && (n_seed_index >= 0))
		{
			return RandomSeeds[n_seed_index];
		}
		else 
		{
			cerr << "Error getting random seed by index. Index value is invalid: " << n_seed_index << endl;
			return 0;
		}

	}
    
	/**
	 Generate a random unsigned integer from full range of 32 bits.

	 @return A random value.
	 */
	unsigned int BBRandomGenerator::RandInt()
	{
		return sfmt_genrand_uint32(m_pState);
	}
	
	/**
	 Generate a random unsigned integer in the range of 0 (inclusive) to n_max (exclusive).

	 @param n_max The maximum value to generate (exclusive).
	 @return A random value.
	 */
	unsigned int BBRandomGenerator::RandInt(unsigned int n_max)
	{
		if (n_max < 1)
		{
			return 0;
		}
		else
		{
			return sfmt_genrand_uint32(m_pState) % n_max;
		}
	}
	
	double BBRandomGenerator::RandProb()
	{
		return sfmt_genrand_real1(m_pState);
	}
    

//Private members
    
    void BBRandomGenerator::SetSeed(unsigned int n_seed)
    {
        m_nUsedSeed = n_seed;
        sfmt_init_gen_rand(m_pState, n_seed);
        
        //Also seed the system standard random generator
        srand(m_nUsedSeed);
        
        cout << "Random number generator initialized with seed: " << m_nUsedSeed << endl;
    }
}
