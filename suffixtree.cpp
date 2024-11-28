Question 8. Write a program to implement a Suffix tree.


#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <limits>

using namespace std;

class SuffixTreeNode {
public:
    unordered_map<char, shared_ptr<SuffixTreeNode>> children;
    shared_ptr<SuffixTreeNode> suffixLink;
    int start;
    int* end;
    int suffixIndex;

    SuffixTreeNode(int start = -1, int* end = nullptr) : 
        start(start), 
        end(end), 
        suffixIndex(-1) {}
};

class SuffixTree {
private:
    string text;
    shared_ptr<SuffixTreeNode> root;
    shared_ptr<SuffixTreeNode> lastNewNode;
    shared_ptr<SuffixTreeNode> activeNode;
    int activeEdge;
    int activeLength;
    int remainingSuffixCount;
    int leafEnd;
    int* rootEnd;
    int size;

    bool walkDown(shared_ptr<SuffixTreeNode>& currentNode) {
        int edgeLength = getEdgeLength(currentNode);
        
        if (activeLength >= edgeLength) {
            activeEdge += edgeLength;
            activeLength -= edgeLength;
            activeNode = currentNode;
            return true;
        }
        return false;
    }

    int getEdgeLength(shared_ptr<SuffixTreeNode>& node) {
        if (node == root)
            return 0;
        return *(node->end) - node->start + 1;
    }

    void extendSuffixTree(int phase) {
        leafEnd = phase;
        remainingSuffixCount++;
        lastNewNode = nullptr;

        while (remainingSuffixCount > 0) {
            if (activeLength == 0)
                activeEdge = phase;

            auto currentChild = activeNode->children.find(text[activeEdge]);
            
            if (currentChild == activeNode->children.end()) {
                activeNode->children[text[activeEdge]] = 
                    make_shared<SuffixTreeNode>(phase, &leafEnd);
                
                if (lastNewNode != nullptr) {
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = nullptr;
                }
            }
            else {
                shared_ptr<SuffixTreeNode> next = currentChild->second;
                
                if (walkDown(next))
                    continue;

                if (text[next->start + activeLength] == text[phase]) {
                    if (lastNewNode != nullptr) {
                        lastNewNode->suffixLink = activeNode;
                        lastNewNode = nullptr;
                    }

                    activeLength++;
                    break;
                }

                int splitEnd = next->start + activeLength - 1;
                auto splitNode = make_shared<SuffixTreeNode>(next->start, &splitEnd);
                
                activeNode->children[text[activeEdge]] = splitNode;
                
                splitNode->children[text[phase]] = 
                    make_shared<SuffixTreeNode>(phase, &leafEnd);
                
                next->start += activeLength;
                splitNode->children[text[next->start]] = next;

                if (lastNewNode != nullptr) {
                    lastNewNode->suffixLink = splitNode;
                }
                lastNewNode = splitNode;
            }

            remainingSuffixCount--;

            if (activeNode == root && activeLength > 0) {
                activeEdge = phase - remainingSuffixCount + 1;
                activeLength--;
            }
            else if (activeNode != root) {
                activeNode = activeNode->suffixLink ? activeNode->suffixLink : root;
            }
        }
    }

    void printTree(shared_ptr<SuffixTreeNode> node, int depth = 0) {
        for (auto& child : node->children) {
            for (int i = 0; i < depth; i++)
                cout << "  ";

            int start = child.second->start;
            int end = *(child.second->end);
            cout << text.substr(start, end - start + 1) << endl;

            printTree(child.second, depth + 1);
        }
    }

public:
    SuffixTree() {
        root = make_shared<SuffixTreeNode>();
        rootEnd = new int(-1);
        root->end = rootEnd;
        activeNode = root;
        size = 0;
    }

    void buildSuffixTree(const string& input) {
        root = make_shared<SuffixTreeNode>();
        root->end = rootEnd;
        activeNode = root;
        activeEdge = -1;
        activeLength = 0;
        remainingSuffixCount = 0;
        leafEnd = -1;

        text = input + "$";
        size = text.length();

        for (int i = 0; i < size; i++) {
            extendSuffixTree(i);
        }
    }

    void searchPattern(const string& pattern) {
        if (text.empty()) {
            cout << "Suffix tree not built. Build tree first." << endl;
            return;
        }

        shared_ptr<SuffixTreeNode> currentNode = root;
        int patternIndex = 0;

        while (patternIndex < pattern.length()) {
            auto child = currentNode->children.find(pattern[patternIndex]);

            if (child == currentNode->children.end()) {
                cout << "Pattern not found in the text." << endl;
                return;
            }

            shared_ptr<SuffixTreeNode> nextNode = child->second;
            int edgeStart = nextNode->start;
            int edgeEnd = *(nextNode->end);
            int j = edgeStart;

            while (j <= edgeEnd && patternIndex < pattern.length() 
                   && text[j] == pattern[patternIndex]) {
                j++;
                patternIndex++;
            }

            if (patternIndex == pattern.length()) {
                cout << "Pattern found in the text." << endl;
                return;
            }

            if (j <= edgeEnd || patternIndex >= pattern.length()) {
                cout << "Pattern not found in the text." << endl;
                return;
            }

            currentNode = nextNode;
        }
    }

    void displayTree() {
        if (text.empty()) {
            cout << "Suffix tree not built. Build tree first." << endl;
            return;
        }
        cout << "Suffix Tree Structure:" << endl;
        printTree(root);
    }

    ~SuffixTree() {
        delete rootEnd;
    }
};

int main() {
    SuffixTree suffixTree;
    int choice;
    string input, pattern;

    while (true) {
        cout << "\n--- Suffix Tree Operations ---" << endl;
        cout << "1. Build Suffix Tree" << endl;
        cout << "2. Search Pattern" << endl;
        cout << "3. Display Suffix Tree" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                cout << "Enter the text to build suffix tree: ";
                getline(cin, input);
                suffixTree.buildSuffixTree(input);
                cout << "Suffix tree built successfully!" << endl;
                break;

            case 2:
                cout << "Enter pattern to search: ";
                getline(cin, pattern);
                suffixTree.searchPattern(pattern);
                break;

            case 3:
                suffixTree.displayTree();
                break;

            case 4:
                cout << "Exiting program..." << endl;
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
