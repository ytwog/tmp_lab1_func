//
// Created by y2g on 04.02.2020.
//

#ifndef LAB1_TEXT_H
#define LAB1_TEXT_H
#include <string>
#include <iostream>
#include <fstream>
#include <locale>
#include <Windows.h>

namespace mLab {
    /// Струтуры
    struct txt_replacement;
    struct txt_cycle;
    struct txt_digit_repl;
    struct text;
    struct _mContainer;

    /// Функции
    // Вывод ошибки по коду error_code
    int print_err(int error_code);
    // Класс текста с заменами

    // Шифрует открытый текст в шифротекст
    void cipher(txt_replacement*);
    void cipher(txt_cycle*);
    void cipher(txt_digit_repl*);

    // Возвращает строку, содержащую информацию про текст и шифр
    std::string info_string(txt_replacement*);
    std::string info_string(txt_cycle*);
    std::string info_string(txt_digit_repl*);

    // Считывает с потока строки и преобразовывает их в поля класса
    int read(std::ifstream*, txt_replacement*);
    int read(std::ifstream*, txt_cycle*);
    int read(std::ifstream*, txt_digit_repl*);

    void Init(txt_replacement*);
    void Init(txt_cycle*);
    void Init(txt_digit_repl*);
    void Init(_mContainer*);

    void write_to_file(std::ofstream *_ofstr, _mContainer *);
    int read_from_file(std::ifstream *_ifstr, _mContainer *);

    text *text_at(int pos, _mContainer *);
    bool remove(text *_node, _mContainer*);
    void append(text *_node, _mContainer*);
    /// Перечисление типов текста
    enum txt_type {
        REPLACEMENT = 1,
        CYCLE = 2,
        DIGIT_REPL = 3
    };

    struct txt_replacement {
        int alphabet_length;
        std::pair<char, char> *mapping;
        std::string *cipher_txt;
        std::string *open_txt;
        std::string *owner_info;
    };

    // Класс текста со сдвигом
    struct txt_cycle{
        int shift;
        std::string *cipher_txt;
        std::string *open_txt;
        std::string *owner_info;
    };

    struct txt_digit_repl{
        int alphabet_length;
        std::pair<char, int> *mapping;
        int *cipher_txt;
        std::string *open_txt;
        std::string *owner_info;
    };

    // Класс для объединения текстов
    struct text {
        union {
            txt_replacement r;
            txt_cycle c;
            txt_digit_repl d;
        };
        txt_type type;
        text *next;
    };

    // Контейнер - однонаправленный цикличный список
    struct _mContainer {
        text *start;
        text *end;
    };

}
#endif //LAB1_TEXT_H
