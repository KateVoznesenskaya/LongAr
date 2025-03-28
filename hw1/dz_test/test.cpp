#include "../_deps/catch2/catch_amalgamated.hpp"
#include "../LongAr.hpp"

TEST_CASE( "Сложение", "[LongARPlus]" ) {

    // given
    LongAr a("23.4", 1, 1);
    LongAr b("4.2", 1, 1);
    LongAr expected("27.6", 1, 1);
    // when
    auto res = a+b;
    // then 
    REQUIRE(res == expected);

}

TEST_CASE("Сложение2", "[LongARPlus2]") {

    LongAr a("4294967295.6", 33, 1);
    LongAr b("0.5", 1, 1);
    LongAr expected("4294967296.1", 33, 1);
    auto res = a+b;
    REQUIRE(res == expected);
}
TEST_CASE( "Вычитание", "[LongARMinus]" ) {

    LongAr a("23.4", 1, 1);
    LongAr b("4.2", 1, 1);
    LongAr exepted("19.2", 1, 1);
    auto res = a-b;
    REQUIRE(res == exepted);
}
TEST_CASE( "Вычитание2", "[LongARMinus2]" ) {

    LongAr a("4294967296.6", 33, 1);
    LongAr b("1.6", 1, 1);
    auto res = a-b;
    LongAr exepted("4294967295.0", 33, 1);
    REQUIRE(res == exepted);
}
TEST_CASE( "Умножение", "[LongARMul]" ) {

    LongAr a("10.5", 1, 1);
    LongAr b("2.5", 1, 1);
    auto res = a*b;
    LongAr exepted("26.25", 1, 1);
    REQUIRE(res == exepted);
}
TEST_CASE( "Деление", "[LongARDiv]" ) {

    LongAr a("100.0", 1, 1);
    LongAr b("2.5", 1, 1);
    auto res = a/b;
    LongAr exepted("40.0", 1, 1);
    REQUIRE(res == exepted);
}
TEST_CASE( "Сравнение", "[LongARDiff]" ) {

    LongAr a("23.4", 1, 1);
    LongAr b("4.2", 1, 1);
    auto res1 = a==b;
    auto res2 = a!=b;
    auto res3 = a>b;
    auto res4 = a<b;
    REQUIRE(res1 == 0);
    REQUIRE(res2 == 1);
    REQUIRE(res3 == 1);
    REQUIRE(res4 == 0);
}