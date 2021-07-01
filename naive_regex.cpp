#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <string>


/**
 *
 给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。

'.' 匹配任意单个字符
'*' 匹配零个或多个前面的那一个元素
所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。

*/

template<typename T>
class FiniteStateMachine {
    public:
        static const char sChAny; 
    public:
        FiniteStateMachine()
            : miSucc(-1)
        {
        }


        void start() {
            //mStates.clear();
            //mStates.insert(0);
        }


        bool take(T input) {

            std::cout << "take " << input  << " on (";
            for (int state : mStates) {
                std::cout << state << ',';
            }
            std::cout << ")";

            std::set<int> newStateSet;
            for (int state : mStates) {
                auto trans = stateRules.find(state);
                if (trans != stateRules.end()) {
                   for (auto tranRule : trans->second) {
                       if (input == tranRule.first || sChAny == tranRule.first) {
                           newStateSet.insert(tranRule.second);
                       }                  
                   }
                    
                }
            }

            std::cout << "-> (";
            for (int state : newStateSet) {
                std::cout << state << ',';
            }
            std::cout << ")" << std::endl;

            if (newStateSet.empty()) {
                mStates.clear();
                return false;
            } else {
                mStates = newStateSet;
                return true;
            }
        }

    public:
        void addRule(int fromState, T input, int toState) {
            std::cout << "add rule: " << fromState << "--" << input << "-->" << toState << std::endl;
            std::vector<std::pair<T, int> > &rule = stateRules[fromState];
            rule.push_back(std::make_pair(input, toState));
        }

        void desc() {
            for (const auto& entry : stateRules) {
                for(const auto& trans : entry.second) {
                    std::cout << entry.first << "-" << (trans.first == '\0' ? '.' : trans.first) << "->" << trans.second << std::endl;
                }
            }
            std::cout << "succ state: " << miSucc << std::endl;
        }

        void setStart(std::set<int> startStates) {
            mStates = startStates;
        }


        void setSucc(int iSuccState) {
            miSucc = iSuccState;
        }

        bool match() {
            return mStates.find(miSucc) != mStates.end() ;
        }

    private:
        std::set<int> mStates;
        int miSucc;
        std::map<int, std::vector<std::pair<T, int> > > stateRules;
};

template<typename T>
const char FiniteStateMachine<T>::sChAny =  '\0';
/**
 */
class Solution {
    public:
        bool match(const std::string &src, const std::string &regex) {
            FiniteStateMachine<char> matcher = compile(regex);

            matcher.desc();
            matcher.start();
            for (char ch : src) {
                if (!matcher.take(ch)) {
                    return false;
                }
            }
            return matcher.match();
        }
        

    private:
        FiniteStateMachine<char> compile(const std::string &regex) const {
            FiniteStateMachine<char> machine;
            int state = 1;
            std::set<int> startStates;
            startStates.insert(0);
            startStates.insert(1);
            char chLast = '\0';
            std::vector<std::pair<int, char> > transparentList;
            bool lastRuleIsStar = false;
            // for now ,not support '\' escape
            int curPos = -1;
            for (char ch : regex) {
                curPos += 1;
                if (chLast == '\0') {
                    chLast = ch;
                    continue;
                }
                switch (ch) {
                    case '.': {
                        if (chLast != '*') {
                            if (chLast == '.') {
                                chLast = FiniteStateMachine<char>::sChAny;
                            }
                            int iNewState = state + 1;
                            machine.addRule(state, chLast, iNewState);
                            transparentList.clear();
                            transparentList.push_back(std::pair<int, char>(state, chLast));
                            state = iNewState;
                        }
                        break;
                    }

                    case '*': {
                        if (chLast == '.') {
                            chLast = FiniteStateMachine<char>::sChAny;
                        }
                        machine.addRule(state, chLast, state);
                        int newState = state + 1;
                        machine.addRule(state, chLast, newState);
                        if (transparentList.empty()) {
                                startStates.insert(newState);
                        } 
                        else {
                            for (auto stateCharPair : transparentList) {
                                for (int i = stateCharPair.first; i < state; ++i) {
                                    char transChar;
                                    if (stateCharPair.second == '.') {
                                        transChar = FiniteStateMachine<char>::sChAny;
                                    } else {
                                        transChar = stateCharPair.second;
                                    }
                                    machine.addRule(i, transChar, newState);
                                }
                            }
                        }
                        transparentList.push_back(std::pair<int, char>(state, chLast));
                        state = newState;
                        lastRuleIsStar = true;

                        break;
                    }

                    default: {
                        if (chLast != '*') {
                            if (chLast == '.') {
                                chLast = FiniteStateMachine<char>::sChAny;
                            }
                            int iNewState = state + 1;
                            machine.addRule(state, chLast, iNewState);
                            transparentList.clear();
                            transparentList.push_back(std::pair<int, char>(state, chLast));
                            state = iNewState;
                        }
                        break;
                    }
                } 
                chLast = ch;
            }

            if (chLast != '*') {
                int iNewState = state + 1;
                if (chLast == '.') {
                    machine.addRule(state, FiniteStateMachine<char>::sChAny, iNewState);
                } else {
                    machine.addRule(state, chLast, iNewState);
                }
                state = iNewState;
            }
            machine.setSucc(state);
            machine.setStart(startStates);
            return std::move(machine);
        }

};

int main(int argc, const char ** argv) {
    Solution sol;
    bool matches = sol.match("bbbba", ".*a*a");
    std::cout << matches << std::endl;


    matches = sol.match("aaba", "ab*a*c*a");
    std::cout << matches << std::endl;

    return 0;
}
