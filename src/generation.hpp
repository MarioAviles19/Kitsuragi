#pragma once


#include <iostream>
#include <sstream>
#include <unordered_map>
#include "./parser.hpp"


class Generator {

    public:

        inline Generator(Node_Prog prog)
        : m_prog(std::move(prog))
        {
        }

        void gen_expr(const Node_Expr& expr){

            

            struct ExprVisitor{
                
                Generator* gen;

                void operator()(const Node_Expr_IntLit& expr_int_lit) const{
                    gen->m_output << "    mov rax," << expr_int_lit.int_lit.value.value() << std::endl;
                    gen->push("rax");
                }
                void operator()(const Node_Expr_Ident& expr_ident){
                    if(!gen->m_vars.contains(expr_ident.ident.value.value())){
                        std::cerr << "Use of undeclared identifier: " << expr_ident.ident.value.value() << std::endl;
                    }

                    const auto& var = gen->m_vars.at(expr_ident.ident.value.value());

                    std::stringstream offset;

                    offset << "QWORD [rsp + " << (gen->m_stack_size - var.stack_loc - 1) * 8  << "]" << std::endl;



                    gen->push(offset.str());
                }
            };

            ExprVisitor visitor {.gen = this};
            std::visit(visitor, expr.var);

        }

        void gen_stmt(const Node_Stmt& stmt) {



            struct StmtVisitor {
                Generator* gen;

                void operator()(const Node_Stmt_Exit& stmt_exit) const{
                    gen->gen_expr(stmt_exit.expr);
                    gen->m_output << "    mov rax, 60" << std::endl;
                    gen->pop("rdi");
                    gen->m_output << "    syscall" << std::endl;
                }
                void operator()(const Node_Stmt_Let& stmt_let){

                    if(gen->m_vars.contains(stmt_let.ident.value.value())){
                        std::cerr << "Identifier already used: " << stmt_let.ident.value.value() << std::endl;
                        exit(1);
                    }

                    gen->m_vars.insert({stmt_let.ident.value.value(), Var {.stack_loc = gen->m_stack_size}});
                    gen->gen_expr(stmt_let.expr);



                }
            };
            StmtVisitor visitor {.gen = this};
            std::visit(visitor,stmt.var);

        }
        std::string gen_prog(){
            
            std::stringstream output;
            m_output << "global _start\n_start:\n";


            for (const Node_Stmt& stmt : m_prog.statments){
                gen_stmt(stmt);
            }


            m_output << "    mov rax, 60" << std::endl;
            m_output << "    mov rdi, 0" << std::endl;
            m_output << "    syscall";

            return m_output.str();
        }
    private:


        void push(const std::string& reg){
            m_output << "    push " << reg << std::endl;
            m_stack_size++;
        }
        void pop(const std::string& reg){
            m_output << "    pop " << reg << std::endl;
            m_stack_size--;
        }

        struct Var {
            size_t stack_loc;
            //TODO add type;
        };

        const Node_Prog m_prog;
        std::stringstream m_output;
        size_t m_stack_size = 0;
        std::unordered_map<std::string, Var> m_vars {};


};