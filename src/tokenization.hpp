#include <iostream>
#include <string>
#include <vector>
#include <optional>

#pragma once


enum class TokenType{

    exit,
    int_lit,
    semi
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

            while(peek(1).has_value()){

                if(std::isalpha(peek(1).value())){
                    buf.push_back(consume());

                    while(peek(1).has_value() && std::isalnum(peek(1).value())){
                        
                        buf.push_back(consume());

                    };


                    if(buf == "exit"){
                        tokens.push_back({.type = TokenType::exit});

                        buf.clear();
                        continue;
                    } else{
                        std::cerr << "Unknown token: " << buf << std::endl;
                        //exit(1);
                    }
                }
                else if(std::isdigit(peek(1).value())){

                    buf.push_back(consume());
                    while(peek(1).has_value() && std::isdigit(peek(1).value())){

                        buf.push_back(consume());
                    }
                    tokens.push_back({.type = TokenType::int_lit, .value = buf});
                    buf.clear();
                    continue;
                }
                else if (peek(1).value() == ';'){
                    consume();

                    tokens.push_back({.type = TokenType::semi});

                }
                else if (std::isspace(peek(1).value())){
                    consume();
                    continue;
                }
            }
            m_index = 0;
            return tokens;

    };

    private:

        std::optional<char> peek(int offset = 1) const {
            if(m_index + offset > m_src.length()){

                return {};
            } else{
                return m_src.at(m_index);
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