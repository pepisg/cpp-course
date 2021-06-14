#include <task_1.hpp>

int main(){
    num = dist(rd);
    while(usr_input != num){
        std::cout << "Enter a number:\n";
        std::cin >> usr_input;
        if (std::cin.fail()){
            std::cout << "The number must be an integer between 0 and 100\n";
            return EXIT_FAILURE;
        }
        if(usr_input==num){
            break;
        }else if(usr_input<0 || usr_input>100){
            std::cout << "The number must be an integer between 0 and 100\n";
        }else if(usr_input < num){
            std::cout << "This number is greater\n";
        }else{
            std::cout << "This number is smaller\n";
        }
    }
    std::cout << "The number was: " << num << std::endl;
    return EXIT_SUCCESS;
}

 