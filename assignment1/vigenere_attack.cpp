#include "attack_common.cpp"

int main(int argc, char *argv[]) {
  std::string cipher_text = readCipherFromFile();
  std::cout << "Key: " << crackVigenere(cipher_text).first << std::endl;
  std::cout << "Deciphered text: " << crackVigenere(cipher_text).second
            << std::endl;

  return 0;
}
