#include "vsarray.h"
#include "character.h"
#include "huffmantree.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::noskipws;
using std::stringstream;

void Usage(char* args[]); // Simple manual
void Encode(VSArray& encode, ifstream& input, ofstream& output, char* args[]);
void CreatFrequencies(VSArray& array, ifstream& input); // Function that creates the frequency table
void CreateEncodings(VSArray& encoding, const HuffTree& huff); // Function that creates the encoding table
void InsertionSort(VSArray& array);	// Insertion sort function
void InorderTraversal(Node* currNode, const string& code, VSArray& encoding);
string CharToString(char letter); // Char to String converter function

int main(int argc, char* argv[]) {

	VSArray frequencies(30);
	VSArray encodingTable(30);
	HuffTree huffmanTree;

	if (argc < 2) {
		Usage(argv);
		return 0;
	}

	ifstream inputFile(argv[2]);

	if (argc > 4) {
		cout << "Too many arguments" << endl;
		return 0;
	}

	if (strcmp("-encode", argv[1]) == 0) {
		if (argc < 4) {
			Usage(argv);
			return 0;
		}

        CreatFrequencies(frequencies, inputFile);

        for (size_t k = 0; k < frequencies.Size(); ++k) {
            encodingTable.Insert(frequencies.Get(k)->Clone(), encodingTable.Size());
        }

        huffmanTree.CreateTree(frequencies);

        CreateEncodings(encodingTable, huffmanTree);

		ofstream outputFile(argv[3]);

		//inputFile.close();

		//ifstream input(argv[2]);

        inputFile.clear();
        inputFile.seekg(0);

		Encode(encodingTable, inputFile, outputFile, argv);

		return 0;
	}
	else if (strcmp("-single", argv[1]) == 0) {

		if (argc < 4) {
			Usage(argv);
			return 0;
		}

		CreatFrequencies(frequencies, inputFile);

		for (size_t k = 0; k < frequencies.Size(); ++k) {
			encodingTable.Insert(frequencies.Get(k)->Clone(), encodingTable.Size());
		}

		huffmanTree.CreateTree(frequencies);

		CreateEncodings(encodingTable, huffmanTree);

		string charLook = argv[3];

		size_t m = 0;
		while (encodingTable.Get(m)->ToString() != charLook && m < encodingTable.Size()) {
			++m;
		}

		cout << encodingTable.Get(m)->GetCode() << endl;

		return 0;
	}
	else if (strcmp("-frequency", argv[1]) == 0) {
		if (argc < 3) {
			Usage(argv);
			return 0;
		}

		CreatFrequencies(frequencies, inputFile);

		for (size_t i = 0; i < frequencies.Size(); ++i) {
			cout << frequencies.Get(i)->ToJSON() << endl;
		}

        inputFile.close();

		return 0;
	}
	else if (strcmp("-encoding-table", argv[1]) == 0) {
		if (argc < 3) {
			Usage(argv);
			return 0;
		}

		CreatFrequencies(frequencies, inputFile);

		for (size_t k = 0; k < frequencies.Size(); ++k) {
			encodingTable.Insert(frequencies.Get(k)->Clone(), encodingTable.Size());
		}

		huffmanTree.CreateTree(frequencies);

        CreateEncodings(encodingTable, huffmanTree);

		for (size_t i = 0; i < encodingTable.Size(); ++i) {
			cout << encodingTable.Get(i)->ToEncodeTable() << endl;
		}

		return 0;
	}
	else if (strcmp("-decode", argv[1]) == 0) {
		cout << "FIX ME DECODING" << endl;
		return 0;
	}
	else {
		Usage(argv);
		return 0;
	}

}

void Usage(char* args[]) {
	cout << "Usage: "<< args[0] << " [options] filename" << endl
	     << endl
	     << "Options:" << endl
	     << "-encode inputfile outputfile\t\t" << "encode a file with huffman encoding" << endl
	     << "-single inputfile c\t\t\t" << "encode the inputfile and prints a string of 1s and 0s for c, the desired character" << endl
	     << "-frequency inputfile\t\t\t" << "encodes the inputfile and prints the frequency table" << endl
	     << "-encoding-table inputfile\t\t" << "encodes the inputfile and prints the encoding table" << endl
	     << "-decode inputfile outputfile\t\t" << "decodes the inputfile and writes to the outputfile" << endl
	     << endl;
}

void Encode(VSArray& encode, ifstream& input, ofstream& output, char* args[]) {
	char currLetter;
	string letter;
	size_t j;
	int bytesWritten = 0;
    string code;
    size_t bitCount = 0;
    unsigned char bitBuffer = 0;

	while (input >> noskipws >> currLetter) {
		//input >> noskipws >> currLetter;
		letter = CharToString(currLetter);
        j = 0;
		while (j < encode.Size() - 1 && letter != encode.Get(j)->GetValue()) {
			++j;
		}
        code = encode.Get(j)->GetCode();

        for (size_t i = 0; i < code.size(); i++) {
            if (code.at(i) == '1')
                bitBuffer |= (1 << bitCount);
            else
                bitBuffer |= (0 << bitCount);
            bitCount++;
            if (bitCount == 8) {
                bitCount = 0;
                output << bitBuffer;
                bitBuffer = 0;
                bytesWritten++;
            }
        }

		//output << code;

	}

	cout << bytesWritten << " bytes written." << endl;
}

void CreatFrequencies(VSArray& array, ifstream& input) {
	char currLetter;
	Character* currChar;
	int where;

	while (input >> noskipws >> currLetter) {
		//input >> noskipws >> currLetter;
		currChar = new Character(CharToString(currLetter));
		where = array.IndexOf(currChar);
		if (where == -1) {
			array.Insert(currChar, array.Size());
		}
		else {
            delete currChar;
			auto addChar = dynamic_cast<Character*>(array.Get(where));
			addChar->SetCount(addChar->GetCount() + 1);
		}
	}

	InsertionSort(array);

}

void InorderTraversal(Node* currNode, const string& code, VSArray& encoding) {

	int j = 0;

	if (currNode != nullptr && currNode->GetLNode() == nullptr && currNode->GetRNode() == nullptr) {
		while (currNode->GetLetter() != encoding.Get(j)->ToString()) {
			++j;
		}
		encoding.Get(j)->SetCode(code);
	}
	else if (currNode != nullptr){
        InorderTraversal(currNode->GetRNode(), code + "0", encoding);
		InorderTraversal(currNode->GetLNode(), code + "1", encoding);
	}
}
void CreateEncodings(VSArray& encodings, const HuffTree& huff) {
    string code;

    InorderTraversal(huff.GetRoot(), code, encodings);
}

void InsertionSort(VSArray& array) {
	Character* temp;
	size_t j;

	for (size_t i = 1; i < array.Size(); ++i) {
		j = i;
		while (array.Get(j)->GreaterThan(*array.Get(j - 1)) && j > 0) {
			temp = array.Get(j - 1);
			array.Remove(j - 1);
			array.Insert(temp, j);
			--j;
		}
	}

}

string CharToString(char letter) {
	stringstream retVal;
	if (letter == '\n') {
		return "CR";
	}
	if (letter == '\r') {
		return "LF";
	}
	retVal << letter;
	return retVal.str();
}
