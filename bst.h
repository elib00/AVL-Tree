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

    //logic based sa description ni sir
    //mo restructure ang whole tree in one go
    //for me di kaayo sha mo make sense kay why paman
    //nimo need i check ang every level if balanced ba
    //if pwede man nimo i balance nalang kada mag insert ka
    //will further look into its advantages in certain cases
    void balance(node *currentNode){
        if(!currentNode) return;
        
        int leftHeight = -1, rightHeight = -1;
        node *currLeft = currentNode->left;
        node *currRight = currentNode->right;

        if(!currLeft && !currRight) balance(currentNode->parent);

        if(currLeft) leftHeight = currLeft->height();
        if(currRight) rightHeight = currRight->height();

        if(abs(leftHeight - rightHeight) > 1){
            restructure(currentNode);
        }

        balance(currentNode->parent);
    }

    // TODO perform post-processing by checking for violation after insertion
    // from the node inserted (or from its parent) until the root
	node* insert(int num) {
		node* n = tree->getRoot();
		if (n == NULL) {
			return tree->addRoot(num);
		}
		
        node *res = insert_node(n, num);
        balance(res->parent);
        return res;
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


    // TODO perform post-processing by checking for violation after deletion
    // from the parent of the node removed until the root
    bool remove(int num) {
        //naay special case, if i remove ang root
        //since pa-up man ta, di jud to ma automatically re-balance
        //need nako og remove nga function nga mo return sa parent sa 
        //na remove na node

        //node *nodeToRemove = search2(num);
        //if(!nodeToRemove) return false; //wa nakit an
        //bool res = remove_node(tree->getRoot(), num);

        node *par = remove_node(num, tree->getRoot());
        balance(par);
        return par != nullptr;
    }

    //mo handle sa case where giremove ang root
    //overloaded method sa original ni sir
    //returns the parent of the removed node
    node *remove_node(int num, node *n){
        if (n == NULL) {
			return nullptr; //meaning wa nakit an if null
		}
        
		if (n->elem == num) {
            node *par = nullptr;
            if (n->left && n->right) {
                node* r = n->right;
                while (r->left) {
                    r = r->left;
                }

                par = r->parent;
                int rem = tree->remove(r);
                n->elem = rem;
            } else {
                par = n->parent;
    			tree->remove(n);
            }
            return par;
		}
		if (num > n->elem) {
			return remove_node(num, n->right);
		} else {
			return remove_node(num, n->left);
		}
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

    bool restructure(node* gp) {
        node* par; // parent
        // TODO find parent
        node *gpLeft = gp->left;
        node *gpRight = gp->right;
        int gpRightHeight;
        int gpLeftHeight;

        if(!gpLeft && gpRight){
            par = gpRight;
        }else if(gpLeft && !gpRight){
            par = gpLeft;
        }else{
            gpRightHeight = gpRight->height();
            gpLeftHeight = gpLeft->height();

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

        if(!parLeft && parRight){
            child = parRight;
        }else if(parLeft && !parRight){
            child = parLeft;
        }else{
            parLeftHeight = parLeft->height();
            parRightHeight = parRight->height();

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