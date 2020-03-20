//
// Created by y2g on 04.02.2020.
//

#include "text.h"

namespace mLab {

    /// Функции

    int from_str_to_int(std::string _s) {
        int res = 0;
        if(_s.length() > 9) return -2; // Big string
        for(int i = 0; i < _s.length(); i++) {
            if(_s[i] >= '0' && _s[i] <= '9')
                res += (_s[i] - '0') * pow(10, _s.length() - 1 - i);
            else
                return -1; // Wrong symbol
        }
        return res;
    }

    int print_err(int error_code) {
        std::string out_str = "Error has occured: ";
        switch(error_code) {
            case 0:
                return 0;
            case 1:
                out_str += "1 - waited \">text\", got other str";
                break;
            case 2:
                out_str += "2 - waited \">replace\", got other str";
                break;
            case 3:
                out_str += "3 - waited \">with\", got other str";
                break;
            case 4:
                out_str += R"(4 - different string-"replace" and string-"with" size)";
                break;
            case 5:
                out_str += "5 - waited \">type\", got other str";
                break;
            case 6:
                out_str += "6 - type should by either 1 or 2";
                break;
            case 7:
                out_str += "7 - input/output file can't be opened";
                break;
            case 8:
                out_str += "8 - incorrect command line! \nUsage: lab.exe [input.txt] [output.txt]";
                break;
            case 9:
                out_str += "9 - waited !<command>, got other str";
                break;
            case 10:
                out_str += "10 - waited \">shift\", got other str";
                break;
            case 11:
                out_str += "11 - got wrong symbol in shift-integer";
                break;
            case 12:
                out_str += "12 - shift-integer is very large";
                break;
            default:
                out_str += "unexpected error.\n";
        }
        std::cout << out_str << std::endl;
        system("pause");
        return error_code;
    }


    void cipher(txt_replacement* _t) {
        std::string *res = new std::string;
        *res = *_t->open_txt;
        for (int i = 0; i < _t->alphabet_length; i++) {
            int temp = 0;
            int pos = 0;
            while (temp != -1 && pos < _t->open_txt->length() && !_t->open_txt->substr(pos).empty()) {
                temp = _t->open_txt->substr(pos).find(_t->mapping[i].first);
                if (temp == -1) break;
                char q = _t->mapping[i].first;
                char w = _t->mapping[i].second;

                (*res)[temp + pos] = _t->mapping[i].second;
                pos += temp + 1;
            }
        }
        _t->cipher_txt = res;
    }
    void cipher(txt_cycle* _t) {
        std::string *res = new std::string;
        *res = *_t->open_txt;
        int _shift = _t->shift % 26;
        for(int i = 0; i < res->length(); i++) {
            bool upper_case = ((*res)[i] >= 'A' && (*res)[i] <= 'Z');
            if(((*res)[i] >= 'a' && (*res)[i] <= 'z') || ((*res)[i] >= 'A' && (*res)[i] <= 'Z')) {
                (*res)[i] += _t->shift;
                if((((*res)[i] < 'a' || (*res)[i] > 'z') && !upper_case)
                   || (((*res)[i] < 'A' || (*res)[i] > 'Z') && upper_case))
                    (*res)[i] -= 26;
            }
        }
        _t->cipher_txt = res;
    }


    void mLab::cipher(txt_digit_repl *_t) {
        int *res = new int[_t->open_txt->length()];
        for (int j = 0; j < _t->open_txt->length(); j++) {
            bool found = false;
            for(int i = 0; i < _t->alphabet_length; i++) {
                if(_t->open_txt->at(j) == _t->mapping[i].first) {
                    res[j] = _t->mapping[i].second;
                    found = true;
                }
            }
            if(!found) {
                res[j] = _t->open_txt->at(j);
            }
        }
        _t->cipher_txt = res;
    }

