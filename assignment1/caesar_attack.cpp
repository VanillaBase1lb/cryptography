#include "attack_common.cpp"
#include <chrono>

int main(int argc, char *argv[]) {
  std::string cipher_text = readCipherFromFile();
  // start timer
  auto start = std::chrono::high_resolution_clock::now();
  int key = crackCaesar(cipher_text).first;
  std::string deciphered_text = crackCaesar(cipher_text).second;
  // end timer
  auto finish = std::chrono::high_resolution_clock::now();
  // print time
  std::chrono::duration<double> elapsed = finish - start;
  std::cout << "Elapsed time: " << elapsed.count() << std::endl;

  std::cout << "Key: " << key << std::endl;
  std::cout << "Deciphered text: " << deciphered_text << std::endl;

  return 0;
}

