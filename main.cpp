//
//  main.cpp
//  Dancing links
//
//  Created by 李欣达 on 16/9/11.
//  Copyright © 2016年 李欣达. All rights reserved.
//

#include <iostream>
using namespace std;


struct Node{
    Node* up,*down,*left,*right;
    Node* col;
    int row_index;
};


bool remove_col_node(Node *colnode){
    colnode->right->left=colnode->left;
    colnode->left->right=colnode->right;
    Node *downnode=colnode->down;
    if(downnode==colnode)
        return false;
    while(downnode!=colnode){
        Node *rightnode=downnode->right;
        while(rightnode!=downnode){
            rightnode->up->down=rightnode->down;
            rightnode->down->up=rightnode->up;
            rightnode=rightnode->right;
        }
        downnode=downnode->down;
    }
    return true;
}

void recover_col_node(Node *colnode){
    colnode->right->left=colnode;
    colnode->left->right=colnode;
    Node *downnode=colnode->down;
    while(downnode!=colnode){
        Node *rightnode=downnode->right;
        while(rightnode!=downnode){
            rightnode->up->down=rightnode;
            rightnode->down->up=rightnode;
            rightnode=rightnode->right;
        }
        downnode=downnode->down;
    }
}






