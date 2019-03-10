#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <utility>
#include <iterator>

class Product{
public:
    Product()  = default;
    ~Product() = default;
    Product( const Product& rhs ) = default;
    Product(  Product&& rhs ) = default;
    Product& operator=( const Product& rhs ) = default;
    Product& operator=( Product&& rhs ) = default;

    Product(
      const std::string& m
    , const std::string& n
    , size_t p):
      m_manufacturer(m)
    , m_name(n)
    , m_price(p){}

    Product(
      std::string&& m
      ,std::string&& n
      , size_t p):
        m_manufacturer(std::move(m))
      , m_name(std::move(n))
      , m_price(p){}

    void setManufacturer( const std::string& m){
        m_manufacturer = m;
    }
    void setManufacturer( std::string&& m){
        m_manufacturer = std::move(m);
    }
    const std::string& getManufacturer() const{
        return m_manufacturer;
    }
    void setName( const std::string& n){
        m_name = n;
    }
    void setName( std::string&& n){
        m_name = std::move(n);
    }
    const std::string& getName() const{
        return m_name;
    }
    void setPrice( size_t p ){
        m_price = p;
    }
    size_t getPrice() const{
        return m_price;
    }
private:
    std::string m_manufacturer;
    std::string m_name;
    size_t      m_price;
};

class  Storage{
public:
    void insert( const std::string& K, const Product& V ){
        m_data.insert(std::make_pair((K), V));
    }


    const bool getOne( const std::string& key, Product& out ) const{
        auto ref = m_data.find(key);
        if(ref == m_data.cend())
            return false;
        out = ref->second;
        return true;
    }

    // TODO: change output container
    void getByManufacturer(const std::string& m, std::unordered_map<std::string, Product>& out) const {
        std::copy_if(m_data.cbegin(), m_data.cend(), std::inserter(out, std::next(out.begin())),
                [&m](const std::pair<std::string, Product>& r){
            return (r.second.getManufacturer() == m);
        });
    }

    void removeOne(const std::string& K){
        auto ref = m_data.find(K);
        if(ref == m_data.cend())
            return;
        m_data.erase(K);
    }
private:
    std::unordered_map<std::string, Product> m_data;
};

int main() {

    Storage s;
    s.insert("art1", Product("China ltd", "trash", 1u));

    return 0;
}