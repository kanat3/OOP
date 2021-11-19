#pragma once
#include <stdexcept>
#include <algorithm>

#include "toolib.hpp"

namespace vector{
    class vec{
        private:
            int *p_arr;
            int a_size;
            int a_total;
            static const short ext = 5;  // extra space during reallocation

        public:
            explicit vec(const int size = 0, const int el = 0);// default, like a vector in stl
            explicit vec(const int size, const int *arr);      // from the array
            vec(const vec &y);                                 // copy constructor
            vec(vec &&y);                                      // move constructor
            ~vec();                                            // de....(wait a second..)....structor!!!
            
            const int& operator[](const int ind) const;        // great choice to read comment here
            int& operator[](const int ind); 

            vec& operator+=(const vec &y);

            bool operator==(const vec &y) const noexcept;
            bool operator!=(const vec &y) const noexcept;
            
            vec& operator=(const vec &y);                      // copy assignment
            vec& operator=(vec &&y);                           // move assignment

            vec operator+(const vec &y) const;                 // adding two vectors                    

            explicit operator bool() const{ return !(this->a_size == 0);}

            void append(int el);
            vec slice(int ind, int len) const;

            void sort();
            int getmax() const;
            void resize(const int n);

            int* begin() const {return this->p_arr;};
            int* end() const {return this->p_arr + this->a_size;};
            int size() const {return this->a_size;};

            friend std::istream &operator>>(std::istream &in, vec &y);    // rewrites the whole vector according to it's size 
            friend std::ostream &operator<<(std::ostream &out,const vec &y);   
    };

std::istream &operator<<(std::istream &in, vec &y);
std::ostream &operator>>(std::ostream &out, const vec &y);
}


