#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


#include "./tokenization.hpp"



std::vector<Token> Tokenize(const std::string& str){

    std::string buf;
    std::vector<Token>  tokens;

    for (int i = 0; i < str.length(); i++){
        char c = str.at(i);

        if(std::isalpha(c)){
            buf.push_back(c);
            i++;
            while (std::isalnum(str.at(i))){
                buf.push_back(str.at(i));
                i++;
            }

            i--;
            //Check for token
            if(buf == "exit"){
                Token token = {.type = TokenType::exit};
                tokens.push_back({.type = TokenType::exit, .value = "return"});
            }  else {
                std::cerr << "Unknown token " << buf << std::endl;
                exit(1);
            }
                buf.clear();
        } else if(std::isdigit(c)){
            buf.push_back(c);
            i++;
            while (std::isdigit(str.at(i))){
                buf.push_back(str.at(i));
                i++;
            }
            i--;

            tokens.push_back({.type = TokenType::int_lit, .value = buf});
            buf.clear();

        } else if(c == ';'){
            tokens.push_back({.type = TokenType::semi, .value = "semi"});
        } 
        else if(std::isspace(c)){
            continue;
        }
    }

    
    return tokens;

}

int main(int argc, char* argv[]){


    std::cout << argc << std::endl;

    if(argc != 2){
        std::cerr << "Incorrect usage. Correct usage is..." << std::endl;
        std::cerr << "kitsuragi <input.kim>" << std::endl;

        
        return 1;
    }



    std::stringstream contents_stream;
    //Own scope to invoke destructor. Negating the need to use input.close()
    {
    std::fstream input(argv[1], std::ios::in);
    contents_stream << input.rdbuf();
    }

    std::string contents = contents_stream.str();


    std::vector<Token> tokens = Tokenize(contents);

    for(int i = 0; i < tokens.size(); i++){
        std::cout << tokens[i].value << std::endl;
    }

    return 3;
}