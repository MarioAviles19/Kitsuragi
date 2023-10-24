#include <vector>
#include <optional>
#include <variant>

#include "./tokenization.hpp"
#include "./arena.hpp"

#pragma once

    struct Node_Expr;

    struct Node_Expr_IntLit{
        Token int_lit;
    };
    struct Node_Expr_Ident{
        Token ident;
    };
    struct Bin_Expr_Multi {
        Node_Expr* lhs;
        Node_Expr* rhs;
    };
    struct Bin_Expr_Add{
        Node_Expr* lhs;
        Node_Expr* rhs;
    };
    struct Node_Bin_Expr {
        std::variant<Bin_Expr_Multi*, Bin_Expr_Add*> var;
    };

    struct Node_Stmt_Exit{
        Node_Expr* expr;
    };
    struct Node_Stmt_Print{
        Node_Expr* expr;
    };

    struct Node_Stmt_Let{
        Token ident;
        Node_Expr* expr;
    };

    struct Node_Stmt{
        std::variant<Node_Stmt_Exit*, Node_Stmt_Let*, Node_Stmt_Print*> var;
    };

    struct Node_Prog{
        std::vector<Node_Stmt*> statments;
    };

    struct Node_Expr {
        std::variant<Node_Expr_IntLit*, Node_Expr_Ident*, Node_Bin_Expr*> var;

    };


class Parser{

    public:
        inline explicit Parser(std::vector<Token> tokens)
        : m_tokens(std::move(tokens)),
        m_allocator(1024 * 1024 * 4) //4mb
        {
        }


        std::optional<Node_Expr*> parse_expr(){

            if(peek().has_value() && peek().value().type == TokenType::int_lit){
                auto expr_int_lit = m_allocator.alloc<Node_Expr_IntLit>();

                expr_int_lit->int_lit = consume();
                auto expr = m_allocator.alloc<Node_Expr>();
                expr->var = expr_int_lit;
                return expr;
            } else if(peek().has_value() && peek().value().type == TokenType::ident){

                auto expr_ident = m_allocator.alloc<Node_Expr_Ident>();

                expr_ident->ident = consume();
                auto expr = m_allocator.alloc<Node_Expr>();

                expr->var = expr_ident;

                return expr;
            }
             else{
                return {};
            }
        }

        std::optional<Node_Stmt*> parse_stmt(){


            if(peek().value().type == TokenType::exit && peek(1).has_value() && peek(1).value().type == TokenType::open_paren){
                //Consume the exit
                consume();
                //Consume the open_paren
                consume();

                auto stmt_exit = m_allocator.alloc<Node_Stmt_Exit>();


                if(auto node_expr = parse_expr()){

                    stmt_exit->expr = node_expr.value();
                
                } else {
                    std::cerr << "Invalid expression" << std::endl;
                    exit(1);
                }
                if(peek().has_value() && peek().value().type == TokenType::close_paren){
                    consume();
                } else{
                    std::cerr << "Expected ')'" << std::endl;
                }

                if(peek().has_value() && peek().value().type == TokenType::semi){
                    
                    consume();
                    
                } else{
                    std::cerr << "Expected ';'" << std::endl;
                    exit(1);
                }

                auto stmt = m_allocator.alloc<Node_Stmt>();
                stmt->var = stmt_exit;

                return stmt;
            } else if (peek().has_value() && peek().value().type == TokenType::let && peek(1).has_value() && peek(1).value().type == TokenType::ident && peek(2).has_value() && peek(2).value().type == TokenType::equals){
                //eat the 'let'
                consume();
                //eat the identifier
                auto stmt_let = m_allocator.alloc<Node_Stmt_Let>();
                stmt_let->ident = consume();
                //eat the '='
                consume();
                if(auto expr = parse_expr()){
                    stmt_let->expr = expr.value();
                } else{
                    std::cerr << "Invalid expression" << std::endl;
                    exit(1);
                }
                if(peek().has_value() && peek().value().type == TokenType::semi){
                    consume();
                } else{
                    std::cerr << "Expected ';'" << std::endl;
                    exit(1);
                }
                
                auto stmt = m_allocator.alloc<Node_Stmt>();
                stmt->var = stmt_let;

                return stmt;
            } else if(peek().value().type == TokenType::print && peek(1).has_value() && peek(1).value().type == TokenType::open_paren){
                //Consume the print
                consume();
                //Consume the open_paren
                consume();
                auto stmt_print = m_allocator.alloc<Node_Stmt_Print>();
                if(auto node_expr = parse_expr()){

                    stmt_print->expr = node_expr.value();
                
                } else {
                    std::cerr << "Invalid expression" << std::endl;
                    exit(1);
                }
                if(peek().has_value() && peek().value().type == TokenType::close_paren){
                    consume();
                } else{
                    std::cerr << "Expected ')'" << std::endl;
                }

                if(peek().has_value() && peek().value().type == TokenType::semi){
                    
                    consume();
                    
                } else{
                    std::cerr << "Expected ';'" << std::endl;
                    exit(1);
                }

                auto stmt = m_allocator.alloc<Node_Stmt>();
                stmt->var = stmt_print;

                return stmt;

            }
            
            else{
                return {};
            }

        }

        std::optional<Node_Prog> parse_prog(){
            
            Node_Prog prog;
            
            int i;
            while(peek().has_value()){
                
                if(auto stmt = parse_stmt()){
                    prog.statments.push_back(stmt.value());
                } else{


                    std::cerr << "Invalid statement" << std::endl;
                    exit(1);
                }
                i++;
            }
            return prog;
        }

    private:

        inline std::optional<Token> peek(int offset = 0) const{

            if(m_index + offset >= m_tokens.size()){
                return {};
            } else {
                return m_tokens.at(m_index + offset);
            }
        }

        inline Token consume()
        {
            return m_tokens.at(m_index++);
        }

        const std::vector<Token> m_tokens;

        size_t m_index = 0;
        ArenaAllocator m_allocator;
};