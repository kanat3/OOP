#include "vect.hpp"

namespace vector{
    // ---------------------- constructors 
    vec::vec(const int size, const int el):a_size(size), a_total(size + this->ext){
        if(size < 0){
            throw std::invalid_argument("negative size");
        }
        this->p_arr = new int [size + this->ext];
        for(int i = 0; i < size; i++){
           this->p_arr[i] = el; 
        }
    }
    
    
    vec::vec(const int size, const int *arr){
        if(size < 0){
            throw std::invalid_argument("negative size");
        }
    
        this->a_total = size + this->ext;
        this->a_size = size;
        this->p_arr = new int [size + this->ext];
        std::copy(arr, arr + size, this->p_arr);
    }
    

    vec::vec(const vec &other){ // :? ------------------
        this->a_size = other.size();
        this->a_total = other.size() + this->ext;
        this->p_arr = new int [this->a_total];
        std::copy(other.begin(), other.end(), this->p_arr);
    }
    
    
    vec::vec(vec &&other):p_arr(nullptr){
        this->a_size = other.a_size;
        this->a_total = other.a_total;
        std::swap(other.p_arr, this->p_arr);
    }
    

    //---------------------- destructor!
    vec::~vec(){
        delete[] this->p_arr;
    } 


    //----------------------  overloading
    const int& vec::operator[](int ind) const{
         if(ind < 0 || ind >= this->a_size){
             throw std::out_of_range("out of range");
         }
         return this->p_arr[ind];
    }
    

    int& vec::operator[](int ind){
        if(ind < 0 || ind >= this->a_size){
            throw std::out_of_range("out of range");
        }
        return this->p_arr[ind];
    }


    vec vec::operator+(const vec &y) const{ // i will improve it, i swear // done
        vec tmp = (y.a_size > this->a_size) ? vec(y.a_size) : vec(this->a_size);
    
        for(int i = 0; i < this->a_size && i < y.a_size; i++){
           tmp[i] = this->p_arr[i] + y.p_arr[i]; 
        }
    
        if(y.a_size > this->a_size){
            std::copy(y.p_arr + this->a_size, y.end(), tmp.p_arr + this->a_size);
        }
        else{
            std::copy(this->p_arr + y.a_size, this->end(), tmp.p_arr + y.a_size);
        }
    
        return tmp;
    }
    

    vec& vec::operator+=(const vec& right) { 
        for(int i = 0; i < right.size() && i < this->a_size; i++){
            this->p_arr[i] += right[i];
        }
        
        if(right.size() > this->a_size){
            int k = this->a_size;
            this->resize(right.size());
            std::copy(right.p_arr + k, right.end(), this->p_arr+k);
        }
        return *this;
    }
    

    vec& vec::operator=(const vec &right){
        if(this != &right){
            delete [] this->p_arr;
            this->a_size = right.size();
            this->a_total = right.size() + this->ext;
            this->p_arr = new int [this->a_total];
            std::copy(right.begin(), right.end(), this->p_arr);
        }
        return *this;
    }
    

    vec& vec::operator=(vec &&right){
        if(this != &right){
            delete [] this->p_arr;
            this->p_arr = nullptr;
            std::swap(this->p_arr, right.p_arr);
            this->a_size = right.a_size;
            this->a_total = right.a_total;
            right.a_size = 0;
            right.a_total = 0;
        }
        return *this;
    }
    
    
    bool vec::operator==(const vec &y) const noexcept{
        if(this == &y){
            return true;
        }
        if(this->a_size != y.size()){
            return false;
        }
        for(int i = 0; i < this->a_size; i++){
            if(this->p_arr[i] != y[i]){
                return false;
            }
        }
        return true;
    }
    

    bool vec::operator!=(const vec &y) const noexcept{
        return !(*this == y);    
    }
     

    std::istream &operator>>(std::istream &in, vec &y){
        for(int i = 0; i < y.a_size; i++){
            getEl(y.p_arr[i], in);
        }
        return in;
    }


    std::ostream &operator<<(std::ostream &out, const vec &y){
        for(int i = 0; i < y.a_size; i++){
            out << y[i] << " ";
        }
        return out;
    } 

    //----------------- extra methods
    void vec::append(const int x){
        if(this->a_total == this->a_size){
            this->resize(this->a_size);    
        }
        this->p_arr[this->a_size] = x;
        this->a_size++;
    }
    
    
    void vec::resize(const int n){
        int *tmp = new int [n + this->ext];
        if(n > this->a_size){
            std::copy(this->begin(),this->end(), tmp);
        }
        else{   
            std::copy(this->begin(), this->p_arr + n, tmp);
        }
        delete[] this->p_arr;
        this->p_arr = tmp;
        this->a_total = n + this->ext;
        this->a_size = n;
    }
    

    vec vec::slice(int ind, int len) const{
        bool neg = (ind < 0 || len < 0);
        bool over = (ind + len > this->a_size || ind >= this->a_size || len  > this->a_size); 

        if(neg){
            throw std::invalid_argument("negative values are not allowed");
        }
        else if(over){  
            throw std::out_of_range("Quiet, buddy");
        }
    
        return vec(len, this->p_arr + ind);
    }
    
    
    void vec::sort(){
        std::make_heap(this->p_arr, this->p_arr + this->a_size);
        std::sort_heap(this->p_arr, this->p_arr + this->a_size);
    }
    
    
    int vec::getmax() const {
        if(this->a_size == 0){
            throw std::out_of_range("no elements");
        }
        return *std::max_element(this->p_arr, this->p_arr + this->a_size);
    }
}
