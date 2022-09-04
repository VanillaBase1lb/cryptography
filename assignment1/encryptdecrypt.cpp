#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#define LOG(x) std::cout << "logging: " << x << std::endl;

template <typename T> class Cipher {
public:
  virtual std::string encrypt(std::string, T) = 0;
  virtual std::string decrypt(std::string, T) = 0;
};

template <typename T, class O>
std::string encrypt_decrypt(std::string input, T key, O obj) {
  char option;
  std::cout << "Enter whether to encrypt(e) or decrypt(d): " << std::endl;
  std::cin >> option;
  switch (option) {
  case 'e':
    return obj->encrypt(input, key);
  case 'd':
    return obj->decrypt(input, key);
  default:
    std::cout << "Invalid input" << std::endl;
    return "ERROR";
    break;
  }
}

class Caesar : public Cipher<int> {
public:
  std::string encrypt(std::string input, int key) {
    for (int i = 0; i < input.size(); ++i) {
      char c = input[i];
      bool uppercase = std::isupper(c);
      c = tolower(c);
      key = key % 26;
      if (c + key > 'z') {
        c = c + key - 'z' + 'a' - 1;
      } else {
        c = c + key;
      }
      input[i] = (uppercase) ? toupper(c) : c;
    }
    return input;
  }

  std::string decrypt(std::string input, int key) {
    for (int i = 0; i < input.size(); ++i) {
      char c = input[i];
      bool uppercase = std::isupper(c);
      c = tolower(c);
      key = key % 26;
      if (c - key < 'a') {
        c = 'z' - ('a' - (c - key)) + 1;
      } else {
        c = c - key;
      }
      input[i] = (uppercase) ? toupper(c) : c;
    }
    return input;
  }
};

class Vigenere : public Cipher<std::string> {
public:
  std::string encrypt(std::string input, std::string key) {
    int keySize = std::ceil((float)input.size() / (float)key.size());
    std::string keyStr;
    for (int i = 0; i < keySize; i++) {
      keyStr.append(key);
    }
    for (int i = 0; i < input.size(); ++i) {
      char c = input[i];
      char k = tolower(keyStr[i]);
      bool uppercase1 = std::isupper(c);
      c = tolower(c);
      k = tolower(k);
      c = (c + k - 2 * 'a') % 26 + 'a';
      input[i] = (uppercase1) ? toupper(c) : c;
    }
    return input;
  }

  std::string decrypt(std::string input, std::string key) {
    int keySize = std::ceil((float)input.size() / (float)key.size());
    std::string keyStr;
    for (int i = 0; i < keySize; i++) {
      keyStr.append(key);
    }
    for (int i = 0; i < input.size(); ++i) {
      char c = input[i];
      char k = tolower(keyStr[i]);
      bool uppercase1 = std::isupper(c);
      c = tolower(c);
      c = (c - k >= 0) ? (c - k) + 'a' : 'z' + (c - k) + 1;
      input[i] = (uppercase1) ? toupper(c) : c;
    }
    return input;
  }
};

int getCipher() {
  int cipher;
  std::cout << "Enter the cipher of your choice: " << std::endl;
  std::cout << "Caesar(1), Vigenere(2), Playfair(3): ";
  std::cin >> cipher;

  return cipher;
}

std::string getKey(int cipher, std::string input) {
  int key;
  std::string keyStr;
  switch (cipher) {
  case 1:
    std::cout << "Enter Caesar cipher key(0-9999)" << std::endl;
    std::cin >> key;
    return encrypt_decrypt(input, key, new Caesar());
    break;
  case 2:
    std::cout << "Enter Vigenere cipher key(string)" << std::endl;
    std::cin >> keyStr;
    return encrypt_decrypt(input, keyStr, new Vigenere());
    break;
  default:
    std::cout << "Invalid input" << std::endl;
    break;
  }
  return "ERROR";
}

std::string getText() {
  std::ifstream fin;
  fin.open("process.txt");
  std::string input;
  fin >> input;
  return input;
}

int main(int argc, char *argv[]) {
  int cipher = getCipher();
  std::string input = getText();
  std::string answer = getKey(cipher, input);
  std::cout << answer << std::endl;

  return 0;
}
