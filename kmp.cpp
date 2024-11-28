Question 7. Write a program to search a pattern in a given text using the KMP algorithm.



#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class KMPSearch {
public:
    // Compute the longest proper prefix which is also a suffix array
    static vector<int> computeLPSArray(const string& pattern) {
        int m = pattern.length();
        vector<int> lps(m, 0);
        
        int len = 0;  // Length of the previous longest prefix suffix
        int i = 1;
        
        while (i < m) {
            if (pattern[i] == pattern[len]) {
                len++;
                lps[i] = len;
                i++;
            }
            else {
                // If characters don't match
                if (len != 0) {
                    len = lps[len - 1];
                }
                else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        return lps;
    }
    
    // KMP search algorithm
    static vector<int> search(const string& text, const string& pattern) {
        vector<int> result;
        
        // Compute the longest prefix suffix (LPS) array
        vector<int> lps = computeLPSArray(pattern);
        
        int n = text.length();
        int m = pattern.length();
        
        int i = 0;  // Index for text
        int j = 0;  // Index for pattern
        
        while (i < n) {
            // If characters match, increment both indices
            if (pattern[j] == text[i]) {
                j++;
                i++;
            }
            
            // If pattern is completely matched, store the starting index
            if (j == m) {
                result.push_back(i - j);
                j = lps[j - 1];
            }
            // Mismatch after some matches
            else if (i < n && pattern[j] != text[i]) {
                // Do not match lps[0..lps[j-1]] characters
                if (j != 0) {
                    j = lps[j - 1];
                }
                else {
                    i++;
                }
            }
        }
        
        return result;
    }
};

int main() {
    string text, pattern;
    char choice;

    do {
        // Clear input buffers
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Get text from user
        cout << "Enter the text to search in: ";
        getline(cin, text);

        // Get pattern from user
        cout << "Enter the pattern to search for: ";
        getline(cin, pattern);

        // Perform KMP search
        vector<int> occurrences = KMPSearch::search(text, pattern);
        
        // Print results
        cout << "\nSearch Results:" <<endl;
        cout << "Text: " << text <<endl;
        cout << "Pattern: " << pattern <<endl;
        
        if (occurrences.empty()) {
            cout << "Pattern not found in the text." << endl;
        }
        else {
            cout << "Pattern found at following starting indices:" <<endl;
            for (int index : occurrences) {
                cout << index << " ";
            }
            cout << endl;
        }

        // Ask if user wants to continue
        cout << "\nDo you want to search again? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "Thank you for using KMP Pattern Search!" << endl;
    return 0;
}
