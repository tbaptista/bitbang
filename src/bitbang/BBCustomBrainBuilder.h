//
// Created by João Simões on 11/07/17.
//

#ifndef BULLET_TEST_BBCUSTOMBRAINBUILDER_H
#define BULLET_TEST_BBCUSTOMBRAINBUILDER_H

#include <string>
#include <vector>
#include "BBRuleCondition.h"
#include "BBAction.h"

namespace bitbang
{

class BBRuleList;

class BBCustomBrainBuilder
{
public:
    BBCustomBrainBuilder();
    virtual ~BBCustomBrainBuilder();
    void LoadFile(std::string pConfigPath);
    
    void SetPerceptionList(BBPerceptionList* pPerceptionList) { perceptionList = pPerceptionList; };
    void SetActionList(BBActionList* pActionList) { actionList = pActionList; };
    
    BBRuleList* Build();

private:
    std::vector<std::string> m_brainStringRules;
    BBPerceptionList* perceptionList;
    BBActionList* actionList;
    void BuildBinaryOperationPerceptions(std::vector<std::string> *tokens,
                                         std::vector<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > >::iterator it,
                                         std::vector<std::string> *perceptions);
    std::string BuildUnaryOperationVariable(std::vector<std::string> *conditionTokens);
    bitbang::BBRuleCondition *
    CreateUnaryCondition(int pos, std::string cToken, std::vector<std::string> *conditionTokens, int unaryOperator);
    BBRuleCondition *CreateBinaryCondition(vector<string> *binaryPerceptions, int binaryOperator);
    bitbang::BBAction *GetActionFromList(string actionName);
    BBPerception *GetPerceptionFromList(string perceptionName);
    BBRuleCondition *ParseCondition(vector<string> *conditionTokens);
    void ConditionsInsideRule(string rule, vector<int> *positions);
    void SplitString(string str, vector<string> *tokens);
    bool IsNumber(const string &s);
    bool IsFloat(string myString);
};

}
#endif //BULLET_TEST_BBCUSTOMBRAINBUILDER_H
