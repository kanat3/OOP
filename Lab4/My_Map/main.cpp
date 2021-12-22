#include "Map.hpp"
#include "Node.hpp"

int main (void) {
    Map<int,int> a;
    a.insert(1, 99);
    a.insert(2, 5);
	for (auto it = a.m_begin(); it != a.m_end(); ++it) {
		std::cout << "   " << "\t    " << it._node->key << "\t      " << it._node->data << std::endl;
	}
    puts("after remove root: ");
    a.remove(1);
    auto it = a.find(1);
    if (it == nullptr) {
        puts("No root");
    } else {
        for (auto it = a.m_begin(); it != a.m_end(); ++it) {
            std::cout << "   " << "\t    " << it._node->key << "\t      " << it._node->data << std::endl;
        }
    }
    
}