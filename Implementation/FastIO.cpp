#include <bits/stdc++.h>

using ll = long long;

// call IO::init() at the start, and call
// IO::_flush_output() at the end.
namespace IO {
    const int BUFFER_SIZE = 1 << 15;
 
    char input_buffer[BUFFER_SIZE];
    int input_pos = 0, input_len = 0;
 
    char output_buffer[BUFFER_SIZE];
    int output_pos = 0;
 
    char number_buffer[100];
    uint8_t lookup[100];
 
    void _update_input_buffer() {
        input_len = std::fread(input_buffer, sizeof(char), BUFFER_SIZE, stdin);
        input_pos = 0;
        if (input_len == 0) { input_buffer[0] = EOF; }
    }
 
    inline char next_char(bool advance = true) {
        if (input_pos >= input_len) { _update_input_buffer(); }
        return input_buffer[advance ? input_pos++ : input_pos];
    }
    
    inline void read_char(char &val) {
        while (std::isspace(val = next_char()));
    }

    inline void read_string(std::string &val) {
        char ch;
        read_char(ch);
        do {
            val.push_back(ch);
        } while (!std::isspace(ch = next_char()));
    }

    template<typename T> 
    inline void read_int(T &number) {
        bool negative = false;
        number = 0;
 
        while (!std::isdigit(next_char(false))) {
            if (next_char() == '-') { negative = true; }
        }

        do {
            number = 10 * number + (next_char() - '0');
        } while (std::isdigit(next_char(false)));
 
        if (negative) { number = -number; }
    }
 
    template<typename T, typename... Args> 
    inline void read_int(T &number, Args &... args) {
        read_int(number);
        read_int(args...);
    }
 
    void _flush_output() {
        std::fwrite(output_buffer, sizeof(char), output_pos, stdout);
        output_pos = 0;
    }
 
    inline void write_char(char c) {
        if (output_pos == BUFFER_SIZE) { _flush_output(); }
        output_buffer[output_pos++] = c;
    }

    inline void write_string(const std::string &val) {
        for (char i : val) {
            write_char(i);
        }
    }
 
    template<typename T>
    inline void write_int(T number, char after = '\0') {
        if (number < 0) {
            write_char('-');
            number = -number;
        }

        int length = 0;
 
        while (number >= 10) {
            uint8_t lookup_value = lookup[number % 100];
            number /= 100;
            number_buffer[length++] = (lookup_value & 15) + '0';
            number_buffer[length++] = (lookup_value >> 4) + '0';
        }
 
        if (number != 0 || length == 0) { 
            write_char(number + '0');
        }
 
        for (int i = length - 1; i >= 0; i--) {
            write_char(number_buffer[i]);
        }
 
        if (after) { write_char(after); }
    }
 
    void init() {
        bool exit_success = atexit(_flush_output) == 0;
        assert(exit_success);
 
        for (int i = 0; i < 100; i++)
            lookup[i] = (i / 10 << 4) + i % 10;
    }
}
