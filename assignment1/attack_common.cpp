#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

#define LOG(x) std::cout << "logging: " << x << std::endl;

std::string common_words[] = {"the", "be", "to", "of", "and", "that"};

// copied from enctryptdecrypt.cpp(Question 1)
std::string decrypt_caesar(std::string input, int key) {
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

// copied from enctryptdecrypt.cpp(Question 1)
std::string decrypt_vigenere(std::string input, std::string key) {
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

std::string readCipherFromFile(char attack_type) {
  std::ifstream fp("process.txt");
  std::string cipher_text;
  if (fp.fail()) {
    std::cout << "'process.txt' not found, using default cipher text"
              << std::endl;
    switch (attack_type) {
    case 'v':
      cipher_text =
          "XUMGGVZINUHRDENSCMDCRREMCGUQNGXUMYVLBCGJXVBWCWPWMRPRBENCVVDGGVXHGVNJ"
          "LGXUMGGVZINOEPPIPIJISMRBENCWRVIIQNQTTIFMMDPRLAVCCMWTMGMRVLNBCQYYLPTS"
          "QCCGLVOHNCRVCTCCBEFXRFTOIFAAIIFBOWWRBHGIAQGOEGPEQTRZAVSENITWGBYRIQBH"
          "GXRFTVLRVBAXHZNKRTIFGAJPEGPFBHGCPWUNHFKRCQOTEVLRUEUWNOEVLEWUILGPEOEP"
          "PIPIBVTJIEMCGMIQNIIALTJIBBHGVBXETEGWRYSHTDPIRLTQWRBTJIVZMCGUQNGAVBHV"
          "LRAAOIJPEGPBZRQXBZOTHRZTQYAACTEZJLGXUMMGWFIGGGBLEDSBSSYIEMDKWGZIDYGM"
          "DVSZMSUETMORIEITQVFAOVLNBTJILKOWPQMNVIEQNVLRKOTVRKTFIPZYRXVWNMILEHGR"
          "EMCGMIQNIEGZAPWZQSUMBVOTMTQNCPYGTJIRVIIQNPAFFRMNKRIMNVIQNOTGBUMGVPQA"
          "NTHZPQWRABGJBZEVLROETQNVMKPVBATCFIWKXFWBXMBCSRSGMNVMNTIPXUMOTCVNTJIT"
          "MROEAAHCHFBUEOGWSVVBVGUXNVDCVQQZGHBXETEGQNITEWCGHHZEUXUMITGBLEUABCLF"
          "MALEGHUIVGTEWVGRNTMQWGQMRSFAIDPRBOFIPQPJIEPOYIIMRVLRGBGGNUEEEEMLGWFE"
          "HGRVBCCQRBOVLVAAUTRKTYLVKHWPGQMCXRTYDIPIMGXUMMCMAEECOAMSUXUITJIYXEFX"
          "UMANPVMSVSQMCTCCBTJIPWDGWNATJITMROEABRQSCAWGVRITVEPSIPKSISVEALRGPRVT"
          "NIFALAMGJEEEZMVKXNTFQVGPECPYQEUXBQNVIEKERXNVDFIPZYRXGPEKVVVTGPYQGGRP"
          "MAVXUMEPHBNTJMEBYVABBHGGVXHGVOCRGEHQNRSYINFSOBAKRRLAPIAQGOEZICJMAMTJ"
          "ILAHCVRLTJIVZIPJBZMCXVWNYMGPTJIOZIVMFPAPHSZEPGUBOFIIMLQTPWDGFEMAMMAO"
          "TGGUVISYRATQGEMAVINLEFMPITGHRNFQVGBOYEELSVLVAEPHGPEDVVBIULTWVGVAUEPX"
          "FMTWTGPEESQMAPHPQPJIEACJSBTLQGNBEFMAJUEOVVGJEZAHKVRJLGXPPLGCCIRMXUMR"
          "GXUMYDVBCGJXVVEZTRZTUMAUAVLRUAVMPALQKVKAPHCZODPRUSQPIQNIXUMSGRRERGGE"
          "CIVWJWRMIQBOIIGPETXBKRGEGMPTSGWTATRAOHIYMCVVBVIEQNKHKRRACQQCIRCFYMTQ"
          "GBUPWXRZSVSCZOFYPMDGGEGPVMBVOPEYIRIIEINFJNATGVFKANIGPEAORXTVLRAEGJSW"
          "RVWUQGJPLAEEVRBIXIFWTJEGEOTHJWUNHAWTNINSTQXUMGGVZINHSEKEUWGQLNFRTIGZ"
          "VVGVLRQRESQMSVSOMFWPYGSGGHZEVLROETQNVSJEQJYVLVATKQRIDQTGMDVLRMNKKZIC"
          "KTUMRUAVBHKRGPEKVNZMARNDYCMENOTGRINFWRKRGXFMRXMPMSKRGPEGEETYFELAAHIJ"
          "KIRLRZSYIEMCTEPSEFFHBRGZRILGHYQTVPRPENTSCLKRSWROEGQOPMAVEYHRKRATGQOP"
          "WEMVGEYMDKRSWROEGQOPEOWUVKRZMCRLXLCRFNOTMADAFMAOGTIRKEUSBVAHXRZTJIRF"
          "PGVGAAVFYMTELYMYFIPZYRXRLSGGEMTKRGMLNMTMNEIEMGCVQQNIXUMIVEYQAPRNDYTI"
          "FCLVMAOIPEAILNMRLVKGGWRAHHZIPKGPEDEGBLGSSKARIZITCTNV";
      return cipher_text;
      break;
    case 'c':
      cipher_text =
          "MUYDJUDTJERUWYDEDJXUVYHIJEVVURHKQHOKDHUIJHYSJUTIKRCQHYDUMQHVQHUMUIXQ"
          "BBUDTUQLEHYDIFYJUEVJXYIJEAUUFJXUKDYJUTIJQJUIEVQCUHYSQDUKJHQBYDJXUULU"
          "DJEVJXYIDEJIKSSUUTYDWMUCQAUCUNYSEQFHEFEIQBEVQBBYQDSUEDJXUVEBBEMYDWRQ"
          "IYICQAUMQHJEWUJXUHCQAUFUQSUJEWUJXUHWUDUHEKIVYDQDSYQBIKFFEHJQDTQDKDTU"
          "HIJQDTYDWEDEKHFQHJJXQJCUNYSEYIJEHUSEDGKUHJXUBEIJJUHHYJEHOYDJUNQIDUMC"
          "UNYSEQDTQHYPEDQJXUIUJJBUCUDJYDTUJQYBYIBUVJJEOEKOEKMYBBYDVEHCJXUFHUIY"
          "TUDJEVJXUQRELUCEIJIUSHUJBOQIIEEDQIJXUEKJRHUQAEVMQHMYJXJXUKDYJUTIJQJU"
          "IEVQCUHYSQYISUHJQYDQDTQTTJXUIKWWUIJYEDJXQJXUIXEKBTEDXYIEMDYDYJYQJYLU"
          "YDLYJUZQFQDJEYCCUTYQJUQTXUHUDSUQDTQJJXUIQCUJYCUCUTYQJURUJMUUDZQFQDQD"
          "TEKHIUBLUIFBUQIUSQBBJXUFHUIYTUDJIQJJUDJYEDJEJXUVQSJJXQJJXUHKJXBUIIUC"
          "FBEOCUDJEVEKHIKRCQHYDUIDEMEVVUHIJXUFHEIFUSJEVSECFUBBYDWUDWBQDTYDQVUM"
          "CEDJXIJECQAUFUQSU";
      return cipher_text;
      break;
    default:
      throw "Invalid attack type";
    }
  }
  std::cout << "Reading from 'process.txt'" << std::endl;
  fp >> cipher_text;
  fp.close();

  return cipher_text;
}

std::pair<int, std::string> crackCaesar(std::string cipher_text) {
  std::unordered_map<char, float> char_frequency;
  char_frequency['A'] = 0.08167;
  char_frequency['B'] = 0.01492;
  char_frequency['C'] = 0.02782;
  char_frequency['D'] = 0.04253;
  char_frequency['E'] = 0.12702;
  char_frequency['F'] = 0.02228;
  char_frequency['G'] = 0.02015;
  char_frequency['H'] = 0.06094;
  char_frequency['I'] = 0.06966;
  char_frequency['J'] = 0.00153;
  char_frequency['K'] = 0.00772;
  char_frequency['L'] = 0.04025;
  char_frequency['M'] = 0.02406;
  char_frequency['N'] = 0.06749;
  char_frequency['O'] = 0.07507;
  char_frequency['P'] = 0.01929;
  char_frequency['Q'] = 0.00095;
  char_frequency['R'] = 0.05987;
  char_frequency['S'] = 0.06327;
  char_frequency['T'] = 0.09056;
  char_frequency['U'] = 0.02758;
  char_frequency['V'] = 0.00978;
  char_frequency['W'] = 0.02360;
  char_frequency['X'] = 0.00150;
  char_frequency['Y'] = 0.01974;
  char_frequency['Z'] = 0.00074;

  std::unordered_map<char, int> char_count;
  for (int i = 0; i < cipher_text.size(); ++i) {
    char_count[cipher_text[i]]++;
  }
  char most_frequent_char =
      std::max_element(
          char_count.begin(), char_count.end(),
          [](const std::pair<char, int> &p1, const std::pair<char, int> &p2) {
            return p1.second < p2.second;
          })
          ->first;
  // std::cout << "most frequent char in cipher: " << most_frequent_char
  //           << std::endl;

  char most_frequent_char_in_deciphered_text =
      std::max_element(char_frequency.begin(), char_frequency.end(),
                       [](const std::pair<char, float> &p1,
                          const std::pair<char, float> &p2) {
                         return p1.second < p2.second;
                       })
          ->first;

  int key;
  key = most_frequent_char - most_frequent_char_in_deciphered_text;
  key = (key < 0) ? 26 + key : key;

  return std::make_pair(key, decrypt_caesar(cipher_text, key));
}

std::pair<std::string, std::string> crackVigenere(std::string cipher_text) {
  // iterate over batches of cipher text of size key_size and group the 'i'the
  // element of each batch
  std::map<int, int> max_E; // map of batch size and count of E
  for (int key_size = 3; key_size <= 10; key_size++) {
    max_E[key_size] = 0;
    std::vector<std::string> groups(key_size);
    for (int i = 0; i < cipher_text.size(); i++) {
      groups[i % key_size].push_back(cipher_text[i]);
    }
    // apply caesar attack on each group and store possible keys in a vector
    std::vector<std::string> possible_deciphered_group(key_size);
    for (int i = 0; i < key_size; i++) {
      possible_deciphered_group[i] = crackCaesar(groups[i]).second;
    }
    for (int i = 0; i < key_size; i++) {
      int count = std::count(possible_deciphered_group[i].begin(),
                             possible_deciphered_group[i].end(), 'E');
      max_E[key_size] = max_E[key_size] + count;
    }
  }
  int best_key_size = std::max_element(max_E.begin(), max_E.end(),
                                       [](const std::pair<int, int> &p1,
                                          const std::pair<int, int> &p2) {
                                         return p1.second < p2.second;
                                       })
                          ->first;
  // LOG(best_key_size);
  // decipher the cipher text using the best key size
  std::vector<std::string> groups(best_key_size);
  for (int i = 0; i < cipher_text.size(); i++) {
    groups[i % best_key_size].push_back(cipher_text[i]);
  }
  // apply caesar attack on each group and store possible keys and deciphered
  // group
  std::vector<std::string> possible_deciphered_group(best_key_size);
  std::vector<int> possible_key(best_key_size);
  for (int i = 0; i < best_key_size; i++) {
    auto result = crackCaesar(groups[i]);
    possible_deciphered_group[i] = result.second;
    possible_key[i] = result.first;
  }
  // transpose the deciphered groups to get the deciphered text
  std::string output;
  for (int i = 0; output.size() < cipher_text.size(); i++) {
    for (int j = 0; j < best_key_size && output.size() < cipher_text.size();
         j++) {
      output.push_back(possible_deciphered_group[j][i]);
    }
  }
  // get the key in string format
  std::string key;
  for (int i = 0; i < possible_key.size(); i++) {
    key.push_back(possible_key[i] + 'A');
  }

  return std::make_pair(key, output);
}
