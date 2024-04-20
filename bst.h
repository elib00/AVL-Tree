#include "mybinarytree.h"

class BST {
	BinaryTree* tree = new MyBinaryTree();

	public:
	bool search(int num) {
		return search_node(tree->getRoot(), num);
	}

	bool search_node(node* n, int num) {
		if (n == NULL) {
			return false;
		}
		if (n->elem == num) {
			return true;
		}
		if (num > n->elem) {
			// proceed to right
			return search_node(n->right, num);
		} else {
			return search_node(n->left, num);
		}
	}

	node* insert(int num) {
		node* n = tree->getRoot();
		if (n == NULL) {
			return tree->addRoot(num);
		}
		return insert_node(n, num);
	}

	node* insert_node(node* n, int num) {
		if (n == NULL) {
			return NULL;
		}
		if (n->elem == num) {
			return NULL;
		}
		if (num > n->elem) {
			if (!n->right) {
				return tree->addRight(n, num);
			} else {
				return insert_node(n->right, num);
			}
		} else {
			if (!n->left) {
				return tree->addLeft(n, num);
			} else {
				return insert_node(n->left, num);
			}
		}
	}

    bool remove(int num) {
        return remove_node(tree->getRoot(), num);
    }

	bool remove_node(node* n, int num) {
		if (n == NULL) {
			return false;
		}
		if (n->elem == num) {
            if (n->left && n->right) {
                node* r = n->right;
                while (r->left) {
                    r = r->left;
                }
                int rem = tree->remove(r);
                n->elem = rem;
            } else {
    			tree->remove(n);
            }
            return true;
		}
		if (num > n->elem) {
			return remove_node(n->right, num);
		} else {
			return remove_node(n->left, num);
		}
	}

    // GIVEN the grandparent (or z), find the parent (or y), and the child (or x).
    bool restructure(node* gp) {
        node* par; // parent
        // TODO find parent
        node *gpLeft = gp->left;
        node *gpRight = gp->right;
        int gpLeftHeight;
        int gpRightHeight;

        if(!gpLeft && gpRight) {
            par = gpRight;
        }else if(gpLeft && !gpRight){
            par = gpLeft;
        }else{
            gpLeftHeight = gpLeft->height();
            gpRightHeight = gpRight->height();

            if(gpLeftHeight > gpRightHeight){
                par = gpLeft;
            }else{
                par = gpRight;
            }
        }

        // This is an indicator of the placement of grandparent to parent (gtop)
        bool gtop_right = false;
        if (gp->right == par) {
            gtop_right = true;
        }

        node* child;
        // TODO find child
        node *parLeft = par->left;
        node *parRight = par->right;
        int parLeftHeight;
        int parRightHeight;

        if(!parLeft && parRight) {
            child = parRight;
        }else if(parLeft && !parRight){
            child = parLeft;
        }else{
            parLeftHeight = parLeft->height();
            parRightHeight = gpRight->height();

            if(parLeftHeight > parRightHeight){
                child = parLeft;
            }else if(parLeftHeight < parRightHeight){
                child = parRight;
            }else{
                if(gtop_right){
                    child = parRight;
                }else{
                    child = parLeft;
                }
            }
        }

        // This is an indicator of the placement of parent to child (ptoc)
        bool ptoc_right = false;
        if (par->right == child) {
            ptoc_right = true;
        }

        // FOR THE FOLLOWING: Write in each of the if statements a console output
        // on its corresponding operation (ZIGLEFT, ZIGRIGHT, ZIGZAGLEFT, or ZIGZAGRIGHT)

        // z
        //  \
        //   y
        //    \
        //     x
        if (gtop_right && ptoc_right) {
            // TODO call to either zigleft or zigright or both
            cout << "ZIGLEFT" << endl;
            zigleft(par);
        }

        // z
        //   \
        //     y
        //    /
        //   x
        else if (gtop_right && !ptoc_right) {
            // TODO call to either zigleft or zigright or both
            cout << "ZIGZAGLEFT" << endl;
            zigright(child);
            zigleft(child);
        }

        //     z
        //    /
        //   y
        //  /
        // x
        else if (!gtop_right && !ptoc_right) {
            // TODO call to either zigleft or zigright or both
            cout << "ZIGRIGHT" << endl;
            zigright(par);
        }

        //      z
        //    /
        //  y
        //   \
        //    x
        else {
            // TODO call to either zigleft or zigright or both
            cout << "ZIGZAGRIGHT" << endl;
            zigleft(child);
            zigright(child);
        }

        return true;
    }

    void zigleft(node* curr) {
        tree->zigleft(curr);
    }

    void zigright(node* curr) {
        tree->zigright(curr);
    }

	void print() {
		tree->print();
	}
};