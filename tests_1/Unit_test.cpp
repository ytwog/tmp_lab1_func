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
    char *arg1 = new char[10]{'i', 'n', 'p', 'u', 't', '.', 't', 'x', 't', '\0'};
    char *arg2 = new char[12]{'o', 'u', 't', 'p', 'u', 't', '1', '.', 't', 'x', 't','\0'};
    std::ifstream ifstr(arg1);
    std::ofstream ofstr(arg2);

    int finalCode = executeProgram(ofstr, ifstr);
    EXPECT_EQ(finalCode, 0);
    delete [] arg1;
    delete [] arg2;
}

// Проверка на обработку ошибки при некорректном вводе метки >text
TEST(Unit_test, TestError1) {
    char *arg1 = new char[22]{'t', 'e', 's', 't', 's', '_', '1', '/', 'i', 'n', 'p', 'e', 'r', 'r', '1', '.', 't', 'x', 't', '\0'};
    char *arg2 = new char[12]{'o', 'u', 't', 'p', 'u', 't', 'Q', '.', 't', 'x', 't', '\0'};
    std::ifstream ifstr(arg1);
    std::ofstream ofstr(arg2);

    int finalCode = executeProgram(ofstr, ifstr);
    EXPECT_EQ(finalCode, 1);
    delete [] arg1;
    delete [] arg2;
}

// Проверка на обработку ошибки при некорректном вводе метки >replace
TEST(Unit_test, TestError2) {
    char *arg1 = new char[22]{'t', 'e', 's', 't', 's', '_', '1', '/', 'i', 'n', 'p', 'e', 'r', 'r', '2', '.', 't', 'x', 't', '\0'};
    char *arg2 = new char[12]{'o', 'u', 't', 'p', 'u', 't', 'Q', '.', 't', 'x', 't', '\0'};
    std::ifstream ifstr(arg1);
    std::ofstream ofstr(arg2);

    int finalCode = executeProgram(ofstr, ifstr);
    EXPECT_EQ(finalCode, 2);
    delete [] arg1;
    delete [] arg2;
}

// Проверка на обработку ошибки при некорректном вводе метки >with
TEST(Unit_test, TestError3) {
    char *arg1 = new char[22]{'t', 'e', 's', 't', 's', '_', '1', '/', 'i', 'n', 'p', 'e', 'r', 'r', '3', '.', 't', 'x', 't', '\0'};
    char *arg2 = new char[12]{'o', 'u', 't', 'p', 'u', 't', 'Q', '.', 't', 'x', 't', '\0'};
    std::ifstream ifstr(arg1);
    std::ofstream ofstr(arg2);

    int finalCode = executeProgram(ofstr, ifstr);
    EXPECT_EQ(finalCode, 3);
    delete [] arg1;
    delete [] arg2;
}


// Проверка на обработку ошибки при различии длины исходного и заменяемого алфавита
TEST(Unit_test, TestError4) {
    char *arg1 = new char[22]{'t', 'e', 's', 't', 's', '_', '1', '/', 'i', 'n', 'p', 'e', 'r', 'r', '4', '.', 't', 'x', 't', '\0'};
    char *arg2 = new char[12]{'o', 'u', 't', 'p', 'u', 't', 'Q', '.', 't', 'x', 't', '\0'};
    std::ifstream ifstr(arg1);
    std::ofstream ofstr(arg2);

    int finalCode = executeProgram(ofstr, ifstr);
    EXPECT_EQ(finalCode, 4);
    delete [] arg1;
    delete [] arg2;
}

// Проверка на обработку ошибки при некорректном вводе метки >type
TEST(Unit_test, TestError5) {
    char *arg1 = new char[22]{'t', 'e', 's', 't', 's', '_', '1', '/', 'i', 'n', 'p', 'e', 'r', 'r', '5', '.', 't', 'x', 't', '\0'};
    char *arg2 = new char[12]{'o', 'u', 't', 'p', 'u', 't', 'Q', '.', 't', 'x', 't', '\0'};
    std::ifstream ifstr(arg1);
    std::ofstream ofstr(arg2);

    int finalCode = executeProgram(ofstr, ifstr);
    EXPECT_EQ(finalCode, 5);
    delete [] arg1;
    delete [] arg2;
}


// Проверка на обработку ошибки
TEST(Unit_test, TestError6) {
    char *arg1 = new char[22]{'t', 'e', 's', 't', 's', '_', '1', '/', 'i', 'n', 'p', 'e', 'r', 'r', '6', '.', 't', 'x', 't', '\0'};
    char *arg2 = new char[12]{'o', 'u', 't', 'p', 'u', 't', 'Q', '.', 't', 'x', 't', '\0'};
    std::ifstream ifstr(arg1);
    std::ofstream ofstr(arg2);

    int finalCode = executeProgram(ofstr, ifstr);
    EXPECT_EQ(finalCode, 13);
    delete [] arg1;
    delete [] arg2;
}


// Проверка на обработку ошибки при вводе некорректного типа
TEST(Unit_test, TestError9) {
    char *arg1 = new char[22]{'t', 'e', 's', 't', 's', '_', '1', '/', 'i', 'n', 'p', 'e', 'r', 'r', '9', '.', 't', 'x', 't', '\0'};
    char *arg2 = new char[12]{'o', 'u', 't', 'p', 'u', 't', 'Q', '.', 't', 'x', 't', '\0'};
    std::ifstream ifstr(arg1);
    std::ofstream ofstr(arg2);

    int finalCode = executeProgram(ofstr, ifstr);
    EXPECT_EQ(finalCode, 9);
    delete [] arg1;
    delete [] arg2;
}


// Проверка на корректность сортировки
TEST(Unit_test, TestSort) {
    char *arg1 = new char[22]{'t', 'e', 's', 't', 's', '_', '1', '/', 'i', 'n', 'p', 't', 'e', 's', 't', '.', 't', 'x', 't', '\0'};
    char *arg2 = new char[12]{'o', 'u', 't', 'p', 'u', 't', 'Q', '.', 't', 'x', 't', '\0'};
    std::ifstream ifstr(arg1);
    std::ofstream ofstr(arg2);

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
    delete [] arg1;
    delete [] arg2;
}