    int read(std::ifstream *_ifstr, txt_replacement *_t) {
        char *s = new char[255];
        int error_code = 0;
        std::string str;
        std::string _open_text;
        int step = 0;
        char *m_first = nullptr;
        std::pair<char, char> *mapping = nullptr;
        while (!_ifstr->eof() && error_code == 0 && step < 8) {
            _ifstr->getline(s, 255);
            str = s;
            if (s[0] == '/' && s[1] == '/') continue;
            switch (step) {
                case 0:
                    if (str == ">text") step++;
                    else error_code = 1;
                    break;
                case 1:
                    _open_text = str;
                    step++;
                    break;
                case 2:
                    if (str == ">replace") step++;
                    else error_code = 2;
                    break;
                case 3:
                    _t->alphabet_length = str.length();
                    m_first = new char[_t->alphabet_length];
                    for (int i = 0; i < _t->alphabet_length; i++) {
                        m_first[i] = str[i];
                    }
                    step++;
                    break;
                case 4:
                    if (str == ">with") step++;
                    else error_code = 3;
                    break;
                case 5:
                    if (str.length() != _t->alphabet_length) {
                        error_code = 4;
                        break;
                    };
                    mapping = new std::pair<char, char>[_t->alphabet_length];
                    for (int i = 0; i < _t->alphabet_length; i++) {
                        mapping[i].first = m_first[i];
                        mapping[i].second = str[i];
                    }
                    delete[] m_first;
                    m_first = NULL;
                    _t->open_txt = new std::string;
                    _t->open_txt->append(_open_text);
                    _t->mapping = mapping;
                    step++;
                    break;
                case 6:
                    if (str == ">owner info") step++;
                    else error_code = 13;
                    break;
                case 7:
                    _t->owner_info = new std::string;
                    _t->owner_info->append(str);
                    step++;
                    break;
                default:
                    break;
            }
        }
        if (m_first) {
            delete[] m_first;
        }
        if (s) delete[] s;
        if (error_code && mapping) delete[] mapping;
        return error_code;
    }


    int read(std::ifstream *_ifstr, txt_cycle *_t) {
        char *s = new char[255];
        int error_code = 0;
        std::string str;
        std::string _open_text;
        int step = 0;
        int _shift = 0;
        while(!_ifstr->eof() && error_code == 0 && step < 5) {
            _ifstr->getline(s, 255);
            str = s;
            if (s[0] == '/' && s[1] == '/') continue;
            switch (step) {
                case 0:
                    if (str == ">text") step++;
                    else error_code = 1;
                    break;
                case 1:
                    _open_text = str;
                    step++;
                    break;
                case 2:
                    if (str.substr(0, 7) != ">shift ") error_code = 10;
                    _shift = from_str_to_int(str.substr(7));
                    if(_shift == -1) return 11;
                    if(_shift == -2) return 12;
                    _t->open_txt = new std::string;
                    _t->open_txt->append(_open_text);
                    _t->shift = _shift;
                    step++;
                    break;
                case 3:
                    if (str == ">owner info") step++;
                    else error_code = 13;
                    break;
                case 4:
                    _t->owner_info = new std::string;
                    _t->owner_info->append(str);
                    step++;
                    break;
                default:
                    break;
            }
        }
        if(s) delete[] s;
        return error_code;
    }


    int mLab::read(std::ifstream *_ifstr, txt_digit_repl *_t) {
        char *s = new char[255];
        int error_code = 0;
        std::string str, temp_str;
        std::string _open_text;
        int step = 0;
        int index = 0;
        int result = 0;
        char *m_first = nullptr;
        std::pair<char, int> *mapping = nullptr;
        while (!_ifstr->eof() && error_code == 0 && step < 8) {
            _ifstr->getline(s, 255);
            str = s;
            if (s[0] == '/' && s[1] == '/') continue;
            switch (step) {
                case 0:
                    if (str == ">text") step++;
                    else error_code = 1;
                    break;
                case 1:
                    _open_text = str;
                    step++;
                    break;
                case 2:
                    if (str == ">replace") step++;
                    else error_code = 2;
                    break;
                case 3:
                    _t->alphabet_length = (str.length()+1)/2;
                    index = 0;
                    m_first = new char[_t->alphabet_length];
                    for (int i = 0; i < _t->alphabet_length; i++) {
                        m_first[i] = str[index];
                        if(i > 0 && str[index-1] != ',') {
                            error_code = 13;
                            break;
                        }
                        index+=2;
                    }
                    step++;
                    break;
                case 4:
                    if (str == ">with") step++;
                    else error_code = 3;
                    break;
                case 5:
                    mapping = new std::pair<char, int>[_t->alphabet_length];
                    index = 0;
                    while(str.find(',')) {
                        temp_str = str.substr(0, str.find(','));
                        result = from_str_to_int(temp_str);
                        if(result < 0) {
                            error_code = 13;
                            break;
                        }
                        mapping[index].first = m_first[index];
                        mapping[index].second = result;
                        if(str.length() > str.find(','))
                            str = str.substr(str.find(',')+1);
                        else break;
                        index++;
                    }
                    if(str.length() > 0) {
                        result = from_str_to_int(temp_str);
                        if(result < 0) {
                            error_code = 13;
                            break;
                        }
                        mapping[index].first = m_first[index];
                        mapping[index].second = result;
                    }
                    delete[] m_first;
                    m_first = NULL;
                    _t->open_txt = new std::string;
                    _t->open_txt->append(_open_text);
                    _t->mapping = mapping;
                    step++;
                    break;
                case 6:
                    if (str == ">owner info") step++;
                    else error_code = 13;
                    break;
                case 7:
                    _t->owner_info = new std::string;
                    _t->owner_info->append(str);
                    step++;
                    break;
                default:
                    break;
            }
        }
        if (m_first) {
            delete[] m_first;
        }
        if (s) delete[] s;
        if (error_code && mapping) delete[] mapping;
        return error_code;
    }

