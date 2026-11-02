#include "article.hpp"
#include "article_catalog.hpp"
#include "money.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <string>

using partial02::Article;
using partial02::ArticleCatalog;
using partial02::Money;

TEST(ArticleCatalog, AddUniquePtrYEncuentra) {
    ArticleCatalog catalog;
    catalog.add(std::make_unique<Article>("CAU-001", "Caucho natural",
                                          Money(150000)));
    const Article* found = catalog.find("CAU-001");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->code(), "CAU-001");
    EXPECT_EQ(found->description(), "Caucho natural");
}

TEST(ArticleCatalog, AddUniquePtrDuplicadoRechazado) {
    ArticleCatalog catalog;
    catalog.add(std::make_unique<Article>("CAU-001", "Caucho natural",
                                          Money(150000)));
    EXPECT_THROW(catalog.add(std::make_unique<Article>("CAU-001", "Otra",
                                                       Money(2000))),
                 std::runtime_error);
    EXPECT_EQ(catalog.all().size(), 1u);
}

TEST(ArticleCatalog, AddPorCopiaYEncuentra) {
    ArticleCatalog catalog;
    catalog.add(Article("AZU-002", "Azufre", Money(80000)));
    const Article* found = catalog.find("AZU-002");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->code(), "AZU-002");
    EXPECT_EQ(found->unitPrice().cents(), 80000);
}

TEST(ArticleCatalog, AddPorCopiaDuplicadoRechazado) {
    ArticleCatalog catalog;
    catalog.add(Article("CAU-001", "Caucho natural", Money(150000)));
    EXPECT_THROW(catalog.add(Article("CAU-001", "Duplicado", Money(999))),
                 std::runtime_error);
    EXPECT_EQ(catalog.all().size(), 1u);
}

TEST(ArticleCatalog, FindInexistenteRetornaNulo) {
    ArticleCatalog catalog;
    EXPECT_EQ(catalog.find("NO-EXISTE"), nullptr);
}

TEST(ArticleCatalog, AllVacio) {
    ArticleCatalog catalog;
    EXPECT_TRUE(catalog.all().empty());
}

TEST(ArticleCatalog, AllRetornaTodos) {
    ArticleCatalog catalog;
    catalog.add(std::make_unique<Article>("CAU-001", "Caucho natural",
                                          Money(150000)));
    catalog.add(std::make_unique<Article>("AZU-002", "Azufre", Money(80000)));
    auto todos = catalog.all();
    ASSERT_EQ(todos.size(), 2u);
    std::string codigos;
    for (const Article* a : todos) {
        codigos += a->code();
    }
    EXPECT_EQ(codigos, "CAU-001AZU-002");
}
