//
//  AntBrainConfig.h
//  AntWorld
//
//  Created by João Miguel Moreira de Carvalho Brás Simões on 27/04/15.
//
//

#ifndef ANTBRAINCONFIG_H_
#define ANTBRAINCONFIG_H_

#include <stdio.h>
#include <string>
#include <vector>
#include "BBRuleCondition.h"
#include "BBRuleList.h"

using namespace std;
using namespace bitbang;

class AntBrainConfig
{
public:
    AntBrainConfig();
    ~AntBrainConfig();
    void Load(string configPath);
    
    BBRuleList* GetCustomBrain(int brainRulesIndex);
    
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
    
    vector< vector<string>* >* customBrains;
    BBPerceptionList* perceptionList;
    BBActionList* actionList;
    
};

#endif //ANTBRAINCONFIG_H_