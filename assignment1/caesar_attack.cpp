#include "attack_common.cpp"

int main(int argc, char *argv[]) {
  std::string cipher_text = readCipherFromFile();
  std::cout << "Key: " << crackCaesar(cipher_text).first << std::endl;
  std::cout << "Deciphered text: " << crackCaesar(cipher_text).second
            << std::endl;

  return 0;
}
