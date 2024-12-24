#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

class HuffmanNode {
public:
    char Character;
    int Frequency;
    HuffmanNode* LeftChild;
    HuffmanNode* RightChild;

    HuffmanNode(char Character, int Frequency) {
        this->Character = Character;
        this->Frequency = Frequency;
        LeftChild = RightChild = nullptr;
    }
};

unordered_map<char, int> CreateFrequencyTable(const string& InputString) {
    unordered_map<char, int> FrequencyTable;
    for (char Ch : InputString) {
        FrequencyTable[Ch]++;
    }
    return FrequencyTable;
}

HuffmanNode* BuildHuffmanTree(const unordered_map<char, int>& FrequencyTable) {
    vector<HuffmanNode*> NodeList;

    for (auto Entry : FrequencyTable) {
        NodeList.push_back(new HuffmanNode(Entry.first, Entry.second));
    }

    while (NodeList.size() > 1) {
        sort(NodeList.begin(), NodeList.end(), [](HuffmanNode* A, HuffmanNode* B) {
            return A->Frequency < B->Frequency;
            });

        HuffmanNode* LeftNode = NodeList[0];
        HuffmanNode* RightNode = NodeList[1];

        NodeList.erase(NodeList.begin());
        NodeList.erase(NodeList.begin());

        HuffmanNode* CombinedNode = new HuffmanNode('\0', LeftNode->Frequency + RightNode->Frequency);
        CombinedNode->LeftChild = LeftNode;
        CombinedNode->RightChild = RightNode;

        NodeList.push_back(CombinedNode);
    }

    return NodeList[0];
}

void GenerateCodes(HuffmanNode* RootNode, const string& CurrentCode, unordered_map<char, string>& HuffmanCodes) {
    if (!RootNode) return;

    if (!RootNode->LeftChild && !RootNode->RightChild) {
        HuffmanCodes[RootNode->Character] = CurrentCode;
    }

    GenerateCodes(RootNode->LeftChild, CurrentCode + "0", HuffmanCodes);
    GenerateCodes(RootNode->RightChild, CurrentCode + "1", HuffmanCodes);
}

string EncodeInput(const string& InputString, const unordered_map<char, string>& HuffmanCodes) {
    string EncodedString = "";
    for (char Ch : InputString) {
        EncodedString += HuffmanCodes.at(Ch);
    }
    return EncodedString;
}

string DecodeInput(const string& EncodedString, HuffmanNode* RootNode) {
    string DecodedString = "";
    HuffmanNode* CurrentNode = RootNode;

    for (char Bit : EncodedString) {
        if (Bit == '0') {
            CurrentNode = CurrentNode->LeftChild;
        }
        else {
            CurrentNode = CurrentNode->RightChild;
        }

        if (!CurrentNode->LeftChild && !CurrentNode->RightChild) {
            DecodedString += CurrentNode->Character;
            CurrentNode = RootNode;
        }
    }

    return DecodedString;
}

int main() {
    string UserInput;
    cout << "==========================================\n";
    cout << "           HUFFMAN CODING PROGRAM         \n";
    cout << "==========================================\n";
    cout << "\nEnter The String To Encode: \n>>> ";
    getline(cin, UserInput);

    unordered_map<char, int> FrequencyTable = CreateFrequencyTable(UserInput);

    cout << "\n==========================================\n";
    cout << "               FREQUENCY TABLE            \n";
    cout << "==========================================\n";
    for (auto Entry : FrequencyTable) {
        cout << Entry.first << ": " << Entry.second << endl;
    }

    HuffmanNode* HuffmanRoot = BuildHuffmanTree(FrequencyTable);

    unordered_map<char, string> HuffmanCodes;
    GenerateCodes(HuffmanRoot, "", HuffmanCodes);

    cout << "\n==========================================\n";
    cout << "                HUFFMAN CODES             \n";
    cout << "==========================================\n";
    for (auto Entry : HuffmanCodes) {
        cout << Entry.first << ": " << Entry.second << endl;
    }

    string EncodedString = EncodeInput(UserInput, HuffmanCodes);

    cout << "==========================================\n";
    cout << "\nOriginal String: " << UserInput << endl;
    cout << "==========================================\n";
    cout << "Encoded String: " << EncodedString << endl;
    cout << "==========================================\n";

    string DecodedString = DecodeInput(EncodedString, HuffmanRoot);
    cout << "Decoded String: " << DecodedString << endl;
    cout << "==========================================\n";

    
    int OriginalSize = UserInput.length() * 8; // 1 Char = 8 Bits
    int CompressedSize = EncodedString.length();

    cout << "==========================================\n";
    cout << "\nCompression Analysis:\n";
    cout << "==========================================\n";
    cout << "Original Size: " << OriginalSize << " Bits\n";
    cout << "Compressed Size: " << CompressedSize << " Bits\n";

    if (DecodedString == UserInput) {
        cout << "\nThe Decoded String Matches The Original String.\n";
    }
    else {
        cout << "\nError: Decoded String Does Not Match The Original String.\n";
    }

    return 0;
}
