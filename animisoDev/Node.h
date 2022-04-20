#pragma once
struct Node {

    int popularity; //key
    //access title and genre through anime object

    int height = 0;

    anime *animeObj;

    //see if node is red or black
    //black = false, means its red
    bool black = false;
    Node *left, *right, *parent;

    //key = popularity rank
    //value = actual anime object
    Node(anime& animeObject) // constructor
    {
        popularity = animeObject.popularity;
        black = false;

        animeObj = &animeObject;

        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }
};

