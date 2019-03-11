#include <iostream>
#include <algorithm>
#include <string>
#include <thread>
#include <vector>
#include <utility>

#include "product.hpp"
#include "storage.hpp"

void inserter(Storage &s, std::string &key) {
  while (std::next_permutation(key.begin(), key.end())) {
    s.insert(key, Product("china ltd", "name", 123));
  }
}

void remover(Storage &s, std::string &key) {
  while (std::next_permutation(key.begin(), key.end())) {
    s.removeOne(key);
  }
}

int main() {

  Storage s;
  std::string k1 = "abracadabra";
  std::string k2 = k1;


  //---sequential execution---//
  std::thread t1(inserter, std::ref(s), std::ref(k1));
  t1.join();
  std::thread t2(remover, std::ref(s), std::ref(k2));
  t2.join();
  std::cout << s.size() << std::endl; // the result should be 0

  k1 = k2 = "abcdef";

  //---parallel execution---//
  std::thread t3(inserter, std::ref(s), std::ref(k1));
  std::thread t4(remover, std::ref(s), std::ref(k2));
  t3.join();
  t4.join();
  std::cout << s.size() << std::endl; // the result may not be 0

  if(s.size()>1u){
    std::vector<std::pair<std::string, Product>> buf;
    s.getByManufacturer("china ltd", std::ref(buf)); // crash here
    std::cout << buf.size() << std::endl;
  }

  std::cin.get();
  return 0;
}