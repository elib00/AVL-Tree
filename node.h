#include <algorithm>
using namespace std;

struct node {
    node* parent;
    node* right;
    node* left;
    int elem;

    // TODO paste your height method here
    int height() {
        if(!right && !left){
            return 0;
        }

        int l = 0, r = 0;

        if(left){
            l = left->height();
        }

        if(right){
            r = right->height();
        }

        return max(l, r) + 1;
    }
};
