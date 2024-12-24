#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>
#include <cctype>
#include <vector>
#include <unordered_set>
#include <iomanip> // For std::setw and formatting
using namespace std;

#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>
#include <cctype>
#include <vector>
#include <unordered_set>
#include <iomanip> // For std::setw and formatting
using namespace std;

// Evaluate logical expression
bool evaluateLogicalExpression(const string& expr, const vector<bool>& varValues, const unordered_map<char, int>& varIndex) {
    stack<bool> s;
    for (int i = 0; i < expr.size(); ++i) {
        char ch = expr[i];

        // If the character is a variable
        if (isalpha(ch)) {
            if (varIndex.find(ch) == varIndex.end()) {
                return false;  // Variable not found
            }
            s.push(varValues[varIndex.at(ch)]);
        }
        // Logical NOT
        else if (ch == '!') {
            if (s.empty()) {
                return false;  // Invalid expression
            }
            bool top = s.top();
            s.pop();
            s.push(!top);
        }
        // Logical AND
        else if (ch == '&') {
            bool top1 = s.top(); s.pop();
            i++;

            bool top2;
            if (expr[i] == '!')
            {
                i++;
                top2 = !varValues[varIndex.at(expr[i])];
            }

            else
                top2 = varValues[varIndex.at(expr[i])];

            s.push(top1 && top2);
        }
        // Logical OR
        else if (ch == '|') {

            bool top1 = s.top(); s.pop();
            i++;
            bool top2;
            if (expr[i] == '!')
            {
                i++;
                top2 = !varValues[varIndex.at(expr[i])];
            }

            else
                top2 = varValues[varIndex.at(expr[i])];


            s.push(top1 || top2);
        }
        // Implication (->)
        else if (ch == '-' && i + 1 < expr.size() && expr[i + 1] == '>') {
            bool top1 = s.top(); s.pop();
            i += 2;
            bool top2;
            if (expr[i] == '!')
            {
                i++;
                top2 = !varValues[varIndex.at(expr[i])];
            }

            else
                top2 = varValues[varIndex.at(expr[i])];

            s.push(!top1 || top2);  // Top2 -> Top1 is equivalent to !Top2 || Top1

        }
        // Biconditional (<->)
        else if (ch == '<' && i + 2 < expr.size() && expr[i + 1] == '-' && expr[i + 2] == '>') {
            bool top1 = s.top(); s.pop();
            i += 3;
            bool top2;
            if (expr[i] == '!')
            {
                i++;
                top2 = !varValues[varIndex.at(expr[i])];
            }

            else
                top2 = varValues[varIndex.at(expr[i])];

            s.push((top1 && top2) || (!top1 && !top2));  // Top1 <-> Top2 is equivalent to (Top1 && Top2) || (!Top1 && !Top2)

        }
    }

    if (s.size() != 1) {
        return false;  // Invalid expression (should only be one value at the end)
    }

    return s.top();  // Final result (either true or false)
}

// Extract unique variables
vector<char> extractVariables(const string& expr) {
    unordered_set<char> variables;
    for (char ch : expr) {
        if (isalpha(ch)) {
            variables.insert(ch);
        }
    }
    return vector<char>(variables.begin(), variables.end());
}

int main() {
    int numPremises;
    cout << "Enter the number of premises: ";
    cin >> numPremises;
    cin.ignore();

    vector<string> premises(numPremises);
    for (int i = 0; i < numPremises; ++i) {
        cout << "Enter premise " << i + 1 << ": ";
        getline(cin, premises[i]);
    }

    string conclusion;
    cout << "Enter the conclusion: ";
    getline(cin, conclusion);

    unordered_set<char> variableSet;
    for (const auto& premise : premises) {
        auto vars = extractVariables(premise);
        variableSet.insert(vars.begin(), vars.end());
    }
    auto conclusionVars = extractVariables(conclusion);
    variableSet.insert(conclusionVars.begin(), conclusionVars.end());

    vector<char> variables(variableSet.begin(), variableSet.end());
    unordered_map<char, int> varIndex;
    for (int i = 0; i < variables.size(); ++i) {
        varIndex[variables[i]] = i;
    }

    int numVars = variables.size();
    int totalRows = 1 << numVars;
    bool isSatisfiable = false, isValid = true;

    cout << "\nTruth Table:\n";
    for (char var : variables) {
        cout << setw(8) << var;
    }
    for (int i = 0; i < numPremises; ++i) {
        cout << setw(16) << "Premise " + to_string(i + 1);
    }
    cout << setw(16) << "Conclusion\n";

    for (int i = 0; i < totalRows; ++i) {
        vector<bool> values(numVars);
        for (int j = 0; j < numVars; ++j) {
            values[j] = (i >> (numVars - j - 1)) & 1;
        }

        for (bool value : values) {
            cout << setw(8) << value;
        }

        bool allPremisesTrue = true;
        for (int j = 0; j < numPremises; ++j) {
            bool result = evaluateLogicalExpression(premises[j], values, varIndex);
            cout << setw(16) << result;
            allPremisesTrue &= result;
        }

        bool conclusionResult = evaluateLogicalExpression(conclusion, values, varIndex);
        cout << setw(16) << conclusionResult;

        if (allPremisesTrue) {
            isSatisfiable = true;
            if (!conclusionResult) {
                isValid = false;
            }
        }

        cout << "\n";
    }

    cout << "\nAnalysis Results:\n";
    cout << "The set of statements is " << (isSatisfiable ? "SATISFIABLE" : "NOT SATISFIABLE") << ".\n";
    cout << "The argument is " << (isValid ? "VALID" : "FALSIFIABLE") << ".\n";

    return 0;
}
