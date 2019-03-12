#include <iostream>
#include <algorithm>
#include <string>
#include <thread>
#include <vector>
#include <utility>

#include "product.hpp"
#include "storage.hpp"

/*
*
 * if the second thread overtakes the first one, 
 * it will not be able to remove all the elements, 
 * because the first thread must first add them
 *
 */
 

// insert objects with specified key sequence
void inserter(Storage &s, std::string &key) {
  // generates a new key in each iteration
  while (std::next_permutation(key.begin(), key.end())) {
    s.insert(key, Product("china ltd", "name", 123));
  }
}

// remove objects with specified key sequence
void remover(Storage &s, std::string &key) {
  // generates a new key in each iteration
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
  // the first thread is guaranteed to exit earlier
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
    std::vector<Product> buf;
    s.getByManufacturer("china ltd", std::ref(buf));
    std::cout << buf.size() << std::endl; // should be eqal to s.size()
  }

  std::cin.get();
  return 0;
}