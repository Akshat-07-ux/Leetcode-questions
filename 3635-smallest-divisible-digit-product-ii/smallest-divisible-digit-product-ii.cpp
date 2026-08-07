#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    struct Factors {
        int c2 = 0, c3 = 0, c5 = 0, c7 = 0;
    };

    Factors getDigitFactors(int d) {
        Factors f;
        while (d % 2 == 0) { f.c2++; d /= 2; }
        while (d % 3 == 0) { f.c3++; d /= 3; }
        if (d == 5) f.c5++;
        if (d == 7) f.c7++;
        return f;
    }

    string getBestDigitsFor23(int c2, int c3) {
        string best = "";
        
        for (int cnt8 = c2 / 3; cnt8 >= 0; cnt8--) {
            int rem2_after_8 = c2 - cnt8 * 3;
            for (int cnt9 = c3 / 2; cnt9 >= 0; cnt9--) {
                int rem3_after_9 = c3 - cnt9 * 2;
                
                for (int cnt6 = min(rem2_after_8, rem3_after_9); cnt6 >= 0; cnt6--) {
                    int rem2 = rem2_after_8 - cnt6;
                    int rem3 = rem3_after_9 - cnt6;

                    int cnt4 = rem2 / 2;
                    int cnt2 = rem2 % 2;
                    int cnt3 = rem3;

                    string candidate = "";
                    candidate.append(cnt2, '2');
                    candidate.append(cnt3, '3');
                    candidate.append(cnt4, '4');
                    candidate.append(cnt6, '6');
                    candidate.append(cnt8, '8');
                    candidate.append(cnt9, '9');

                    sort(candidate.begin(), candidate.end());

                    if (best.empty() || candidate.length() < best.length() || 
                       (candidate.length() == best.length() && candidate < best)) {
                        best = candidate;
                    }
                }
            }
        }
        return best;
    }

    int getMinDigitsNeeded(Factors required) {
        string base = "";
        base.append(required.c7, '7');
        base.append(required.c5, '5');
        base += getBestDigitsFor23(required.c2, required.c3);
        return base.length();
    }

    // Returns "INVALID" if impossible, otherwise the valid suffix (can be "" if len == 0)
    string getSmallestSuffix(Factors required, int len) {
        if (getMinDigitsNeeded(required) > len) return "INVALID";

        int c2 = required.c2;
        int c3 = required.c3;
        int c5 = required.c5;
        int c7 = required.c7;

        string suffix = "";
        suffix.append(c7, '7');
        suffix.append(c5, '5');
        suffix += getBestDigitsFor23(c2, c3);

        while ((int)suffix.length() < len) {
            suffix += '1';
        }

        sort(suffix.begin(), suffix.end());
        return suffix;
    }

public:
    string smallestNumber(string num, long long t) {
        Factors tFactors;
        long long temp_t = t;

        while (temp_t % 2 == 0) { tFactors.c2++; temp_t /= 2; }
        while (temp_t % 3 == 0) { tFactors.c3++; temp_t /= 3; }
        while (temp_t % 5 == 0) { tFactors.c5++; temp_t /= 5; }
        while (temp_t % 7 == 0) { tFactors.c7++; temp_t /= 7; }

        if (temp_t > 1) return "-1";

        int n = num.length();

        // 1. Check if num itself works
        bool hasZero = false;
        Factors currentPrefixFactors;
        for (char c : num) {
            if (c == '0') {
                hasZero = true;
                break;
            }
            Factors df = getDigitFactors(c - '0');
            currentPrefixFactors.c2 += df.c2;
            currentPrefixFactors.c3 += df.c3;
            currentPrefixFactors.c5 += df.c5;
            currentPrefixFactors.c7 += df.c7;
        }

        if (!hasZero &&
            currentPrefixFactors.c2 >= tFactors.c2 &&
            currentPrefixFactors.c3 >= tFactors.c3 &&
            currentPrefixFactors.c5 >= tFactors.c5 &&
            currentPrefixFactors.c7 >= tFactors.c7) {
            return num;
        }

        // 2. Precalculate prefix factor counts up to the first '0'
        vector<Factors> prefixFactors(n + 1);
        int firstZeroPos = n;
        for (int i = 0; i < n; i++) {
            if (num[i] == '0') {
                firstZeroPos = i;
                break;
            }
            Factors df = getDigitFactors(num[i] - '0');
            prefixFactors[i + 1].c2 = prefixFactors[i].c2 + df.c2;
            prefixFactors[i + 1].c3 = prefixFactors[i].c3 + df.c3;
            prefixFactors[i + 1].c5 = prefixFactors[i].c5 + df.c5;
            prefixFactors[i + 1].c7 = prefixFactors[i].c7 + df.c7;
        }

        // 3. Try prefix matching
        for (int i = min(n - 1, firstZeroPos); i >= 0; i--) {
            int startDigit = (num[i] - '0') + 1;

            for (int d = startDigit; d <= 9; d++) {
                Factors df = getDigitFactors(d);

                Factors req;
                req.c2 = max(0, tFactors.c2 - (prefixFactors[i].c2 + df.c2));
                req.c3 = max(0, tFactors.c3 - (prefixFactors[i].c3 + df.c3));
                req.c5 = max(0, tFactors.c5 - (prefixFactors[i].c5 + df.c5));
                req.c7 = max(0, tFactors.c7 - (prefixFactors[i].c7 + df.c7));

                int suffixLen = n - 1 - i;
                string suffix = getSmallestSuffix(req, suffixLen);

                if (suffix != "INVALID") {
                    string result = num.substr(0, i);
                    result += to_string(d);
                    result += suffix;
                    return result;
                }
            }
        }

        // 4. Extend length if length 'n' was insufficient
        int minLen = max(n + 1, getMinDigitsNeeded(tFactors));
        string suffix = getSmallestSuffix(tFactors, minLen);
        return suffix != "INVALID" ? suffix : "-1";
    }
};