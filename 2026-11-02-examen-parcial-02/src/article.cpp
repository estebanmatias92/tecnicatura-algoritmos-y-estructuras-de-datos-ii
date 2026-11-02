#include "article.hpp"

#include <stdexcept>

namespace partial02 {

Article::Article(std::string code, std::string description, Money unitPrice)
    : code_(std::move(code)),
      description_(std::move(description)),
      unitPrice_(std::move(unitPrice)) {
    if (code_.empty()) {
        throw std::invalid_argument("Article code cannot be empty");
    }
    if (unitPrice_.cents() <= 0) {
        throw std::invalid_argument("Unit price must be greater than zero");
    }
}

}  // namespace partial02
