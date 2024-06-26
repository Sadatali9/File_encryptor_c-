#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to encrypt the text using Caesar Cipher
string encrypt(const string& text, int shift) {
    string result = text;
    for (char& c : result) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = (c - base + shift) % 26 + base;
        }
    }
    return result;
}

// Function to decrypt the text using Caesar Cipher
string decrypt(const string& text, int shift) {
    return encrypt(text, 26 - shift);  // Decrypting is just encrypting with 26 - shift
}

// Function to read file content
string readFile(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        throw runtime_error("Could not open file.");
    }
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

// Function to write content to file
void writeFile(const string& filePath, const string& content) {
    ofstream file(filePath);
    if (!file.is_open()) {
        throw runtime_error("Could not open file.");
    }
    file << content;
}

void showMenu() {
    cout << "File Encryptor" << endl;
    cout << "1. Encrypt File" << endl;
    cout << "2. Decrypt File" << endl;
    cout << "3. Exit" << endl;
}

int main() {
    int choice;
    string filePath;
    int shift;
    do {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter file path to encrypt: ";
                cin >> filePath;
                cout << "Enter shift value: ";
                cin >> shift;
                try {
                    string content = readFile(filePath);
                    string encryptedContent = encrypt(content, shift);
                    writeFile(filePath, encryptedContent);
                    cout << "File encrypted successfully." << endl;
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
            case 2: {
                cout << "Enter file path to decrypt: ";
                cin >> filePath;
                cout << "Enter shift value: ";
                cin >> shift;
                try {
                    string content = readFile(filePath);
                    string decryptedContent = decrypt(content, shift);
                    writeFile(filePath, decryptedContent);
                    cout << "File decrypted successfully." << endl;
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
            case 3:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
