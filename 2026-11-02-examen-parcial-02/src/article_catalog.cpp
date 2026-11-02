#include "article_catalog.hpp"

namespace partial02 {

void ArticleCatalog::add(std::unique_ptr<Article> article) {
    for (const auto& existing : items_) {
        if (existing->code() == article->code()) {
            throw std::runtime_error("duplicate article code");
        }
    }
    items_.push_back(std::move(article));
}

void ArticleCatalog::add(const Article& article) {
    if (find(article.code()) != nullptr) {
        throw std::runtime_error("duplicate article code");
    }
    items_.push_back(std::make_unique<Article>(article));
}

const Article* ArticleCatalog::find(const std::string& code) const {
    for (const auto& item : items_) {
        if (item->code() == code) {
            return item.get();
        }
    }
    return nullptr;
}

std::vector<const Article*> ArticleCatalog::all() const {
    std::vector<const Article*> result;
    result.reserve(items_.size());
    for (const auto& item : items_) {
        result.push_back(item.get());
    }
    return result;
}

}  // namespace partial02
