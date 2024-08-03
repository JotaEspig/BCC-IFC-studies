#include <fstream>
#include <iostream>

int main() {
  std::ifstream arquivo("bla.txt");
  std::string linha;
  for (int i = 0; i < 1000; ++i) {
    for (int j = 0; j < 3; ++j) {
      std::getline(arquivo, linha);
      std::cout << linha << std::endl;
    }
  }
}
