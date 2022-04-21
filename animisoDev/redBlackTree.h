#pragma once
#include <iostream>
#include "Node.h"
#pragma once

class redBlackTree {
    //backend of map

public:
    bool found = false; //for findTitle function
    anime* foundAnime = nullptr;

    Node* root;
    redBlackTree() // constructor
    {
        root = nullptr;
    }

    void insert(anime &animeObj);

    void inorder(); //test^

    //print top 10
    void printTopTen();

    //get top within genre
    vector<string> getTopWithinGenre(int genre);

    //search for title
    void findTitle(string title);

private:

    vector<anime> orderedAnime; //order anime by inorder traversal

    void rotateLeft(Node *&root, Node *&node);
    void rotateRight(Node *&root, Node *&node);

    Node* insertHelper(Node* root, Node* node);
    void insertionRepair(Node *&root, Node *&node);

    void inorderHelper(Node *root);

    void printAnimeStats(anime current);

    vector<string> genreHelper(vector<string> genres);

    Node* titleHelper(string title, Node* root);

};

void redBlackTree::rotateLeft(Node *&root, Node *&node) {
    Node* nodeRight = node->right;

    node->right = nodeRight->left;

    if(node->right != nullptr)
    {
        node->right->parent = node;
    }

    nodeRight->parent = node->parent;

    if(node->parent == nullptr)
    {
        root = nodeRight;
    }

    else if(node == node->parent->left)
    {
        node->parent->left = nodeRight;
    }
    else
    {
        node->parent->right = nodeRight;
    }
    nodeRight->left = node;
    node->parent = nodeRight;
}
void redBlackTree::rotateRight(Node *&root, Node *&node) // right rotation
{
    Node *nodeLeft = node->left;

    node->left = nodeLeft->right;

    if(node->left != nullptr)
    {
        node->left->parent = node;
    }

    nodeLeft->parent = node->parent;

    if(node->parent == nullptr)
    {
        root = nodeLeft;
    }
    else if(node == node->parent->left)
    {
        node->parent->left = nodeLeft;
    }
    else
    {
        node->parent->right = nodeLeft;
    }

    nodeLeft->right = node;
    node->parent = nodeLeft;
}

Node* redBlackTree::insertHelper(Node* root, Node* node)
{

    if (root == nullptr) // if empty tree, sets node to root
    {
        root = node;
        root->parent = nullptr;
        root->black = true; //root is always black
    }
    else if (node->popularity < root->popularity) // if ID is less than root, recursively calls the left node
    {
        node->height++;
        root->left = insertHelper(root->left, node);
        root->left->parent = root;
    }
    else if (node->popularity > root->popularity) // if ID is less than root, recursively calls the right node
    {
        node->height++;
        root->right = insertHelper(root->right, node);
        root->right->parent = root;
    }

//    cout << "inserted: " << root->animeObj->title << endl;

    return root;
}

void redBlackTree::insertionRepair(Node *&root, Node *&node)
{
    //red - 1 and black -0
    Node* parent_ = nullptr;
    Node* grand = nullptr;

    //while node is not root, is red, and parents are red
    //todo parent is null
    while ((node != root) && (node->black == false) && (node->parent != nullptr) && (node->parent->black == false))
    {
        parent_ = node->parent;
        grand = node->parent->parent;

        //if parent of node is LEFT child
        //of grandparent of node
        if (parent_ = grand->left)
        {
            Node* aunt = grand->right;
            //if uncle of node is also red
            //just have to RECOLOR
            if (aunt != nullptr && aunt->black == false)
            {
                grand->black = false;
                parent_->black = true;
                aunt->black = true;
                node = grand;
            }
            else
            {
                //if node is right child of its parent
                //LEFT ROTATE
                if (node == parent_->right)
                {
                    rotateLeft(root, parent_);
                    node = parent_;
                    parent_=node->parent;

                }
                //node is LEFT child of parent
                //RIGHT ROTATE
                rotateRight(root, parent_);
                swap(parent_->black, grand->black);
                node = parent_;
            }
        }
            //if parent of node is RIGHT child
            //of grandparent of node
        else
        {
            Node* aunt = grand->left;

            //if uncle of node is also red
            //only recoloring required
            if ((aunt != nullptr) && (aunt->black == false))
            {
                grand->black = false;
                parent_->black = true;
                aunt->black = true;
                node = grand;
            }
            else
            {
                //if node is LEFT child of parent
                //ROTATE RIGHT
                if (node = parent_->left)
                {
                    rotateRight(root, parent_);
                    node = parent_;
                    parent_ = node->parent;
                }
                //if node is RIGHT child of parent
                //LEFT rotate
                rotateLeft(root, parent_);
                swap(parent_->black, grand->black);
                node = parent_;
            }

        }
    }
    root->black = true;

}

