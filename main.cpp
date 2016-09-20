//
//  main.cpp
//  Dancing links
//
//  Created by 李欣达 on 16/9/19.
//  Copyright © 2016年 李欣达. All rights reserved.
//

#include <iostream>
#include <stack>
using namespace std;


struct Node{
    Node* up,*down,*left,*right;
    Node* col;
    int row_index;
    Node(int r):up(NULL),down(NULL),left(NULL),right(NULL),col(NULL),row_index(r){}
};


class DLX{
public:
    // remove all items and their corresponding row items under colnode.
    bool remove_col_node(Node *colnode);
    // recover the removed colnode;
    void recover_col_node(Node *colnode);
    // generate a DLX from a two-dimension array board.
    Node* create(int board[6][7]);
    // use backtracking algorithm with recursion to solve the DLX.
    bool solve_DLX(Node* head);
    // print the result rows stored in the stack answers.
    void print_answer();
private:
    // a stack used to store rows.
    stack<int> answers;
};


bool DLX::remove_col_node(Node *colnode){
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


void DLX::recover_col_node(Node *colnode){
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



Node* DLX::create(int board[6][7]){
    Node* head=new Node(0);
    Node* lastnode=head;
    for(int i=1;i<=7;i++){
        Node* node=new Node(0);
        lastnode->right=node;
        node->left=lastnode;
        node->up=node;
        node->down=node;
        lastnode=node;
    }
    lastnode->right=head;
    head->left=lastnode;
    for(int i=0;i<6;i++){
        Node *lastnode=NULL,*firstnode=NULL;
        for(int j=0;j<7;j++){
            if(board[i][j]==1){
                Node* columnnode=head;
                for(int n=0;n<=j;++n){
                    columnnode=columnnode->right;
                }
                Node* node=new Node(i+1);
                node->up=columnnode->up;
                node->down=columnnode;
                columnnode->up->down=node;
                columnnode->up=node;
                node->col=columnnode;
                if(lastnode==NULL){
                    firstnode=node;
                    lastnode=node;
                }
                node->left=lastnode;
                lastnode->right=node;
                lastnode=node;
            }
        }
        firstnode->left=lastnode;
        lastnode->right=firstnode;
    }
    return head;
}


bool DLX::solve_DLX(Node* head){
    if(head->right==head)
        return true;
    Node* nextnode=head->right;
    if(!remove_col_node(nextnode))
        return false;
    Node* downnode=nextnode->down;
    while(downnode!=nextnode){
        Node* downRightNode=downnode->right;
        while(downRightNode!=downnode){
            Node* rightColNode=downRightNode->col;
            remove_col_node(rightColNode);
            downRightNode=downRightNode->right;
        }
        if(solve_DLX(head)){
            answers.push(downnode->row_index);
            return true;
        }else{
            Node* downRightNode=downnode->right;
            while(downRightNode!=downnode){
                Node* rightColNode=downRightNode->col;
                recover_col_node(rightColNode);
                downRightNode=downRightNode->right;
            }
            downnode=downnode->down;
        }
    }
    recover_col_node(nextnode);
    return false;
}


void DLX::print_answer(){
    while(!answers.empty()){
        cout<<answers.top()<<endl;
        answers.pop();
    }
}


int main(){
    int board[6][7]={
        {0,0,1,0,1,1,0},
        {1,0,0,1,0,0,1},
        {0,1,1,0,0,1,0},
        {1,0,0,1,0,0,0},
        {0,1,0,0,0,0,1},
        {0,0,0,1,1,0,1}
    };
    DLX dlx;
    Node * head=dlx.create(board);
    dlx.solve_DLX(head);
    dlx.print_answer();
}



