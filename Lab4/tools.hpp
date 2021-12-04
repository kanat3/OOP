#include <exception>
#include <iostream>
#include <vector>
#include <limits>


template <typename T>
void getInput (T &x, std::istream &in = std::cin, std::ostream &err= std::cerr){
    bool valid;
    do {
        try{
            in >> x;
            valid = in.good();
            if(in.fail()){
                throw std::invalid_argument("Bad input");
            }
        }
        catch(const std::exception &e){
            err << e.what();
            if(in.bad()){
                throw std::runtime_error("Stream fell");
            }
            else if(in.eof()){
                throw std::runtime_error("Reached eof");
            }
            err << ", retry" << std::endl;
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while(!valid);
}