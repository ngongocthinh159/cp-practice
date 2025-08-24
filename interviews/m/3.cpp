#include <bits/stdc++.h>
using namespace std;

// given array of integers (can be negative)
// find min(abs(arr[i] + arr[j])) (i != j)

int findMinAbsolute(vector<int> &arr) {
    int n = arr.size();
    if (n < 2) {
        return -1;
    }
    
    sort(arr.begin(), arr.end());
    int ans = INT_MAX;
    vector<int> neg, pos;
    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0) pos.push_back(arr[i]);
        else neg.push_back(arr[i]);
    }

    if (neg.empty()) {
        return pos[0] + pos[1];
    }
    if (pos.empty()) {
        return neg[neg.size() - 1] + neg[neg.size() - 2];
    }
    reverse(neg.begin(), neg.end());

    for (int i = 0, j = 0; i < (int) neg.size(); i++) {
        while (j < (int) pos.size() && pos[j] <= abs(neg[i])) j++;
        vector<int> tryIndexes;
        if (j < (int) pos.size()) {
            tryIndexes.push_back(j);
        }
        if (j - 1 >= 0) {
            tryIndexes.push_back(j - 1);
        }
        for (int idx : tryIndexes) {
            ans = min(ans, abs(pos[idx] + neg[i]));
        }
    }
    return ans;
}
int findMinAbsolute2(vector<int> &arr) {
    int n = arr.size();
    if (n < 2) {
        return -1;
    }

    sort(arr.begin(), arr.end());
    int pivotIdx = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0) {
            pivotIdx = i;
            break;
        }
    }

    if (pivotIdx == -1) {
        return arr[arr.size() - 1] + arr[arr.size() - 2];
    }
    if (pivotIdx == 0) {
        return arr[0] + arr[1];
    }

    int ans = INT_MAX;
    for (int i = pivotIdx - 1, j = pivotIdx; i >= 0 ; i--) {
        while (j < (int) arr.size() && arr[j] <= abs(arr[i])) j++;
        vector<int> tryIndexes;
        if (j < (int) arr.size()) {
            tryIndexes.push_back(j);
        }
        if (j - 1 >= pivotIdx) {
            tryIndexes.push_back(j - 1);
        }
        for (int idx : tryIndexes) {
            ans = min(ans, abs(arr[idx] + arr[i]));
        }
    }
    return ans;
}
int main() {
    vector<int> arr = {-8, -4, -1, 2, 3, 5};
    // {-1,-4,-8}
    // {2,3,5}
    cout << findMinAbsolute(arr) << '\n';
    return 0;
}