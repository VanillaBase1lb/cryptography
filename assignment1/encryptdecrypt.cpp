#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

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
    throw "Invalid input";
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

class Playfair : public Cipher<std::string> {
  char keySquare[5][5];
  std::string diagraphized_input;
  struct xy {
    int x;
    int y;
  };
  std::unordered_map<char, xy> char_coordinates;

  std::string diagraphize(std::string input, char bogus) {
    for (int i = 0; i < input.size(); i = i + 2) {
      if (input[i] == 'j') {
        input[i] = 'i';
      }
      if (i - 1 >= 0 && input[i - 1] == input[i]) {
        input.insert(i, 1, bogus);
        i++;
      }
      if (i + 1 >= input.size()) {
        input.append(1, bogus);
        break;
      }
      if (input[i + 1] == 'j') {
        input[i] = 'i';
      }
      if (input[i + 1] == input[i]) {
        input.insert(i + 1, 1, bogus);
        i = i + 2;
      }
    }
    return input;
  }

public:
  Playfair(std::string key, std::string input, char bogus) {
    // generate key square
    char a = 'a';
    int counter = 0;
    int i = 0, j = 0;
    this->char_coordinates['j'] = {5, 5}; // invalid coordinates

    for (i = 0; i < 5 && counter < key.size(); i++) {
      for (j = 0; j < 5 && counter < key.size(); j++, counter++) {
        if (this->char_coordinates.count(key[counter]) > 0) {
          j--;
          continue;
        }
        if (counter >= key.size())
          break;
        this->char_coordinates[key[counter]] = {j, i};
        this->keySquare[i][j] = key[counter];
      }
      if (counter >= key.size())
        break;
    }
    counter = 0;
    for (; i < 5; i++) {
      for (; j < 5; j++, counter++) {
        if (this->char_coordinates.count(a + counter) > 0) {
          j--;
          continue;
        }
        this->keySquare[i][j] = a + counter;
        this->char_coordinates[a + counter] = {j, i};
      }
      j = 0;
    }
    this->diagraphized_input = diagraphize(input, bogus);
    LOG(this->diagraphized_input)
    // for (int i = 0; i < 5; i++) {
    //   for (int j = 0; j < 5; j++) {
    //     LOG(this->keySquare[i][j])
    //     LOG(this->char_coordinates[keySquare[i][j]].y)
    //     LOG(this->char_coordinates[keySquare[i][j]].x)
    //   }
    // }
  }

  std::string encrypt(std::string input, std::string key) {
    std::string output = this->diagraphized_input;
    for (int i = 0; i < this->diagraphized_input.size(); i = i + 2) {
      char c1 = output[i];
      char c2 = output[i + 1];
      // if on same column
      if (this->char_coordinates[c1].x == this->char_coordinates[c2].x) {
        output[i] =
            (this->char_coordinates[c1].y + 1 > sizeof(this->keySquare[0]) - 1)
                ? this->keySquare[0][this->char_coordinates[c1].x]
                : this->keySquare[this->char_coordinates[c1].y + 1]
                                 [this->char_coordinates[c1].x];
        output[i + 1] =
            (this->char_coordinates[c2].y + 1 > sizeof(this->keySquare[0]) - 1)
                ? this->keySquare[0][this->char_coordinates[c2].x]
                : this->keySquare[this->char_coordinates[c2].y + 1]
                                 [this->char_coordinates[c2].x];
      }
      // if on same row
      else if (this->char_coordinates[c1].y == this->char_coordinates[c2].y) {
        output[i] =
            (this->char_coordinates[c1].x + 1 > sizeof(this->keySquare[0]) - 1)
                ? this->keySquare[this->char_coordinates[c1].y][0]
                : this->keySquare[this->char_coordinates[c1].y]
                                 [this->char_coordinates[c1].x + 1];
        output[i + 1] =
            (this->char_coordinates[c2].x + 1 > sizeof(this->keySquare[0]) - 1)
                ? this->keySquare[this->char_coordinates[c2].y][0]
                : this->keySquare[this->char_coordinates[c2].y]
                                 [this->char_coordinates[c2].x + 1];
      }
      // else if neither on same row or column
      else {
        output[i] = this->keySquare[this->char_coordinates[c1].y]
                                   [this->char_coordinates[c2].x];
        output[i + 1] = this->keySquare[this->char_coordinates[c2].y]
                                       [this->char_coordinates[c1].x];
      }
    }

    return output;
  }

  std::string decrypt(std::string input, std::string key) {
    std::string output = this->diagraphized_input;
    for (int i = 0; i < this->diagraphized_input.size(); i = i + 2) {
      char c1 = output[i];
      char c2 = output[i + 1];
      // if on same column
      if (this->char_coordinates[c1].x == this->char_coordinates[c2].x) {
        output[i] = (this->char_coordinates[c1].y - 1 < 0)
                        ? this->keySquare[sizeof(this->keySquare[0]) - 1]
                                         [this->char_coordinates[c1].x]
                        : this->keySquare[this->char_coordinates[c1].y - 1]
                                         [this->char_coordinates[c1].x];
        output[i + 1] = (this->char_coordinates[c2].y - 1 < 0)
                            ? this->keySquare[sizeof(this->keySquare[0]) - 1]
                                             [this->char_coordinates[c2].x]
                            : this->keySquare[this->char_coordinates[c2].y - 1]
                                             [this->char_coordinates[c2].x];
      }
      // if on same row
      else if (this->char_coordinates[c1].y == this->char_coordinates[c2].y) {
        output[i] = (this->char_coordinates[c1].x - 1 < 0)
                        ? this->keySquare[this->char_coordinates[c1].y]
                                         [sizeof(this->keySquare[0]) - 1]
                        : this->keySquare[this->char_coordinates[c1].y]
                                         [this->char_coordinates[c1].x - 1];
        output[i + 1] = (this->char_coordinates[c2].x - 1 < 0)
                            ? this->keySquare[this->char_coordinates[c2].y]
                                             [sizeof(this->keySquare[0]) - 1]
                            : this->keySquare[this->char_coordinates[c2].y]
                                             [this->char_coordinates[c2].x - 1];
      }
      // else if neither on same row or column
      else {
        output[i] = this->keySquare[this->char_coordinates[c1].y]
                                   [this->char_coordinates[c2].x];
        output[i + 1] = this->keySquare[this->char_coordinates[c2].y]
                                       [this->char_coordinates[c1].x];
      }
    }

    return output;
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
    std::cout << "Enter Vigenere cipher key(string[a-z,A-Z])" << std::endl;
    std::cin >> keyStr;
    return encrypt_decrypt(input, keyStr, new Vigenere());
    break;
  case 3:
    std::cout << "Enter Playfair cipher key(string[a-z])" << std::endl;
    std::cin >> keyStr;
    // convert input to lowercase
    std::transform(input.begin(), input.end(), input.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return encrypt_decrypt(input, keyStr, new Playfair(keyStr, input, 'x'));
    break;
  default:
    throw "Invalid input";
  }
}

std::string getText() {
  std::ifstream fin;
  fin.open("process.txt");
  if (fin.fail()) {
    throw "Cannot open file 'process.txt'";
  }
  std::string input;
  fin >> input;
  fin.close();
  return input;
}

int main(int argc, char *argv[]) {
  try {
    int cipher = getCipher();
    std::string input = getText();
    std::string answer = getKey(cipher, input);
    std::cout << answer << std::endl;

  } catch (const char *err) {
    std::cout << err << std::endl;
  }

  return 0;
}
