#include <bits/stdc++.h>
using namespace std;

// Tokenization
enum class TokenType {
    exit,
    int_lit,
    semi,
    open_paren,
    close_paren,
    ident,
    let,
    eq,
    plus,
    star,
    minus,
    fslash,
    open_curly,
    close_curly,
    if_,
    elif,
    else_,
};

inline std::string to_string(const TokenType type)
{
    switch (type) {
    case TokenType::exit:
        return "`exit`";
    case TokenType::int_lit:
        return "int literal";
    case TokenType::semi:
        return "`;`";
    case TokenType::open_paren:
        return "`(`";
    case TokenType::close_paren:
        return "`)`";
    case TokenType::ident:
        return "identifier";
    case TokenType::let:
        return "`let`";
    case TokenType::eq:
        return "`=`";
    case TokenType::plus:
        return "`+`";
    case TokenType::star:
        return "`*`";
    case TokenType::minus:
        return "`-`";
    case TokenType::fslash:
        return "`/`";
    case TokenType::open_curly:
        return "`{`";
    case TokenType::close_curly:
        return "`}`";
    case TokenType::if_:
        return "`if`";
    case TokenType::elif:
        return "`elif`";
    case TokenType::else_:
        return "`else`";
    }
    assert(false);
}

// inline std::optional<int> bin_prec(const TokenType type)
// {
//     switch (type) {
//     case TokenType::minus:
//     case TokenType::plus:
//         return 0;
//     case TokenType::fslash:
//     case TokenType::star:
//         return 1;
//     default:
//         return {};
//     }
// }

struct Token {
    TokenType type;
    int line;
    std::optional<std::string> value {};
};

std::vector<Token> tokenize(std::string s)
{
    std::vector<Token> tokens;
    std::string buf;
    int line_count = 1;
    int n = s.size();
    int i = 0;

    while (i < n) {
        if (std::isalpha(s[i])) {
            buf.push_back(s[i]);
            i++;
            while (i < n && std::isalnum(s[i])) {
                buf.push_back(s[i]);
                i++;
            }
            if (buf == "exit") {
                tokens.push_back({ TokenType::exit, line_count });
                buf.clear();
            }
            else if (buf == "let") {
                tokens.push_back({ TokenType::let, line_count });
                buf.clear();
            }
            else if (buf == "if") {
                tokens.push_back({ TokenType::if_, line_count });
                buf.clear();
            }
            else if (buf == "elif") {
                tokens.push_back({ TokenType::elif, line_count });
                buf.clear();
            }
            else if (buf == "else") {
                tokens.push_back({ TokenType::else_, line_count });
                buf.clear();
            }
            else {
                tokens.push_back({ TokenType::ident, line_count, buf });
                buf.clear();
            }
        }
        else if (std::isdigit(s[i])) {
            buf.push_back(s[i]);
            i++;
            while (i < n && std::isdigit(s[i])) {
                buf.push_back(s[i]);
                i++;
            }
            tokens.push_back({ TokenType::int_lit, line_count, buf });
            buf.clear();
        }
        else if (s[i] == '/' && i + 1 < n && s[i + 1] == '/') {
            i += 2;
            while (i < n && s[i] != '\n') {
                i++;
            }
        }
        else if (s[i] == '/' && i + 1 < n && s[i + 1] == '*') {
            i += 2;
            while (i < n) {
                if (s[i] == '*' && i + 1 < n && s[i + 1] == '/') {
                    break;
                }
                i++;
            }
            if (i < n) {
                i += 2; // Skip the closing */
            }
        }
        else if (s[i] == '(') {
            i++; // consume
            tokens.push_back({ TokenType::open_paren, line_count });
        }
        else if (i < n && s[i] == ')') {
            i++; // consume
            tokens.push_back({ TokenType::close_paren, line_count });
        }
        else if (i < n && s[i] == ';') {
            i++; // consume
            tokens.push_back({ TokenType::semi, line_count });
        }
        else if (i < n && s[i] == '=') {
            i++; // consume
            tokens.push_back({ TokenType::eq, line_count });
        }
        else if (i < n && s[i] == '+') {
            i++; // consume
            tokens.push_back({ TokenType::plus, line_count });
        }
        else if (i < n && s[i] == '*') {
            i++; // consume
            tokens.push_back({ TokenType::star, line_count });
        }
        else if (i < n && s[i] == '-') {
            i++; // consume
            tokens.push_back({ TokenType::minus, line_count });
        }
        else if (i < n && s[i] == '/') {
            i++; // consume
            tokens.push_back({ TokenType::fslash, line_count });
        }
        else if (i < n && s[i] == '{') {
            i++; // consume
            tokens.push_back({ TokenType::open_curly, line_count });
        }
        else if (i < n && s[i] == '}') {
            i++; // consume
            tokens.push_back({ TokenType::close_curly, line_count });
        }
        else if (i < n && s[i] == '\n') {
            i++; // consume
            line_count++;
        }
        else if (i < n && std::isspace(s[i])) {
            i++; // consume
        }
        else {
            std::cerr << "Invalid token" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    return tokens;
}

// Parsing
struct NodeExpr {
    Token int_lit;
};
struct NodeExit {
    NodeExpr expr;
};

class Parser { };
std::optional<NodeExpr> parse_expr(Token token)
{

    if (token.type == TokenType::int_lit) {
        // cout<<token.value.value()<<endl;
        return NodeExpr { .int_lit = token };
    }
    else
        return {};
}
std::optional<NodeExit> parse(std::vector<Token>& tokens)
{

    int i = 0;
    int n = tokens.size();
    std::optional<NodeExit> exit_node;
    while (i < n) {
        if (i < n && tokens[i].type == TokenType::exit) {
            i++;
            if (i < n) {
                auto node_expr = parse_expr(tokens[i]);
                exit_node = NodeExit { .expr = node_expr.value() };
                i++;
            }
        }
        else {
            std::cerr << "Invalid expression" << std::endl;
            exit(EXIT_FAILURE);
        }
        if ((i >= n) || (tokens[i].type != TokenType::semi)) {
            cout << "Error" << endl;
        };
        i++;
    }

    // if (exit_node.has_value()) {
    //     std::cout << exit_node.value().expr.int_lit.value.value() << std::endl;
    // }

    return exit_node;
}

int main()
{
    std::string s = "exit 45;";

    std::vector<Token> tokens = tokenize(s);
    for (auto token : tokens) {
        cout << to_string(token.type) << " " << (token.value.has_value() ? token.value.value() : "NULL") << endl;
    }
    if (parse(tokens)) {
        auto val = parse(tokens);
        if(val.has_value()){
        std::cout << val.value().expr.int_lit.value.value() << std::endl;
        }
    }
    return 0;
}
