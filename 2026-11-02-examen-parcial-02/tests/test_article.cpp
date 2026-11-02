#include "article.hpp"

#include <gtest/gtest.h>

using partial02::Article;
using partial02::Money;

TEST(Article, ValidArticle) {
    Article a("CAU-001", "Caucho natural", Money(150000));
    EXPECT_EQ(a.code(), "CAU-001");
    EXPECT_EQ(a.description(), "Caucho natural");
    EXPECT_EQ(a.unitPrice().cents(), 150000);
}

TEST(Article, EmptyCodeRejected) {
    EXPECT_THROW(Article("", "Desc", Money(1000)), std::invalid_argument);
}

TEST(Article, ZeroPriceRejected) {
    EXPECT_THROW(Article("CAU-001", "Desc", Money(0)), std::invalid_argument);
}

TEST(Article, NegativePriceRejected) {
    EXPECT_THROW(Article("CAU-001", "Desc", Money(-1)), std::invalid_argument);
}

TEST(Article, DescriptionCanBeEmpty) {
    // Ninguna regla de negocio prohíbe descripción vacía
    Article a("CAU-001", "", Money(150000));
    EXPECT_EQ(a.description(), "");
}

TEST(Article, ComparisonByCode) {
    Article a("CAU-001", "A", Money(1000));
    Article b("CAU-002", "B", Money(2000));

    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
    EXPECT_TRUE(a == a);
}
