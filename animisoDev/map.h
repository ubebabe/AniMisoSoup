#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>
#include "redBlackTree.h"
#pragma once
using namespace std;

//inserts data into the map
//in which the map inserts the data into the red and black tree
//red and black tree goes to node class
//node class goes to anime class
class map
{
    redBlackTree tree;

public:
    vector<anime> ogAnime; //vector to hold all the OG anime from dataset (unsorted)

    //transfer all the data
    void loadFile(string fileInput);

    //make map data structure (mass insertion)
    void makeMap();
    //for testing!
    void treeTest();



};

void map::loadFile(string fileInput) {

    //iterates through file ROWS
    //only using certain data in this project
    ifstream animeData(fileInput);
    string title;
    string popularity;
    string genresString; //using this will be used to create edges for graph
    string indivGenre;

    string ignore; //placeholder for skipped spaces when taking in input

    string firstLine;
    getline(animeData, firstLine); //ignore first line, gives variable names

    while (!animeData.eof()) //Not @ end of file
    {
        //defined variables
        getline(animeData, popularity, ',');
        //deliminator is [, since title can have commas... genres are seperated by []
        getline(animeData, title, '[');
        //no deliminator, since last one
        getline(animeData, genresString);

        //convert genre string into a vector:

        //deliminators that separate words in input vector
        int stringCount = 0;
        int openQuote = 0; //index of first quotation
        int closedQuote = 0; //index of last quotation
        int delimDistance = 0;
        vector<string> genreVector; //make new vector for each anime

        //repeat until size - 3 bc end of string is ']
        while (stringCount < genresString.size()-3)
        {
            //each genre is between ' '

            //first genre read in
            if (stringCount == 0)
            {
                //find first quote
                openQuote = genresString.find('\'');
                //find next quote after ^
                closedQuote = genresString.find('\'', openQuote+1);
            }
            else //all genres in between first and last one
            {
                //find first quote after latest closing quote
                openQuote = genresString.find('\'', closedQuote+1);
                //find next quote after ^
                closedQuote = genresString.find('\'', openQuote+1);
            }

            //distance between two quotes = length of genre string
            delimDistance = closedQuote - openQuote - 1;
            indivGenre = genresString.substr(openQuote+1, delimDistance);
            genreVector.push_back(indivGenre);

            stringCount = closedQuote;
        }

        //delete last 2 char in title, which is ",""
        //since the deliminator was [
        title = title.substr(0, title.size()-2);

        //anime obj
        anime anime(title, popularity, genreVector); //taking separate variables and now putting them together into the animeFile obj
        //make a vector of anime objects
        //then construct data structures with information stored (popularity, title, and rank)
        ogAnime.push_back(anime);

    }

    animeData.close();
}

void map::makeMap() {
    for(int i = 0; i < ogAnime.size(); i++)
    {
//        cout << ogAnime[i].title << endl;
        tree.insert(ogAnime[i]);
    }
}

//tests if objects were inserted by inorder print traversal
void map::treeTest() {
//    for(int i = 0; i < ogAnime.size(); i++)
//    {
//        tree.insert(ogAnime[i]);
//    }

    //tree.inorder();
    tree.findTitle("Naruto");
    tree.printTopTen();
}