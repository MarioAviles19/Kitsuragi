#include <vector>
#include <optional>
#include <variant>

#include "./tokenization.hpp"


#pragma once


    struct Node_Expr_IntLit{
        Token int_lit;
    };
    struct Node_Expr_Ident{
        Token ident;
    };

    struct Node_Expr {
        std::variant<Node_Expr_IntLit, Node_Expr_Ident> var;

    };

    struct Node_Stmt_Exit{
        Node_Expr expr;
    };

    struct Node_Stmt_Let{
        Token ident;
        Node_Expr expr;
    };

    struct Node_Stmt{
        std::variant<Node_Stmt_Exit, Node_Stmt_Let> var;
    };

    struct Node_Prog{
        std::vector<Node_Stmt> statments;
    };




class Parser{

    public:
        inline explicit Parser(std::vector<Token> tokens)
        : m_tokens(std::move(tokens))

        {
        }


        std::optional<Node_Expr> parse_expr(){

            if(peek().has_value() && peek().value().type == TokenType::int_lit){
                
                return Node_Expr{.var = Node_Expr_IntLit{.int_lit = consume()}};
            } else if(peek().has_value() && peek().value().type == TokenType::ident){
                return Node_Expr {.var = Node_Expr_Ident {.ident = consume()}};
            }
             else{
                return {};
            }
        }

        std::optional<Node_Stmt> parse_stmt(){


            if(peek().value().type == TokenType::exit && peek(1).has_value() && peek(1).value().type == TokenType::open_paren){
                //Consume the exit
                consume();
                //Consume the open_paren
                consume();
                Node_Stmt_Exit stmt_exit;
                if(auto node_expr = parse_expr()){

                    stmt_exit = {.expr = node_expr.value()};
                
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
                return Node_Stmt{.var = stmt_exit};
            } else if (peek().has_value() && peek().value().type == TokenType::let && peek(1).has_value() && peek(1).value().type == TokenType::ident && peek(2).has_value() && peek(2).value().type == TokenType::equals){
                //eat the 'let'
                consume();
                //eat the identifier
                auto stmt_let = Node_Stmt_Let{.ident = consume()};
                //eat the '='
                consume();
                if(auto expr = parse_expr()){
                    stmt_let.expr = expr.value();
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

                return Node_Stmt {.var = stmt_let};
            } else{
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
};