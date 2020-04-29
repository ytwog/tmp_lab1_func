#include "../text.h"
#include <gtest/gtest.h>

using namespace mLab;

int executeProgram(std::ofstream &ofstr, std::ifstream &ifstr) {
    setlocale(LC_ALL, 0);

    if(ifstr.bad() || ifstr.fail() || ofstr.bad() || ofstr.fail()) {
        return print_err(7);
    }
    _mContainer container;
    Init(&container);

    int error_code = read_from_file(&ifstr, &container);
    sort(&container);
    return error_code;
}

// Проверка на отсутствие ошибок при стандартном раскладе
TEST(Unit_test, TestNoErrors) {
    std::ifstream ifstr("input.txt");
    std::ofstream ofstr("output.txt");

    int finalCode = executeProgram(ofstr, ifstr);
    EXPECT_EQ(finalCode, 0);
}

// Проверка на обработку ошибки при некорректном вводе метки >text
TEST(Unit_test, TestError1) {
    std::ifstream ifstr("tests_1/inperr1.txt");
    std::ofstream ofstr("output.txt");
    int finalCode = executeProgram(ofstr, ifstr);
    EXPECT_EQ(finalCode, 1);
}

// Проверка на обработку ошибки при некорректном вводе метки >replace
TEST(Unit_test, TestError2) {
    std::ifstream ifstr("tests_1/inperr2.txt");
    std::ofstream ofstr("output.txt");
    int finalCode = executeProgram(ofstr, ifstr);
    EXPECT_EQ(finalCode, 2);
}

// Проверка на обработку ошибки при некорректном вводе метки >with
TEST(Unit_test, TestError3) {
    std::ifstream ifstr("tests_1/inperr3.txt");
    std::ofstream ofstr("output.txt");
    int finalCode = executeProgram(ofstr, ifstr);
    EXPECT_EQ(finalCode, 3);
}


// Проверка на обработку ошибки при различии длины исходного и заменяемого алфавита
TEST(Unit_test, TestError4) {
    std::ifstream ifstr("tests_1/inperr4.txt");
    std::ofstream ofstr("output.txt");
    int finalCode = executeProgram(ofstr, ifstr);
    EXPECT_EQ(finalCode, 4);
}

// Проверка на обработку ошибки при некорректном вводе метки >type
TEST(Unit_test, TestError5) {
    std::ifstream ifstr("tests_1/inperr5.txt");
    std::ofstream ofstr("output.txt");
    int finalCode = executeProgram(ofstr, ifstr);
    EXPECT_EQ(finalCode, 5);
}


// Проверка на обработку ошибки
TEST(Unit_test, TestError6) {
    std::ifstream ifstr("tests_1/inperr6.txt");
    std::ofstream ofstr("output.txt");
    int finalCode = executeProgram(ofstr, ifstr);
    EXPECT_EQ(finalCode, 13);
}


// Проверка на обработку ошибки при вводе некорректного типа
TEST(Unit_test, TestError9) {
    std::ifstream ifstr("tests_1/inperr9.txt");
    std::ofstream ofstr("output.txt");
    int finalCode = executeProgram(ofstr, ifstr);
    EXPECT_EQ(finalCode, 9);
}


// Проверка на корректность сортировки
TEST(Unit_test, TestSort) {
    std::ifstream ifstr("tests_1/inptest.txt");
    std::ofstream ofstr("output.txt");
    if(ifstr.bad() || ifstr.fail() || ofstr.bad() || ofstr.fail()) {
        // Тест провален
        EXPECT_FALSE(true);
    }
    _mContainer container;
    Init(&container);

    read_from_file(&ifstr, &container);
    write_to_file(&ofstr, &container);
    sort(&container);

    int prev = counter_function((text*)container.start);
    for(auto i = container.start->next; i != nullptr; i = i->next) {
        if(prev < counter_function((text*)i)) {
            //EXPECT_FALSE(true);
            return;
        }
        prev = counter_function((text*)i);
    }
    write_to_file(&ofstr, &container);
    ofstr.close();
}
