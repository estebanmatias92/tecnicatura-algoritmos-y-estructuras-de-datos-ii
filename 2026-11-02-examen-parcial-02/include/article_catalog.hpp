#ifndef PARTIAL02_ARTICLE_CATALOG_HPP
#define PARTIAL02_ARTICLE_CATALOG_HPP

#include "article.hpp"
#include "repository.hpp"

#include <memory>
#include <string>
#include <vector>

namespace partial02 {

/// Catálogo de artículos: dueño de los objetos Article (punteros estables).
/// Los PurchaseOrder referencian artículos mediante punteros no propietarios
/// al catálogo, así que el precio unitario siempre se consulta aquí (BR-012).
/// Implementa Repository<Article, std::string> para que el catálogo en memoria
/// y el adaptador MariaDbArticleRepository sean intercambiables por el mismo
/// puerto (DIP): Console y PurchaseOrderService programan contra la interfaz,
/// no contra una implementación concreta.
class ArticleCatalog : public Repository<Article, std::string> {
public:
    /// Agrega un artículo al catálogo. Lanza si el código ya existe (BR-002).
    void add(std::unique_ptr<Article> article);

    /// Repository<Article, std::string>: agrega por copia (el llamador ya no
    /// necesita transferir la propiedad). Lanza si el código ya existe.
    void add(const Article& article) override;

    /// Busca un artículo por código. Retorna nullptr si no existe.
    const Article* find(const std::string& code) const override;

    /// Retorna todos los artículos (punteros al catálogo, no copias).
    std::vector<const Article*> all() const override;

private:
    std::vector<std::unique_ptr<Article>> items_;
};

}  // namespace partial02

#endif  // PARTIAL02_ARTICLE_CATALOG_HPP
