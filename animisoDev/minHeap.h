#include <iostream>
#include <algorithm>    // std::swap
#include "anime.h"
#pragma once
using namespace std;

class MinHeap
{
private:
    vector<anime> allAnime; //vector of anime objects

    //for the insertion
    void heapify(int index);
    bool isDuplicate(anime currentAnime);

    //basic heap functions
    int getParentIndex(int index); //returns parent anime index based on rank
    int getLeftChildIndex(int index);
    int getRightChildIndex(int index);
    anime getTopPopular(); //returns the root

    //functions for our program
    anime extractMin(); //gets the top most popular anime
    void printAnimeStats(anime current);

    //option 2 helper
    vector<string> getTopWithinGenreHelper(vector<string> condensedGenres);

    //option 3 helper
    int searchByNameHelper(string title); //searches anime objects by name and returns index found

public:
    MinHeap();

    void insert(anime newAnime);

    //option 1
    void printTopTen(); //prints out the top 10 anime overall

    //option 2
    vector<string> getTopWithinGenre(int genre); // get the top 5 within a genre

    //option 3
    void searchByName(string title); //search for anime and print out stats

};

MinHeap::MinHeap()
{
    //todo i don't think anything needs to be here
}

void MinHeap::heapify(int index) {

    int min = index; //min = root
    int left = 2 * index + 1; //position of left child
    int right = 2 * index + 2; //position of right child

    // if LEFT child smaller than max
    if (left < allAnime.size() && allAnime[left].popularity < allAnime[min].popularity)
        min = left;

    // if RIGHT child is smaller than max
    if (right < allAnime.size() && allAnime[right] .popularity < allAnime[min].popularity)
        min = right;

    // if min is not the root
    if (min != index) {
        //swap the values to the correct position
        //https://www.cplusplus.com/reference/algorithm/swap/
        swap(allAnime[index], allAnime[min]);

        //fix the rest of the subtree
        heapify(min);
    }
}

bool MinHeap::isDuplicate(anime currentAnime){

    for(int i = 0; i < allAnime.size(); i++){
        if (currentAnime.title == allAnime[i].title){
            return true;
        }
    }
    return false;
}

void MinHeap::insert(anime newAnime)
{
    //if duplicate, just skip
    if(isDuplicate(newAnime))
    {
        return;
    }

    allAnime.push_back(newAnime); // add new anime to heap

    int currentInd = allAnime.size()-1; //get index of new anime added

    //if the parent's popularity rank is greater than newly added
    while (currentInd != 0 && (allAnime[getParentIndex(currentInd)].popularity > allAnime[currentInd].popularity))
    {
        //check if it's a duplicate

        //swap the values to the correct position
        //https://www.cplusplus.com/reference/algorithm/swap/
        swap(allAnime[currentInd], allAnime[getParentIndex(currentInd)]);

        //update index to where the parent is currently as (as long as it's not root
        currentInd = getParentIndex(currentInd);
    }
}

int MinHeap::getParentIndex(int index)
{
    return (index - 1) / 2;

}

int MinHeap::getLeftChildIndex(int index)
{
    return index * 2 + 1;
}

int MinHeap::getRightChildIndex(int index)
{
    return index * 2 + 2;
}

anime MinHeap::getTopPopular()
{
    //returns only the root
    return allAnime[0];
}

//can only call this function one time, because it deletes a node form the heap
//removes the minimum element from heap
anime MinHeap::extractMin() {

    //store the minimum value
    anime topAnime = allAnime[0];
    //replace root with last element in the vector
    allAnime[0] = allAnime[allAnime.size()-1];
    //erase last index
    allAnime.pop_back();
    //heapify
    heapify(0);

    //TEST to see if extract works - it does
//    cout << "removing " << topAnime.title << endl;
//    cout << "new root " << allAnime[0].title << endl;

    return topAnime;
}

void MinHeap::printAnimeStats(anime current) {
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

void MinHeap::printTopTen() {

    vector<anime> dontActuallyDelete;

    //use extract min to get top
    for(int i = 0; i < 10; i++)
    {
        anime top = extractMin();
        printAnimeStats(top);
        dontActuallyDelete.push_back(top);
    }

    //reinsert mins so it doesn't actually delete
    for(int i = 0; i < dontActuallyDelete.size(); i++)
    {
        insert(dontActuallyDelete[i]);
    }

}

vector<string> MinHeap::getTopWithinGenreHelper(vector<string> condensedGenres) {

    //vector to hold top 5 anime in genre
    vector<string> animeList;
    int index = 0;

    bool alreadyAdded = false;

    vector<anime> dontActuallyDelete;

    //while there is not 5 anime, iterate thru entire allAnime via extractMin to get top 5
    while (animeList.size() < 5)
    {
        anime top = extractMin();

        //save extracted min so does not delete
        dontActuallyDelete.push_back(top);

        //iterate through genres in top node
        for(int i = 0; i < top.genres.size(); i++)
        {
            //iterate through the genres in condensedGenres
            for(int k = 0; k < condensedGenres.size(); k++){
                if (top.genres[i] == condensedGenres[k])
                {
                    animeList.push_back(top.title);
                    alreadyAdded = true;
                    break; //break out of this for loop
                }
            }
            if(alreadyAdded){
                alreadyAdded = false;
                break; //break out of second for loop
            }
        }

        index++;
    }

    //reinsert mins so it doesn't actually delete
    for(int i = 0; i < dontActuallyDelete.size(); i++)
    {
        insert(dontActuallyDelete[i]);
    }

    return animeList;

}

vector<string> MinHeap::getTopWithinGenre(int genre) {

    //condensed data set into 4 genres
    vector<string> actionVect = {"Sports", "Shounen", "Adventure", "Supernatural", "Sci-Fi", "Super Power", "School", "Samurai", "Fantasy"};
    vector<string> comedyVect = {"Comedy", "Slice of Life", "Parody"};
    vector<string> dramaVect = {"Drama", "Mystery", "Magic", "Military", "Samurai", "Fantasy", "Mecha"};
    vector<string> romanceVect = {"Romance", "Josei", "Shoujo"};


    switch (genre) {
        case 1:
            return getTopWithinGenreHelper(actionVect);
        case 2:
            return getTopWithinGenreHelper(comedyVect);
        case 3:
            return getTopWithinGenreHelper(dramaVect);
        case 4:
            return getTopWithinGenreHelper(romanceVect);
    }
}

int MinHeap::searchByNameHelper(string title) {

    //should return only one anime
    //if there are multiple anime w same name (but different season titles)
    //will return first anime found

    for(int i = 0; i < allAnime.size(); i++)
    {
        if (allAnime[i].title == title)
        {
            return i;
        }
    }

    return -1;
}

void MinHeap::searchByName(string title) {

    //if title is found
    int indexFound = searchByNameHelper(title);
    if (indexFound != -1)
    {
        printAnimeStats(allAnime[indexFound]);
    }
    else
    {
        cout << "anime not found :(\n";
    }
}
