#include "domain_error.hpp"

#include <gtest/gtest.h>

using partial02::ConflictError;
using partial02::DomainError;
using partial02::ErrorCode;
using partial02::NotFoundError;
using partial02::ValidationError;

TEST(DomainError, CodeAndFields) {
    partial02::Fields fields{{"cuit", "2012345678"}};
    ConflictError err(ErrorCode::DuplicateCuit, fields);
    EXPECT_EQ(err.code(), ErrorCode::DuplicateCuit);
    EXPECT_EQ(err.fields().at("cuit"), "2012345678");
    EXPECT_EQ(err.code(), ErrorCode::DuplicateCuit);
    EXPECT_EQ(err.fields().size(), 1u);
}

TEST(DomainError, DefaultFieldsEmpty) {
    NotFoundError err(ErrorCode::UnknownSupplier);
    EXPECT_TRUE(err.fields().empty());
}

TEST(DomainError, Hierarchy) {
    ValidationError ve(ErrorCode::EmptyArticleCode);
    NotFoundError nfe(ErrorCode::UnknownArticle);
    ConflictError ce(ErrorCode::DuplicateCuit);

    EXPECT_EQ(ve.code(), ErrorCode::EmptyArticleCode);
    EXPECT_EQ(nfe.code(), ErrorCode::UnknownArticle);
    EXPECT_EQ(ce.code(), ErrorCode::DuplicateCuit);

    // Todas son std::runtime_error derivadas
    EXPECT_NE(std::string(ve.what()).find("domain"), std::string::npos);
    EXPECT_NE(std::string(nfe.what()).find("domain"), std::string::npos);
    EXPECT_NE(std::string(ce.what()).find("domain"), std::string::npos);
}
