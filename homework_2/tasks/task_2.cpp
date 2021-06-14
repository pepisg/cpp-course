#include <task_2.hpp>

file get_file(std::string name){
    file f;
    if(name.find_last_of(".") != std::string::npos)
        f.name = name.substr(0, name.find_last_of("."));
        f.extension = name.substr(name.find_last_of(".")+1);
    return f;
}

int main(int argc, char *argv[]){
    if(argc != 3){
        std::cerr << "Input 2 arguments with number names and extensions .txt or .png\n";
        return EXIT_FAILURE;
    }
    std::cout << argv[1] << " " << argv[2] << std::endl;
    try
    {
        files[0] = get_file(argv[1]); files[1] = get_file(argv[2]);
        if (files[0].extension=="png" && files[1].extension=="png"){
            result = stof(files[0].name) + stof(files[1].name);
        }else if(files[0].extension=="txt" && files[1].extension=="txt"){
            result = (stof(files[0].name) + stof(files[1].name))/2.0f;
        }else if(files[0].extension=="txt" && files[1].extension=="png" || files[0].extension=="png" && files[1].extension=="txt"){
            result =  stoi(files[0].name) % stoi(files[1].name);
        }else{
            std::cerr << "Input 2 arguments with number names and extensions .txt or .png\n";
            return EXIT_FAILURE;
        }
        std::cout << "result: " << result << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Input 2 arguments with number names and extensions .txt or .png\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}