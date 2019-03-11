#ifndef __PRODUCT_HPP__
#define __PRODUCT_HPP__

#include <string>

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
    void setPrice( size_t p ) noexcept{
        m_price = p;
    }
    size_t getPrice() const noexcept{
        return m_price;
    }
private:
    std::string m_manufacturer;
    std::string m_name;
    size_t      m_price;
};

#endif // __PRODUCT_HPP__