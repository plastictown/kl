#ifndef __STORAGE_HPP__
#define __STORAGE_HPP__

#include <string>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <utility>
#include <iterator>

#include <thread>
#include <mutex>

class  Storage{
  
public:
    void insert( const std::string& K, const Product& V ){
      
        std::unique_lock<decltype(m_rlock)> lk1(m_rlock, std::defer_lock);
        std::unique_lock<decltype(m_wlock)> lk2(m_wlock, std::defer_lock);
        std::lock(lk1, lk2);
        
        m_data.insert(std::make_pair((K), V));
    }

    const bool getOne( const std::string& key, Product& out ) const{
      
      std::unique_lock<decltype(m_wlock)> lock(m_wlock);
      
        auto ref = m_data.find(key);
        if(ref == m_data.cend())
            return false;
        out = ref->second;
        return true;
    }

    // TODO: change output container
    void getByManufacturer(const std::string& m, std::vector<std::pair<std::string, Product>>& out) const {
      
        std::unique_lock<decltype(m_wlock)> lock(m_wlock);
        
        std::copy_if(m_data.cbegin(), m_data.cend(), out.begin(),
                [&m](const std::pair<std::string, Product>& r){
            return (r.second.getManufacturer() == m);
        });
    }
    
    size_t size() const{
      std::unique_lock<decltype(m_wlock)> lock(m_wlock);
      return m_data.size();
    }

    void removeOne(const std::string& K){
      
      std::unique_lock<decltype(m_rlock)> lk1(m_rlock, std::defer_lock);
      std::unique_lock<decltype(m_wlock)> lk2(m_wlock, std::defer_lock);
      std::lock(lk1, lk2);
      
        auto ref = m_data.find(K);
        if(ref == m_data.cend())
            return;
        m_data.erase(K);
    }
private:
    std::unordered_map<std::string, Product> m_data;
    mutable std::recursive_mutex m_rlock;
    mutable std::recursive_mutex m_wlock;
};

#endif // __STORAGE_HPP__