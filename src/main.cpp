#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


#include "./tokenization.hpp"


std::string tokens_to_asm(std::vector<Token> tokens){
    std::stringstream output;

    output << "global _start\n_start:\n";
    if(tokens.size() == 3){
        if(tokens[0].type == TokenType::exit && tokens[1].type == TokenType::int_lit && tokens[2].type == TokenType::semi){
            output << "mov rax, 60" << std::endl;
            output << "mov rdi, " << tokens[1].value.value() << std::endl;
            output << "syscall";
        } else{

            std::cerr << "Unexpected behavior";
            exit(1);
        }
    } else{
        std::cerr << "Unexpected behavior";
        exit(1);
    }

    return output.str();
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


    Tokenizer tokenizer(std::move(contents));

    std::string output = tokens_to_asm(tokenizer.Tokenize());

    {
        std::fstream file("out.asm", std::ios::out);
        file << output;
    }
    system("nasm -felf64 out.asm");
    system("ld -o test out.o");

    return 0;
}