    void Init(txt_replacement*_t) {
        _t->alphabet_length = 0;
        _t->mapping = nullptr;
        _t->cipher_txt = nullptr;
        _t->open_txt = nullptr;
    }

    void Init(txt_cycle*_t) {
        _t->shift = 0;
        _t->cipher_txt = nullptr;
        _t->open_txt = nullptr;
    }

    void mLab::Init(txt_digit_repl *_t) {
        _t->mapping = nullptr;
        _t->cipher_txt = nullptr;
        _t->open_txt = nullptr;
    }

    std::string int_to_str(int ask) {
        std::string res = "";
        if(ask == 0) return "0";
        while(ask) {
            res = char(ask % 10 + 48) + res;
            ask /= 10;
        }
        return res;
    }

    std::string info_string(txt_replacement *_t) {
        std::string res = "Cipher type: symbol replacement\n";
        res += "Open_text:\n";
        res += *_t->open_txt;
        res += "\nReplace:\n";
        std::string temp = "";
        for(int i = 0; i < _t->alphabet_length; i++) {
            res += _t->mapping[i].first;
            temp += _t->mapping[i].second;
        }
        res += "\nWith:\n";
        res += temp;
        res += "\nCipher text:\n";
        std::string ciph;
        if(!_t->cipher_txt)
            cipher(_t);
        ciph = *_t->cipher_txt;
        res += ciph;
        res += "\nOwner info:\n";
        res += *(_t->owner_info);
        res += "\nOpenText length:\n";
        res += int_to_str(counter_function(_t));
        res += "\n";
        return res;
    }

    std::string info_string(txt_cycle *_t) {
        std::string res = "Cipher type: symbol cycle\n";
        res += "Open_text:\n";
        res += *_t->open_txt;
        res += "\nShift: ";
        int _shift = _t->shift;
        char *temp_shift = new char[16];
        _itoa_s(_shift, temp_shift, 10, 10);
        res += temp_shift;
        res += "\nCipher text:\n";
        std::string ciph;
        if(!_t->cipher_txt)
            cipher(_t);
        ciph = *_t->cipher_txt;
        res += ciph;
        res += "\nOwner info:\n";
        res += *(_t->owner_info);
        res += "\nOpenText length:\n";
        res += int_to_str(counter_function(_t));
        res += "\n";
        return res;
    }

    std::string mLab::info_string(txt_digit_repl *_t) {
        std::string res = "Cipher type: digit replacement\n";
        res += "Open_text:\n";
        res += *_t->open_txt;
        res += "\nReplace:\n";
        std::string temp = "";
        for(int i = 0; i < _t->alphabet_length; i++) {
            res += _t->mapping[i].first;
            int result = _t->mapping[i].second;
            temp += int_to_str(result);
            if(i + 1 != _t->alphabet_length) {
                res += ',';
                temp += ',';
            }
        }
        res += "\nWith:\n";
        res += temp;
        res += "\nCipher text:\n";
        std::string ciph;
        if(!_t->cipher_txt)
            cipher(_t);
        for(int i = 0; i < _t->open_txt->length(); i++) {
            ciph += int_to_str(_t->cipher_txt[i]);
            ciph += ' ';
        }
        res += ciph;
        res += "\nOpenText length:\n";
        res += int_to_str(counter_function(_t));
        res += "\n";
        return res;
    }

    /// Returns error_code:
    /// 0 - no error has occurred
    /// 1 - waited ">text", got other str
    /// 2 - waited ">replace", got other str
    /// 3 - waited ">with", got other str
    /// 4 - different string-"replace" and string-"with" size
    /// 5 - waited ">type", got other str
    /// 6 - type should by either 1 or 2
    /// 9 - waited !<command>, got other str
    int read_from_file(std::ifstream *_ifstr, _mContainer *_c) {
        char *s = new char[255];
        std::string str;
        int operation = -1; // ADD = 0
        int type = 0;
        std::string open_text;
        int map_length = 0;
        int error_code = 0;
        std::pair<char, char> *mapping = nullptr;
        while (!_ifstr->eof() && error_code == 0) {
            _ifstr->getline(s, 255);
            str = s;
            if (s[0] == '/' && s[1] == '/') continue;
            if (str.substr(0, 8) == "!IGNORE ") {
                if (str[8] == '1') _c->ignore = txt_type::REPLACEMENT;
                else if (str[8] == '2') _c->ignore = txt_type::CYCLE;
                else if (str[8] == '3') _c->ignore = txt_type::DIGIT_REPL;
                else {
                    error_code = 6;
                    break;
                }
                continue;
            }
            if (str == "!ADD") {
                operation = 0;
                continue;
            }
            if (operation == 0) {
                if (str.substr(0, 6) == ">type ") {
                    if (str[6] == '1') type = txt_type::REPLACEMENT;
                    else if (str[6] == '2') type = txt_type::CYCLE;
                    else if (str[6] == '3') type = txt_type::DIGIT_REPL;
                    else {
                        error_code = 6;
                        break;
                    }
                } else {
                    error_code = 5;
                    break;
                }
                text *txt = new text;
                txt->type = (txt_type) type;
                txt->next = NULL;
                switch(txt->type) {
                    case txt_type::REPLACEMENT:
                        Init(&txt->u.r);
                        error_code = read(_ifstr, &txt->u.r);
                        break;
                    case txt_type::CYCLE:
                        Init(&txt->u.c);
                        error_code = read(_ifstr, &txt->u.c);
                        break;
                    case txt_type::DIGIT_REPL:
                        Init(&txt->u.d);
                        error_code = read(_ifstr, &txt->u.d);
                        break;
                }

                if (!error_code) append(txt, _c);
                else delete txt;
                operation = -1;
            } else {
                error_code = 9;
            }
        }
        delete[] s;
        return error_code;
    }

