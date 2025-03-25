#pragma once

#include "parser.hpp"
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <variant> // Ensure compatibility for std::visit

class Generator {
public:
    inline explicit Generator(NodeProg prog)
        : m_prog(std::move(prog))
    {
    }

    void gen_expr(const NodeExpr& expr)
    {
        struct ExprVisitor {
            Generator* gen;

            void operator()(const NodeExprIntLit& expr_int_lit) const
            {
                if (!expr_int_lit.int_lit.value) {
                    std::cerr << "Invalid integer literal" << std::endl;
                    exit(EXIT_FAILURE);
                }
                gen->m_output << "    mov rax, " << expr_int_lit.int_lit.value.value() << "\n";
                gen->push("rax");
            }

            void operator()(const NodeExprIdent& expr_ident) const
            {
                if (!expr_ident.ident.value) {
                    std::cerr << "Invalid identifier" << std::endl;
                    exit(EXIT_FAILURE);
                }
                std::string ident_name = expr_ident.ident.value.value();

                if (gen->m_vars.find(ident_name) == gen->m_vars.end()) {
                    std::cerr << "Undeclared identifier: " << ident_name << std::endl;
                    exit(EXIT_FAILURE);
                }

                const auto& var = gen->m_vars.at(ident_name);
                std::stringstream offset;
                offset << "QWORD [rsp + " << (gen->m_stack_size - var.stack_loc - 1) * 8 << "]";
                gen->push(offset.str());
            }
        };

        ExprVisitor visitor { .gen = this };
        std::visit(visitor, expr.var);
    }

    void gen_stmt(const NodeStmt& stmt)
    {
        struct StmtVisitor {
            Generator* gen;

            void operator()(const NodeStmtExit& stmt_exit) const
            {
                gen->gen_expr(stmt_exit.expr);
                gen->m_output << "    mov rax, 60\n"; // syscall: exit
                gen->pop("rdi");
                gen->m_output << "    syscall\n";
            }

            void operator()(const NodeStmtLet& stmt_let) const
            {
                if (!stmt_let.ident.value) {
                    std::cerr << "Invalid identifier" << std::endl;
                    exit(EXIT_FAILURE);
                }
                std::string ident_name = stmt_let.ident.value.value();

                if (gen->m_vars.find(ident_name) != gen->m_vars.end()) {
                    std::cerr << "Identifier already used: " << ident_name << std::endl;
                    exit(EXIT_FAILURE);
                }

                gen->m_vars.insert({ ident_name, Var { .stack_loc = gen->m_stack_size } });
                gen->gen_expr(stmt_let.expr);
            }
        };

        StmtVisitor visitor { .gen = this };
        std::visit(visitor, stmt.var);
    }

    [[nodiscard]] std::string gen_prog()
    {
        m_output << "global _start\n_start:\n";

        for (const NodeStmt& stmt : m_prog.stmts) {
            gen_stmt(stmt);
        }

        m_output << "    mov rax, 60\n";
        m_output << "    mov rdi, 0\n";
        m_output << "    syscall\n"; // syscall: exit(0)
        return m_output.str();
    }

private:
    void push(const std::string& reg)
    {
        m_output << "    push " << reg << "\n";
        m_stack_size++;
    }

    void pop(const std::string& reg)
    {
        m_output << "    pop " << reg << "\n";
        m_stack_size--;
    }

    struct Var {
        size_t stack_loc;
    };

    const NodeProg m_prog;
    std::stringstream m_output;
    size_t m_stack_size = 0;
    std::unordered_map<std::string, Var> m_vars {};
};
