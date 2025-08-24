// We have digits from 0 - 9, select several of them to be lucky digits
// Given a target integer >= 0, (ex: 3188)
// Return largest integer not greater than target integer and compose of lucky digits

// input: [3, 6, 9], 388
// output: 369

// input: [3, 6, 9], 6733
// output: 6633

#include <bits/stdc++.h>
using namespace std;

pair<string,bool> improveCurrentNum(string &curStr, vector<int> &digit) {
    string cur = curStr;
    bool improvable = false;
    for (int i = cur.size() - 1; i >= 0; i--) {
        if (cur[i] - '0' > digit.front()) {
            improvable = true;
            for (int j = digit.size() - 1; j >= 0; j--) {
                if (digit[j] < cur[i] - '0') {
                    cur[i] = digit[j] + '0';
                }
            }
            for (int j = i + 1; j < cur.size(); j++) {
                cur[j] = digit.back() + '0';
            }
            break;
        }
    }
    return {cur, improvable};
}
string getTheLargestNumber(vector<int> &digit, string &num) {
    if (digit.empty()) {
        return "-1";
    }
    sort(digit.begin(), digit.end());
    string res = "";
    int n = num.size();
    bool smaller = false;
    for (int i = 0; i < n; i++) {
        // find first lucky digit satisfy current digit
        int upper = smaller ? 9 : (num[i] - '0');
        int dit = -1;
        for (int j = digit.size() - 1; j >= 0; j--) {
            if (digit[j] <= upper) {
                dit = digit[j];
                break;
            }
        }
        // can not found
        if (dit == -1) {
            if ((int) res.size()) {
                auto [improvedStr, isImprovable] = improveCurrentNum(res, digit);
                if (!isImprovable) {
                    int len = res.size();
                    res = "";
                    len = len - 1;
                    while (len--) {
                        res += digit.back() + '0';
                    }
                    res += digit.back() + '0';
                    smaller = true;
                } else {
                    res = improvedStr;
                    for (int j = i ; j < n; j++) res += digit.back() + '0';
                    break;
                }
            } else {
                smaller = true;
            }
        } else {
            res += dit + '0';
            smaller = smaller | (dit < num[i] - '0');
        }
    }
    return res.empty() ? "-1" : res;
}
int main() {
    vector<int> luckyDigits = {3, 6, 9};
    // string targetNumber = "333111"; // "99999"
    // string targetNumber = "363111"; // "339999"
    // string targetNumber = "363111"; // "339999"
    // string targetNumber = "336111"; // "333999"
    string targetNumber = "2"; // "333999"
    string res = getTheLargestNumber(luckyDigits, targetNumber);
    cout << res << '\n';
    return 0;
}
