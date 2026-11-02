#ifndef PARTIAL02_ARTICLE_HPP
#define PARTIAL02_ARTICLE_HPP

#include "money.hpp"

#include <string>

namespace partial02 {

/// Artículo de materia prima. Tiene code, description y unitPrice.
/// El precio vive en el catálogo, no en el pedido.
class Article {
public:
    Article(std::string code, std::string description, Money unitPrice);

    const std::string& code() const noexcept { return code_; }
    const std::string& description() const noexcept { return description_; }
    const Money& unitPrice() const noexcept { return unitPrice_; }

    bool operator==(const Article& other) const noexcept { return code_ == other.code_; }
    bool operator!=(const Article& other) const noexcept { return !(*this == other); }
    bool operator<(const Article& other) const noexcept { return code_ < other.code_; }

private:
    std::string code_;
    std::string description_;
    Money unitPrice_;
};

}  // namespace partial02

#endif  // PARTIAL02_ARTICLE_HPP
