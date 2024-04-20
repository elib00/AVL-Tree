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
    }
};