void redBlackTree::insert(anime &animeObj) {

    Node *insertedAnime = new Node(animeObj); //make new node

    root = insertHelper(root, insertedAnime); //insert node into red black tree

    insertionRepair(root, insertedAnime); //fix insertion based on red black rules

}

void redBlackTree::inorderHelper(Node *root) {

    if(root == nullptr)
    {
        return;
    }

    inorderHelper(root->left);

//    cout << root->animeObj->popularity << " " << root->animeObj->title << endl;
    orderedAnime.push_back(*root->animeObj);

    inorderHelper(root->right);
}

void redBlackTree::inorder() {

    orderedAnime.clear();

    inorderHelper(root); //adds ordered anime to global inorder vector

    //can return void bc it updates globally
}

void redBlackTree::printTopTen()
{
    inorder();

    for (int i = 0; i < 10; i++)
    {
        anime top = orderedAnime[i];
        printAnimeStats(top);
    }
};

void redBlackTree::printAnimeStats(anime current) {
    cout << current.title << endl;
    cout << "- popularity rank: " << current.popularity << endl;
    cout << "- genre(s): ";
    for (int i = 0; i < current.genres.size(); i++){
        cout << current.genres[i];
        if(i != current.genres.size()-1)
        {
            cout << ", ";
        }
    }
    cout << "\n\n";
}


vector<string> redBlackTree::genreHelper(vector<string> _genres)
{
    vector<string> animeList;
    inorder();
    bool added = false;
    int index = 0;
    while (animeList.size() < 5)
    {
        for (int j = 0; j < orderedAnime[index].genres.size(); j++)
        {
            for (int k = 0; k < _genres.size(); k++)
            {
                if (orderedAnime[index].genres[j] == _genres[k])
                {
                    animeList.push_back(orderedAnime[index].title);
                    added = true;
                    break;
                }
            }
            if (added)
            {
                added = false;
                break;
            }
        }
        index++;
    }
    return animeList;
}

vector<string> redBlackTree::getTopWithinGenre(int genre)
{
    vector<string> actionVect = {"Sports", "Shounen", "Adventure", "Supernatural", "Sci-Fi", "Super Power", "School", "Samurai", "Fantasy"};
    vector<string> comedyVect = {"Comedy", "Slice of Life", "Parody"};
    vector<string> dramaVect = {"Drama", "Mystery", "Magic", "Military", "Samurai", "Fantasy", "Mecha"};
    vector<string> romanceVect = {"Romance", "Josei", "Shoujo"};

    switch (genre)
    {
        case 1:
            return genreHelper(actionVect);
        case 2:
            return genreHelper(comedyVect);
        case 3:
            return genreHelper(dramaVect);
        case 4:
            return genreHelper(romanceVect);
    }
}

Node* redBlackTree::titleHelper(string _title, Node *root)
{
    //if node is empty, DNE
    if (root == nullptr)
    {
        return root;
    }

    //traverse through the left nodes
    root->left = titleHelper(_title, root->left);

    //if title is found
    if (root->animeObj->title == _title)
    {
        found = true;
        foundAnime = root->animeObj;
    }

    //traverse through right nodes
    root->right = titleHelper(_title, root->right);

    //if title is found
    /*
    if (root->animeObj->title == _title)
    {
        found = true;
    }*/

    return root;
}

void redBlackTree::findTitle(string title)
{
    foundAnime = nullptr;
    found = false;
    if (root == nullptr)
    {
        cout << "anime not found :(\n";
    }

    titleHelper(title, root);

    if (!found)
    {
        cout << "anime not found :(\n";
    }
    if (foundAnime == nullptr)
    {
        cout << "anime not found :(\n";
    }
    printAnimeStats(*foundAnime);
}

