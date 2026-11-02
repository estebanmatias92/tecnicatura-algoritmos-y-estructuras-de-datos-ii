#ifndef PARTIAL02_ARTICLE_CATALOG_HPP
#define PARTIAL02_ARTICLE_CATALOG_HPP

#include "article.hpp"

#include <memory>
#include <string>
#include <vector>

namespace partial02 {

/// Catálogo de artículos: dueño de los objetos Article (punteros estables).
/// Los PurchaseOrder referencian artículos mediante punteros no propietarios
/// al catálogo, así que el precio unitario siempre se consulta aquí (BR-012).
/// No implementa Repository<Article,string> porque find() necesita devolver
/// punteros estables, no copias por valor.
class ArticleCatalog {
public:
    /// Agrega un artículo al catálogo. Lanza si el código ya existe (BR-002).
    void add(std::unique_ptr<Article> article);

    /// Busca un artículo por código. Retorna nullptr si no existe.
    const Article* find(const std::string& code) const;

    /// Retorna todos los artículos (punteros al catálogo, no copias).
    std::vector<const Article*> all() const;

private:
    std::vector<std::unique_ptr<Article>> items_;
};

}  // namespace partial02

#endif  // PARTIAL02_ARTICLE_CATALOG_HPP
