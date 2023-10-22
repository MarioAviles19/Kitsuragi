#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


#include "./tokenization.hpp"
#include "./parser.hpp"
#include "./generation.hpp"



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
    std::vector<Token> tokens = tokenizer.Tokenize();

    Parser parser(std::move(tokens));
    std::optional<Node_Prog> program = parser.parse_prog();

    if(!program.has_value()){
        std::cerr << "Invalid program" << std::endl;
        exit(1);
    }


    Generator generator(program.value());

    {
        std::fstream file("out.asm", std::ios::out);
        file << generator.gen_prog();

    }
    system("nasm -felf64 out.asm");
    system("ld -o test out.o");

    return 0;
}


