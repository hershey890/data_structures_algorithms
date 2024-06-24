#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace Tester {
/**
 * @brief Parse a vector of strings numerical test cases into a vector of vectors of integers.
 * @param cases A vector of strings representing numerical test cases.
 * @return A vector of vectors of numerical values
 */
vector<vector<int>> parse_int_vectors(vector<string> cases) {
    vector<vector<int>> parsed_cases(cases.size(), vector<int>());

    for(int i=0; i<cases.size(); i++) {
        vector<int> parsed_case;
        string case_str = cases[i];
        string num_str = "";

        for(int j=0; j<case_str.size(); j++) {
            if(isspace(case_str[i]))
                continue;
            else if(case_str[j] == ',') {
                parsed_case.push_back(stoi(num_str));
                num_str = "";
            } else
                num_str += case_str[j];
        }

        if(num_str.size() > 0)
            parsed_case.push_back(stoi(num_str));
        parsed_cases[i] = parsed_case;
    }

    return parsed_cases;
}

// template <typename T>
vector<int> parse_int_values(string case_str) {
    vector<int> parsed_case;
    string num_str = "";

    for(int i=0; i<case_str.size(); i++) {
        if(isspace(case_str[i]))
            continue;
        else if(case_str[i] == ',') {
            parsed_case.push_back(stoi(num_str));
            num_str = "";
        } else
            num_str += case_str[i];
    }

    if(num_str.size() > 0)
        parsed_case.push_back(stoi(num_str));
    return parsed_case;
}

}