    void write_to_file(std::ofstream *_ofstr, _mContainer*_c, int ignore_type) {
        std::string out_str = "";
        if(_c->ignore != -1) ignore_type = _c->ignore;
        sort(_c);
        if(_c->start) {
            for (text *i = _c->start; ; i = i->next) {
                if(ignore_type != 0 && (txt_type)ignore_type == i->type) {
                    if (i == _c->end) break;
                    continue;
                }
                switch(i->type) {
                    case txt_type::REPLACEMENT:
                        out_str += info_string(&i->u.r);
                        break;
                    case txt_type::CYCLE:
                        out_str += info_string(&i->u.c);
                        break;
                    case txt_type::DIGIT_REPL:
                        out_str += info_string(&i->u.d);
                        break;
                }
                out_str += "----------------\n";
                if(i == _c->end) break;
            }
        } else {
            out_str += "Empty container\n";
        }
        _ofstr->write(out_str.c_str(), out_str.length());
    }

    text *text_at(int pos, _mContainer *_c) {
        text *res = _c->start;
        for(int i = 0; i < pos; i++) {
            res = res->next;
        }
        return res;
    }

    bool remove(text *_node, _mContainer*_c) {
        text *prev = _c->start;
        for(text *i = _c->start; i != _c->end; i = i->next) {
            if(i == NULL) return false;
            if(i == _node) {
                prev->next = i->next;
                if(i->type == txt_type::REPLACEMENT) {
                    if(i->u.r.mapping) delete[] i->u.r.mapping;
                }
                delete i;
                return true;
            }
            prev = i;
        }
        return false;
    }

    void append(text *_node, _mContainer*_c) {
        if(_c->start) {
            _c->end->next = _node;
            _node->next = _c->start;
            _c->end = _node;

        } else {
            _node->next = _node;
            _c->start = _c->end = _node;
        }
    }

    void mLab::Init(_mContainer *_c) {
        _c->end = _c->start = NULL;
    }

    int counter_function(txt_replacement *_t) {
        return _t->open_txt->length();
    }


    int counter_function(txt_cycle *_t) {
        return _t->open_txt->length();
    }

    bool comparat(text *_f, text *_s) {
        int l1 = 0, l2 = 0;
        switch (_f->type) {
            case txt_type::CYCLE:
                l1 = counter_function(&_f->u.c);
                break;
            case txt_type::REPLACEMENT:
                l1 = counter_function(&_f->u.r);
                break;
            case txt_type::DIGIT_REPL:
                l1 = counter_function(&_f->u.d);
            default:
                break;
        }

        switch (_s->type) {
            case txt_type::CYCLE:
                l2 = counter_function(&_s->u.c);
                break;
            case txt_type::REPLACEMENT:
                l2 = counter_function(&_s->u.r);
                break;
            case txt_type::DIGIT_REPL:
                l2 = counter_function(&_s->u.d);
            default:
                break;
        }
        if(l1 > l2)
            std::cout << l1 << ">" << l2 << std::endl;
        else std::cout << l1 << "<=" << l2 << std::endl;
        return l1 > l2;
    }

    void sort(_mContainer *cont) {
        for(text* i = cont->start; i != cont->end; i = i->next) {
            for(text* j = i->next; j != cont->start; j = j->next) {
                if(comparat(i, j)) {
                    auto q = i->u;
                    i->u = j->u;
                    j->u = q;
                    txt_type w = i->type;
                    i->type = j->type;
                    j->type = w;
                }
            }
        }
    }

    int mLab::counter_function(txt_digit_repl *_t) {
        return _t->open_txt->length();
    }

}