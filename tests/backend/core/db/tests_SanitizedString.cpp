//
// Created by parthu on 1/3/24.
//
#include "tests_SanitizedString.hpp"

TEST(SanitizedString, unchanged_values)
{
    const std::string alpha{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    const SanitizedString alpha_sanitized{alpha};
    ASSERT_EQ(alpha, alpha_sanitized.data());
}
