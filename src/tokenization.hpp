#include <iostream>
#include <string>
#include <vector>
#include <optional>

#pragma once


enum class TokenType{

    exit,
    int_lit,
    semi,
    open_paren,
    close_paren,
    ident,
    let,
    equals
};

struct Token {
    TokenType type;
    std::optional<std::string> value;
};


class Tokenizer{

    public:
        inline explicit Tokenizer(std::string src)
            : m_src(std::move(src))

        {

        }


        std::vector<Token> Tokenize(){
            
            std::string buf;
            std::vector<Token>  tokens;

            while(peek().has_value()){

                if(std::isalpha(peek().value())){
                    buf.push_back(consume());

                    while(peek().has_value() && std::isalnum(peek().value())){
                        
                        buf.push_back(consume());

                    };
                    if(buf == "exit"){
                        tokens.push_back({.type = TokenType::exit, .value = "exit"});

                        buf.clear();
                        continue;
                    }
                    if(buf == "let"){
                        tokens.push_back({.type = TokenType::let, .value = "let"});
                        buf.clear();
                        continue;
                    } else{
                        tokens.push_back({.type = TokenType::ident, .value = buf});
                        buf.clear();
                        continue;
                    }
                }
                else if(std::isdigit(peek().value())){

                    buf.push_back(consume());
                    while(peek().has_value() && std::isdigit(peek().value())){

                        buf.push_back(consume());
                    }
                    tokens.push_back({.type = TokenType::int_lit, .value = buf});
                    buf.clear();
                    continue;
                }
                else if (peek().value() == ';'){
                    consume();

                    tokens.push_back({.type = TokenType::semi});

                }
                else if (peek().value() == '='){
                    consume();

                    tokens.push_back({.type = TokenType::equals});

                }
                else if (std::isspace(peek().value())){
                    consume();
                    continue;
                } else if(peek().value() == '('){
                    consume();
                    tokens.push_back({.type = TokenType::open_paren});
                } else if(peek().value() == ')'){
                    consume();
                    tokens.push_back({.type = TokenType::close_paren});
                }
            }
            m_index = 0;

            for(int i = 0; i < tokens.size(); i++){
            }
            return tokens;

    };

    private:

        std::optional<char> peek(int offset = 0) const {
            if(m_index + offset >= m_src.length()){

                return {};
            } else{
                return m_src.at(m_index + offset);
            }
        }

        char consume(){
            int val = m_index;
            m_index++;
            return m_src.at(val);
            
        }


        const std::string m_src;
        int m_index = 0;

};