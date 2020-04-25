//19081999 - 7,3,1,1
#include "text.h"
#include <gtest/gtest.h>
using namespace mLab;

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, 0);
    char test_arg[] = "-unit_tests";
    if(!strcmp(argv[1], test_arg)) {
        std::cout << "Running tests..." << std::endl;
        testing::InitGoogleTest();
        return RUN_ALL_TESTS();
    } else {
        char *out_stream = nullptr;
        if (argc < 2 || argc > 3) return print_err(8);
        if (argc == 2) { // Если не указан output файл, выводим в стандартный файл
            out_stream = new char[11]{'o', 'u', 't', 'p', 'u', 't', '.', 't', 'x', 't', '\0'};
        } else if (argc == 3) {
            out_stream = argv[2];
        }
        std::ifstream ifstr(argv[1]);
        std::ofstream ofstr(out_stream);
        if (ifstr.bad() || ifstr.fail() || ofstr.bad() || ofstr.fail()) { // Если проблемы с файлом
            return print_err(7);
        }
        std::cout << "Program started" << std::endl;
        _mContainer container;
        Init(&container);
        print_err(read_from_file(&ifstr, &container));
        write_to_file(&ofstr, &container);
        return 0;
    }
}
