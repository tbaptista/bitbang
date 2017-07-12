//
// Created by João Simões on 11/07/17.
//

#include "BBCustomBrainBuilder.h"
#include "BBRule.h"
#include <fstream>
#include <iostream>
#include <bitbang/src/bitbang/perceptions/BBPerceptionBoolean.h>
#include <sstream>
#include <bitbang/src/bitbang/perceptions/BBPerceptionNumber.h>
#include "BBRuleList.h"

namespace bitbang
{

using namespace std;

BBCustomBrainBuilder::BBCustomBrainBuilder()
{

}

BBCustomBrainBuilder::~BBCustomBrainBuilder()
{

}

void BBCustomBrainBuilder::LoadFile(std::string pConfigPath)
{
    std::ifstream brainFile;
    std::string cRule;
    
    m_brainStringRules.clear();
    brainFile.open(pConfigPath.c_str());
    
    if (brainFile.is_open())
    {
        while (getline(brainFile, cRule))
        {
            m_brainStringRules.push_back(cRule);
        }
    } else
    {
        std::cerr << "Error opening custom brain file!" << std::endl;
        exit(1);
    }
}

BBRuleList* BBCustomBrainBuilder::Build()
{
    size_t thenPosition;
    vector<string>::iterator cRule;
    vector<string> *cConditionElem = new vector<string>;
    vector<int> *positionOfConditions = new vector<int>;
    vector<int>::iterator cCondition;
    BBRuleList *pBrain = new BBRuleList();
    BBRule *pRule;
    BBRuleCondition *pCondition;
    string action, cConditionString;
    int endCondition;
    
    string cToken;
    int i;
    
    for (cRule = m_brainStringRules.begin(); cRule != m_brainStringRules.end(); ++cRule)
    {
        pRule = new BBRule();
        
        positionOfConditions->clear();
        
        ConditionsInsideRule(*cRule, positionOfConditions); //Each position holds the initial position of each "AND"
        
        thenPosition = (*cRule).find("THEN");
        
        action = (*cRule).substr(thenPosition + 5, (*cRule).length());
        
        for (cCondition = positionOfConditions->begin(); cCondition != positionOfConditions->end(); ++cCondition)
        {
            cConditionElem->clear();
            
            if (*cCondition == *(positionOfConditions->end() - 1))
            {
                endCondition = thenPosition - 1;
            } else
            {
                endCondition = *(cCondition + 1);
            }
            
            cConditionString = (*cRule).substr((*cCondition) + 4, endCondition - ((*cCondition) + 4));
            
            SplitString(cConditionString, cConditionElem);
            
            pCondition = ParseCondition(cConditionElem);
            
            if (pCondition == NULL)
            {
                cerr << "NULL condition" << endl;
                exit(1);
            }
            
            pRule->AddCondition(*pCondition);
        }
        
        pRule->SetAction(GetActionFromList(action));
        
        pBrain->AddRule(pRule);
    }
    
    return pBrain;
}

/*
 Split a given string by white spaces.
 
 Param:
 str - string to be spllited
 tokens - vector to store tokens
 */
void BBCustomBrainBuilder::SplitString(string str, vector<string> *tokens)
{
    string cToken;
    istringstream iss(str);
    
    while (iss >> cToken)
    {
        tokens->push_back(cToken);
    }
}

/*
 Load brain rules from a given text file to a string array list.
 
 Params:
 configPath = full path to brain file
 */
void BBCustomBrainBuilder::ConditionsInsideRule(string rule, vector<int> *positions)
{
    positions->push_back(-1);
    
    size_t pos = rule.find("AND", 0);
    while (pos != string::npos)
    {
        positions->push_back(pos);
        pos = rule.find("AND", pos + 1);
    }
}

/*
 Parse a given condition.
 
 Example of conditionTokens structure:
 
 isnot(Feature placing_pheromone)
 conditionTokens = ["isnot(Feature", "placing_pheromone)"]
 
 Returns a new BBRuleCondition*
 */
BBRuleCondition *BBCustomBrainBuilder::ParseCondition(vector<string> *conditionTokens)
{
    BBRuleCondition *pRuleCondition;
    string cToken, cTokenOperator;
    int i;
    int condOperator = 0;   //1 - True | 2 - False | 3 - Greater | 4 - Equal | 5 - Less
    string cPerception;
    vector<string>::iterator operatorIt, cPosition;
    vector<string> binaryPerceptions;
    
    cToken = (*conditionTokens)[0];
    
    if (cToken.substr(0, 4) == "not(") //False
    {
        pRuleCondition = CreateUnaryCondition(4, cToken, conditionTokens, BBPerceptionBoolean::nOPNOT);
    } else if (cToken.substr(0, 7) == "istrue(") //True
    {
        pRuleCondition = CreateUnaryCondition(7, cToken, conditionTokens, BBPerceptionBoolean::nOPTRUE);
    } else //Binary operation
    {
        if ((operatorIt = find(conditionTokens->begin(), conditionTokens->end(), "=")) !=
            conditionTokens->end()) //Equal
        {
            BuildBinaryOperationPerceptions(conditionTokens, operatorIt, &binaryPerceptions);
            
            pRuleCondition = CreateBinaryCondition(&binaryPerceptions, BBPerceptionNumber::nOPEQUAL);
        } else if ((operatorIt = find(conditionTokens->begin(), conditionTokens->end(), ">")) !=
                   conditionTokens->end()) //Greater
        {
            BuildBinaryOperationPerceptions(conditionTokens, operatorIt, &binaryPerceptions);
            
            pRuleCondition = CreateBinaryCondition(&binaryPerceptions, BBPerceptionNumber::nOPGREATER);
        } else if ((operatorIt = find(conditionTokens->begin(), conditionTokens->end(), "<")) !=
                   conditionTokens->end()) //Less
        {
            BuildBinaryOperationPerceptions(conditionTokens, operatorIt, &binaryPerceptions);
            
            pRuleCondition = CreateBinaryCondition(&binaryPerceptions, BBPerceptionNumber::nOPLESS);
            
        }
    }
    
    if (pRuleCondition == NULL)
    {
        cerr << "Error parsing condition!" << endl;
        exit(1);
    }
    
    return pRuleCondition;
}

/*
 Returns BBPerception* given the perception name
 */
BBPerception *BBCustomBrainBuilder::GetPerceptionFromList(string perceptionName)
{
    BBPerceptionList::iterator it;
    
    for (it = perceptionList->begin(); it != perceptionList->end(); ++it)
    {
        if (((*it)->GetName()).compare(perceptionName) == 0)
        {
            return *it;
        }
    }
    
    cerr << "Perception not found! - " << perceptionName << endl;
    exit(1);
}

/*
 Returns BBAction* given the action name
 */
BBAction *BBCustomBrainBuilder::GetActionFromList(string actionName)
{
    BBActionList::iterator it;
    
    for (it = actionList->begin(); it != actionList->end(); ++it)
    {
        if (((*it)->GetName()).compare(actionName) == 0)
        {
            return *it;
        }
    }
    
    cerr << "Action not found!" << endl;
    exit(1);
}

/*
 Creates a new binary operator condition given the binary perceptuons and binary operator.
 */
BBRuleCondition *BBCustomBrainBuilder::CreateBinaryCondition(vector<string> *binaryPerceptions, int binaryOperator)
{
    BBRuleCondition *pRuleCondition;
    
    if (IsNumber((*binaryPerceptions)[1]))
    {
        pRuleCondition = new BBRuleCondition((BBPerceptionNumber *) GetPerceptionFromList((*binaryPerceptions)[0]),
                                             atoi((*binaryPerceptions)[1].c_str()), binaryOperator);
    } else
    {
        pRuleCondition = new BBRuleCondition((BBPerceptionNumber *) GetPerceptionFromList((*binaryPerceptions)[0]),
                                             (BBPerceptionNumber *) GetPerceptionFromList((*binaryPerceptions)[1]),
                                             binaryOperator);
    }
    
    return pRuleCondition;
}

/*
 Creates a new unary operator condition.
 */
BBRuleCondition *
BBCustomBrainBuilder::CreateUnaryCondition(int pos, string cToken, vector<string> *conditionTokens, int unaryOperator)
{
    BBRuleCondition *pRuleCondition;
    string cPerception;
    
    if (cToken.substr(pos, cToken.length()) == "Feature") //Boolean feature perception
    {
        cPerception = BuildUnaryOperationVariable(conditionTokens);
    } else //Boolean perception
    {
        cPerception = BuildUnaryOperationVariable(conditionTokens);
    }
    
    pRuleCondition = new BBRuleCondition((BBPerceptionBoolean *) GetPerceptionFromList(cPerception), unaryOperator);
    
    return pRuleCondition;
}

/*
 Verify if a given string is a number
 */
bool BBCustomBrainBuilder::IsNumber(const string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

/*
 Extracts expression of a given unary condition
 */
string BBCustomBrainBuilder::BuildUnaryOperationVariable(vector<string> *conditionTokens)
{
    
    string token, variable;
    int i, pos;
    vector<string>::iterator it;
    
    variable = "";
    
    token = (*conditionTokens)[0];
    pos = token.find("(") + 1;
    variable = token.substr(pos);
    variable += " ";
    
    if (conditionTokens->size() == 1)
        return variable.substr(0, variable.size() - 2);
    
    for (it = conditionTokens->begin() + 1; it != conditionTokens->end(); ++it)
    {
        variable += *it;
        variable += " ";
    }
    
    return variable.substr(0, variable.size() - 2);
}

/*
 Extracts expressions of a given binary condition
 */
void BBCustomBrainBuilder::BuildBinaryOperationPerceptions(vector<string> *tokens, vector<string>::iterator it,
                                                           vector<string> *perceptions)
{
    string p1, p2;
    vector<string>::iterator cPosition;
    
    cPosition = tokens->begin();
    while (cPosition != it)
    {
        p1 += *cPosition;
        if (cPosition + 1 != it)
        {
            p1 += " ";
        }
        ++cPosition;
    }
    ++it;
    while (it != tokens->end())
    {
        p2 += *it;
        if (it + 1 != tokens->end())
            p2 += " ";
        ++it;
    }
    
    perceptions->push_back(p1);
    perceptions->push_back(p2);
}

}