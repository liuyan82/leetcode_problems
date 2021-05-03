#include <iostream>
#include <string>
#include <map>

template<typename T>
class FiniteStateMachine {
    public:
        void start() {
        }

        void take(T input) {
        }

        int getCurrentState() {
            return state;
        }

    public:
        void addRule(int fromState, T input, int toState) {
            std::map<int, int> &rule = stateRules[input];
            rule[fromState] = toState;
        }

    private:
        int state;
        std::map<T, std::map<int, int> > stateRules;
};

class Solution {
    public:
        bool match(const std::string &src, const std::string &regex) {
            FiniteStateMachine<char> matcher = compile(regex);
            return false;
        }
        

    private:
        FiniteStateMachine<char> compile(const std::string &regex) const {
            FiniteStateMachine<char> machine;
            int state = 0;
            for (char c : regex) {
                machine.addRule(state, c, ++state);
            }
            return std::move(machine);
        }

};

int main(int argc, const char ** argv) {
    Solution sol;
    std::cout << sol.match("abcd", "abcd") << std::endl;
    return 0;
}
