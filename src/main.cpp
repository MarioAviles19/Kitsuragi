#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

enum class TokenType{

    _return,
    int_lit,
    semi
};

struct Token {
    TokenType type;
    std::string value;
};

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

            if(buf == "return"){
                Token token = {.type = TokenType::_return};
                tokens.push_back({.type = TokenType::_return, .value = "ret"});
            } else {
                std::cerr << "Unknown token " << buf << std::endl;
                exit(1);
            }
        }
    }

    
    return tokens;

}

int main(int argc, char* argv[]){

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
    std::cout << Tokenize(contents)[0].value << std::endl;
    return 0;
}