//
//  BrainConfig.h
//  AircraftEvacuation
//
//  Created by João Simões on 04/09/15.
//
//

#ifndef __AircraftEvacuation__BrainConfig__
#define __AircraftEvacuation__BrainConfig__

#include <stdio.h>
#include <string>
#include <vector>
#include "BBRuleCondition.h"
#include "ForwardChainingRuleList.hpp"

using namespace std;
using namespace bitbang;

class BrainConfig
{
public:
    BrainConfig();
    ~BrainConfig();
    
    void Load(string configPath);
    
    FordwardChainingRuleList* GetCustomBrain();
    
    void BuildBinaryOperationPerceptions(vector<string>* tokens, vector<string>::iterator it, vector<string>* perceptions);
    string BuildUnaryOperationVariable(vector<string>* conditionTokens);
    BBRuleCondition* ParseCondition(vector<string>* conditionTokens);
    
    void ConditionsInsideRule(string rule, vector<int>* positions);
    void SplitString(string str, vector<string>* tokens);
    bool IsNumber(const string& s);
    
    BBRuleCondition* CreateBinaryCondition(vector<string>* binaryPerceptions, int binaryOperator);
    BBRuleCondition* CreateUnaryCondition(int pos, string cToken, vector<string>* conditionTokens, int unaryOperator);
    BBPerception* GetPerceptionFromList(string perceptionName);
    BBAction* GetActionFromList(string perceptionName);
    
    void SetPerceptionList(BBPerceptionList* list) { perceptionList = list; };
    void SetActionList(BBActionList* list) { actionList = list; };
    
private:
    vector<string> customBrain;
    BBPerceptionList* perceptionList;
    BBActionList* actionList;
};

#endif /* defined(__AircraftEvacuation__BrainConfig__) */
