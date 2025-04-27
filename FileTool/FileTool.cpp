#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
using namespace std;

// Base64 encoding table
const string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Function to encode data to Base64
string base64Encode(const string& input) {
    string encoded = "";
    int i = 0;
    unsigned char char_array_3[3], char_array_4[4];
    int len = input.length();

    while (len--) {
        char_array_3[i++] = input[input.length() - len - 1];
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) | ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) | ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            for (int j = 0; (j < 4); j++)
                encoded += base64_chars[char_array_4[j]];
            i = 0;
        }
    }

    if (i)
    {
        for (int j = i; j < 3; j++)
            char_array_3[j] = '\0';
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) | ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) | ((char_array_3[2] & 0xc0) >> 6);
        for (int j = 0; (j < i + 1); j++)
            encoded += base64_chars[char_array_4[j]];
        while ((i++ < 3))
            encoded += "=";
    }

    return encoded;
}

// Function to decode Base64 string to original data
string base64Decode(const string& input) {
    int len = input.size();
    int i = 0, j = 0;
    unsigned char char_array_4[4], char_array_3[3];
    string decoded = "";
    while (len-- && (input[j] != '=') && isalnum(input[j])) {
        char_array_4[i++] = input[j++];
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);
            char_array_3[0] = (char_array_4[0] << 2) | (char_array_4[1] >> 4);
            char_array_3[1] = ((char_array_4[1] & 0x0f) << 4) | (char_array_4[2] >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x03) << 6) | char_array_4[3];
            for (i = 0; (i < 3); i++)
                decoded += char_array_3[i];
            i = 0;
        }
    }
    return decoded;
}

// Function to compress a file using RLE and Base64 encoding
void compressFileWithEncoding(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName, ios::in);
    ofstream outputFile(outputFileName, ios::out);
    
    if (!inputFile) {
        cout << "Error opening input file!" << endl;
        return;
    }
    if (!outputFile) {
        cout << "Error opening output file!" << endl;
        return;
    }

    char currentChar, nextChar;
    int count;
    string rawContent = "";

    // Read the entire input file into a string
    while (inputFile.get(currentChar)) {
        rawContent += currentChar;
    }

    // Apply RLE to the string
    string rleCompressed = "";
    for (int i = 0; i < rawContent.size(); i++) {
        currentChar = rawContent[i];
        count = 1;
        while (i < rawContent.size() - 1 && rawContent[i] == rawContent[i + 1]) {
            count++;
            i++;
        }
        rleCompressed += to_string(count) + currentChar;
    }

    // Base64 encode the RLE compressed string
    string encodedData = base64Encode(rleCompressed);

    // Write the encoded data to the output file
    outputFile << encodedData;

    inputFile.close();
    outputFile.close();
    cout << "File compression with encoding completed!" << endl;
}

// Function to decompress a file with Base64 decoding and RLE decompression
void decompressFileWithEncoding(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName, ios::in);
    ofstream outputFile(outputFileName, ios::out);
    
    if (!inputFile) {
        cout << "Error opening input file!" << endl;
        return;
    }
    if (!outputFile) {
        cout << "Error opening output file!" << endl;
        return;
    }

    string encodedData = "";
    char currentChar;

    // Read the encoded file
    while (inputFile.get(currentChar)) {
        encodedData += currentChar;
    }

    // Base64 decode the data
    string rleCompressed = base64Decode(encodedData);

    // Perform RLE decompression
    string decompressedData = "";
    for (int i = 0; i < rleCompressed.size(); i++) {
        int count = rleCompressed[i] - '0'; // Get the count (assumes single digit)
        char c = rleCompressed[i + 1];     // Get the character
        for (int j = 0; j < count; j++) {
            decompressedData += c;
        }
        i++; // Skip the character in the next iteration
    }

    // Write the decompressed data to the output file
    outputFile << decompressedData;

    inputFile.close();
    outputFile.close();
    cout << "File decompression with decoding completed!" << endl;
}

int main() {
    int choice;
    string inputFileName, outputFileName;

    cout << "File Compression Tool using RLE and Base64 Encoding" << endl;
    cout << "1. Compress File with Encoding" << endl;
    cout << "2. Decompress File with Decoding" << endl;
    cout << "Enter your choice (1/2): ";
    cin >> choice;
    
    cout << "Enter the input file name: ";
    cin >> inputFileName;
    cout << "Enter the output file name: ";
    cin >> outputFileName;

    if (choice == 1) {
        compressFileWithEncoding(inputFileName, outputFileName);
    } else if (choice == 2) {
        decompressFileWithEncoding(inputFileName, outputFileName);
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
