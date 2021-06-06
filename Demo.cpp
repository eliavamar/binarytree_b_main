/**
 * Demo file for the exercise on binary tree
 *
 * @author Erel Segal-Halevi
 * @since 2021-04
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "BinaryTree.hpp"
using namespace ariel;

int f(int x){return x+2;};
int main(){
        BinaryTree<int> tree4;
        tree4.add_root(11);
        tree4.add_left(11,3);
        transform(tree4.begin(), tree4.end(), tree4.begin(), f);
        cout<<tree4.root->value<<endl;
    }


