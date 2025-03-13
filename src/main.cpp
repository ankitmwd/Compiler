#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <optional>
#include <cstdlib> // For system()

enum class TokenType {
    _return,
    int_lit,
    semi
};

struct Token {
    TokenType type;
    std::optional<std::string> value;
};

std::vector<Token> tokenize(const std::string& str) {
    std::string buf;
    std::vector<Token> tokens;
    for (int i = 0; i < str.size(); i++) {
        char c = str[i];
        if (std::isalpha(c)) {
            buf.push_back(c);
            i++;
            while (std::isalnum(str[i])) {
                buf.push_back(str[i]);
                i++;
            }
            i--;
            if (buf == "return") {
                tokens.push_back({TokenType::_return});
                buf.clear();
                continue;
            } else {
                std::cerr << "Unknown token: " << buf << std::endl;
                exit(EXIT_FAILURE);
            }
        } else if (std::isdigit(c)) {
            buf.push_back(c);
            i++;
            while (std::isdigit(str[i])) {
                buf.push_back(str[i]);
                i++;
            }
            i--;
            tokens.push_back({TokenType::int_lit, buf});
            buf.clear();
        } else if (c == ';') {
            tokens.push_back({TokenType::semi});
        } else if (std::isspace(c)) {
            continue;
        }
    }
    return tokens;
}

std::string token_to_asm(const std::vector<Token>& tokens) {
    std::stringstream output;
    output << "global _start\n_start:\n";
    for (int i = 0; i < tokens.size(); i++) {
        const Token& token = tokens[i];
        if (token.type == TokenType::_return) {
            if (i + 1 < tokens.size() && tokens[i + 1].type == TokenType::int_lit) {
                if (i + 2 < tokens.size() && tokens[i + 2].type == TokenType::semi) {
                    output << "   mov rax, 60\n";
                    output << "   mov rdi, " << tokens[i + 1].value.value() << "\n";
                    output << "   syscall\n";
                }
            }
        }
    }
    return output.str();
}

int main(int argc, char *argv[]) {
    // the first argument is always the executable
    if (argc != 2) {
        std::cerr << "Incorrect usage" << std::endl;
        return EXIT_FAILURE;
    }
    std::string contents;
    {
        std::stringstream contents_stream;
        std::fstream input(argv[1], std::ios::in);
        if (!input.is_open()) {
            std::cerr << "Failed to open file: " << argv[1] << std::endl;
            return EXIT_FAILURE;
        }
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }
    std::vector<Token> tokens = tokenize(contents);
    std::string asm_code = token_to_asm(tokens);
    std::cout << asm_code << std::endl; // Print the generated assembly code
    {
        std::fstream file("out.asm", std::ios::out);
        if (!file.is_open()) {
            std::cerr << "Failed to create file: out.asm" << std::endl;
            return EXIT_FAILURE;
        }
        file << asm_code;
        std::cout << "Assembly code written to out.asm" << std::endl;
    }

    // Run NASM and LD commands
    int ret = system("nasm -f elf64 out.asm");
    std::cout << "NASM command exit status: " << ret << std::endl;
    if (ret != 0) {
        std::cerr << "NASM command failed" << std::endl;
        return EXIT_FAILURE;
    }

    ret = system("ld -o out out.o");
    std::cout << "LD command exit status: " << ret << std::endl;
    if (ret != 0) {
        std::cerr << "LD command failed" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}