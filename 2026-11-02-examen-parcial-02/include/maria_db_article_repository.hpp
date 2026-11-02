#ifndef PARTIAL02_MARIA_DB_ARTICLE_REPOSITORY_HPP
#define PARTIAL02_MARIA_DB_ARTICLE_REPOSITORY_HPP

#include "maria_db_connection.hpp"
#include "repository.hpp"
#include "article.hpp"

#include <memory>
#include <string>
#include <vector>

namespace partial02 {

/// Adaptador MariaDB para Article. Implementa Repository<Article, std::string>
/// (solo lectura + alta). Los objetos Article se almacenan en un caché interno
/// para que los punteros devueltos por find()/all() sean estables.
class MariaDbArticleRepository : public Repository<Article, std::string> {
public:
    explicit MariaDbArticleRepository(MariaDbConnection& conn);

    const Article* find(const std::string& key) const override;
    std::vector<const Article*> all() const override;
    void add(const Article& entity) override;

private:
    MariaDbConnection& conn_;
    mutable std::vector<std::unique_ptr<Article>> cache_;

    void loadAll() const;
    const Article* findInCache(const std::string& key) const;
};

}  // namespace partial02

#endif  // PARTIAL02_MARIA_DB_ARTICLE_REPOSITORY_HPP
