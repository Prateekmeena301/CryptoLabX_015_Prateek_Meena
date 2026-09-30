#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// Function to generate 5x5 key matrix
vector<vector<char>> generate_key_matrix(string keyword) {
    vector<vector<char>> matrix(5, vector<char>(5));
    bool used[26] = {false};

    // Treat I and J as same
    used['J' - 'A'] = true;

    string key = "";

    // Add keyword characters
    for (char ch : keyword) {
        ch = toupper(ch);
        if (ch == 'J') ch = 'I';

        if (ch >= 'A' && ch <= 'Z' && !used[ch - 'A']) {
            used[ch - 'A'] = true;
            key += ch;
        }
    }

    // Add remaining alphabet letters
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            used[ch - 'A'] = true;
            key += ch;
        }
    }

    // Fill matrix
    int k = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = key[k++];
        }
    }

    return matrix;
}

// Display matrix
void print_matrix(vector<vector<char>> &matrix) {
    cout << "Key Matrix:\n";
    for (auto row : matrix) {
        for (char ch : row)
            cout << ch << " ";
        cout << endl;
    }
}

// Prepare plaintext
string prepare_plaintext(string text) {
    string clean = "";

    // Remove spaces and special characters
    for (char ch : text) {
        if (isalpha(ch)) {
            ch = toupper(ch);
            if (ch == 'J') ch = 'I';
            clean += ch;
        }
    }

    string prepared = "";

    for (int i = 0; i < clean.length(); i++) {
        prepared += clean[i];

        if (i + 1 < clean.length()) {
            if (clean[i] == clean[i + 1]) {
                prepared += 'X';
            }
        }
    }

    // Ensure even length
    if (prepared.length() % 2 != 0)
        prepared += 'X';

    return prepared;
}

// Create digraphs
vector<string> create_digraphs(string text) {
    vector<string> digraphs;

    for (int i = 0; i < text.length(); i += 2) {
        string pair = "";
        pair += text[i];
        pair += text[i + 1];
        digraphs.push_back(pair);
    }

    return digraphs;
}

// Find position of character
pair<int, int> find_position(vector<vector<char>> &matrix, char ch) {
    if (ch == 'J') ch = 'I';

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == ch)
                return {i, j};
        }
    }
    return {-1, -1};
}

// Encryption
string playfair_encrypt(vector<vector<char>> &matrix,
                        vector<string> digraphs) {
    string cipher = "";

    for (string pair : digraphs) {
        char a = pair[0];
        char b = pair[1];

        auto p1 = find_position(matrix, a);
        auto p2 = find_position(matrix, b);

        int r1 = p1.first, c1 = p1.second;
        int r2 = p2.first, c2 = p2.second;

        // Same row
        if (r1 == r2) {
            cipher += matrix[r1][(c1 + 1) % 5];
            cipher += matrix[r2][(c2 + 1) % 5];
        }
        // Same column
        else if (c1 == c2) {
            cipher += matrix[(r1 + 1) % 5][c1];
            cipher += matrix[(r2 + 1) % 5][c2];
        }
        // Rectangle rule
        else {
            cipher += matrix[r1][c2];
            cipher += matrix[r2][c1];
        }
    }

    return cipher;
}

// Decryption
string playfair_decrypt(vector<vector<char>> &matrix, string cipher) {
    string plain = "";

    for (int i = 0; i < cipher.length(); i += 2) {
        char a = cipher[i];
        char b = cipher[i + 1];

        auto p1 = find_position(matrix, a);
        auto p2 = find_position(matrix, b);

        int r1 = p1.first, c1 = p1.second;
        int r2 = p2.first, c2 = p2.second;

        // Same row
        if (r1 == r2) {
            plain += matrix[r1][(c1 + 4) % 5];
            plain += matrix[r2][(c2 + 4) % 5];
        }
        // Same column
        else if (c1 == c2) {
            plain += matrix[(r1 + 4) % 5][c1];
            plain += matrix[(r2 + 4) % 5][c2];
        }
        // Rectangle rule
        else {
            plain += matrix[r1][c2];
            plain += matrix[r2][c1];
        }
    }

    return plain;
}

// Digraph frequency analysis
void digraph_frequency(string cipher) {
    map<string, int> freq;

    for (int i = 0; i < cipher.length(); i += 2) {
        string pair = "";
        pair += cipher[i];
        pair += cipher[i + 1];
        freq[pair]++;
    }

    cout << "\nDigraph Frequency:\n";
    for (auto x : freq) {
        cout << x.first << " : " << x.second << endl;
    }
}

// Verification
void verify(vector<vector<char>> &matrix,
            string decrypted,
            string originalCipher) {

    vector<string> d = create_digraphs(decrypted);
    string recipher = playfair_encrypt(matrix, d);

    cout << "\nVerification: ";
    if (recipher == originalCipher)
        cout << "SUCCESS\n";
    else
        cout << "FAILED\n";
}

// Main
int main() {
    string keyword = "MONARCHY";
    string plaintext = "INSTRUMENTS";

    auto matrix = generate_key_matrix(keyword);

    print_matrix(matrix);

    string prepared = prepare_plaintext(plaintext);

    vector<string> digraphs = create_digraphs(prepared);

    cout << "\nPrepared Digraphs:\n";
    for (string s : digraphs)
        cout << s << " ";
    cout << endl;

    string cipher = playfair_encrypt(matrix, digraphs);

    cout << "\nCiphertext:\n" << cipher << endl;

    string decrypted = playfair_decrypt(matrix, cipher);

    cout << "\nDecrypted Text:\n" << decrypted << endl;

    digraph_frequency(cipher);

    verify(matrix, decrypted, cipher);

    return 0;
}
