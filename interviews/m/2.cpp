#include <bits/stdc++.h>
using namespace std;
 
// You are given a list of strings, each representing an IP subnet (either IPv4 or IPv6). Write a function to sort these subnets based on the following rules:
// + IPv4 subnets should come before IPv6 subnets.
// + Within the same type, sort by network address in ascending order.
// + For subnets with the same network address, the one with the smaller subnet mask (i.e., larger network) should come first.

// Special case on IPv6: IPv6 should have 8 terms,  but sometimes terms will be reduced in at most 1 segment that has two "::", that segment should be replace with 0s
// Example: 2001:db8:abcd::     -> 2001:db8:abcd:0:0:0:0:0
//          2001:db8:abcd::1    -> 2001:db8:abcd:0:0:0:0:1

/*
input:
[
    "192.168.1.0/24",
    "2001:db8::/32",
    "10.0.0.0/8",
    "2001:db8:abcd::/48",
    "192.168.0.0/16"
]
 
output:
[
    "10.0.0.0/8",
    "192.168.0.0/16",
    "192.168.1.0/24",
    "2001:db8::/32",
    "2001:db8:abcd::/48"
]*/
 
bool isIpAddressV4(string &ip) {
    int n = ip.size();
    bool isV4 = false;
    for (int i = 0; i < n; i++) {
        if (ip[i] == '.') {
            isV4 = true;
            break;
        }
    }
    return isV4;
}
pair<string,string> sparateToIpAndNetMask(string &ip) {
    int n = ip.size();
    string curIp = "";
    string curMask = "";
    int i = 0;
    while (i < n && ip[i] != '/') {
        curIp += ip[i];
        i++;
    }
    i++;
    while (i < n) {
        curMask += ip[i];
        i++;
    }
    return {curIp, curMask};
}
int convertCharToNum(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    return c - 'a' + 10;
}
vector<int> divideToNumbers(string &ip) {
    vector<int> res;
    int n = ip.size();
    bool isV4 = isIpAddressV4(ip);
    int mul = isV4 ? 10 : 16;
    for (int i = 0; i < n;) {
        int curNum = 0;
        while (i < n && ip[i] != '.' && ip[i] != ':') {
            curNum = mul * curNum + convertCharToNum(ip[i]); // 'a' - 10
            i++;
        }
        i++;
        res.push_back(curNum);
    }
    return res;
}
int cmpIp(string &ip1, string &ip2) { // return 0 if equal, -1 smaller, 1 larger
    vector<int> n1 = divideToNumbers(ip1);
    vector<int> n2 = divideToNumbers(ip2);
    int i = 0, n = n1.size();
    while (i < n) {
        if (n1[i] < n2[i]) {
            return -1;
        }
        if (n1[i] > n2[i]) {
            return 1;
        }
        i++;
    }
    return 0;
}
void sortIpAddress(vector<string> &ipAddress) {
    auto cmp = [&](string &ip1, string &ip2) {
        bool isV41 = isIpAddressV4(ip1);
        bool isV42 = isIpAddressV4(ip2);
        if (isV41 && !isV42)
            return true;
        if (!isV41 && isV42)
            return false;
        auto [curIp1, curMask1] = sparateToIpAndNetMask(ip1);
        auto [curIp2, curMask2] = sparateToIpAndNetMask(ip2);
        int ipCmpRes = cmpIp(curIp1, curIp2);
        if (ipCmpRes == 0) {
            return curMask1 < curMask2;
        }
        return ipCmpRes == -1 ? true : false;
    };
    sort(ipAddress.begin(), ipAddress.end(), cmp);
}
int main() {
    vector<string> ipAddresses = {  "192.168.1.0/24",
                                    "2001:db8::/32",
                                    "10.0.0.0/8",
                                    "2001:db8:abcd::/48",
                                    "192.168.0.0/16"};
    sortIpAddress(ipAddresses);
    for (int i = 0; i < (int) ipAddresses.size(); i++) {
        cout << ipAddresses[i] << '\n';
    }
    return 0;
}