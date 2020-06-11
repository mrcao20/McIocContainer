#include "MacroTest.h"

#include <QDebug>

#include "ReferenceBean.h"

template<typename T>
void aaa(const char *a) {
    qDebug() << "aaaaaaaaa1111111" << a;
}

template<typename T, typename O>
void aaa(const char *a) {
    qDebug() << "bbbbbbbbbbb1111111" << a;
}

#define TEST_IMPL(Class, ...) #Class

#define TEST(...) \
    aaa<__VA_ARGS__>(TEST_IMPL(__VA_ARGS__));

MacroTest::MacroTest()
{
    TEST(ReferenceBean, IRR)
}
