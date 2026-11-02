#ifndef PARTIAL02_INMEMORY_REPOSITORY_HPP
#define PARTIAL02_INMEMORY_REPOSITORY_HPP

#include "repository.hpp"

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

namespace partial02 {

/// Implementación en memoria de Repository<T,K> y MutableRepository<T,K>.
/// Almacena entidades en std::unique_ptr para que los punteros devueltos por
/// find()/all() sean estables (no se invalidan por realocación de vector).
template <class T, class K>
class InMemoryRepository : public MutableRepository<T, K> {
public:
    using KeyExtractor = std::function<K(const T&)>;

    explicit InMemoryRepository(KeyExtractor keyOf) : keyOf_(std::move(keyOf)) {}

    const T* find(const K& key) const override {
        for (const auto& ptr : items_) {
            if (keyOf_(*ptr) == key) {
                return ptr.get();
            }
        }
        return nullptr;
    }

    std::vector<const T*> all() const override {
        std::vector<const T*> result;
        result.reserve(items_.size());
        for (const auto& ptr : items_) {
            result.push_back(ptr.get());
        }
        return result;
    }

    void add(const T& entity) override {
        K key = keyOf_(entity);
        if (find(key) != nullptr) {
            throw std::runtime_error("duplicate key");
        }
        items_.push_back(std::make_unique<T>(entity));
    }

    void update(const T& entity) override {
        K key = keyOf_(entity);
        for (auto& ptr : items_) {
            if (keyOf_(*ptr) == key) {
                *ptr = entity;
                return;
            }
        }
        throw std::runtime_error("not found");
    }

    void remove(const K& key) override {
        auto it = std::remove_if(items_.begin(), items_.end(),
                                 [&](const std::unique_ptr<T>& ptr) {
                                     return keyOf_(*ptr) == key;
                                 });
        if (it == items_.end()) {
            throw std::runtime_error("not found");
        }
        items_.erase(it, items_.end());
    }

private:
    KeyExtractor keyOf_;
    std::vector<std::unique_ptr<T>> items_;
};

}  // namespace partial02

#endif  // PARTIAL02_INMEMORY_REPOSITORY_HPP
