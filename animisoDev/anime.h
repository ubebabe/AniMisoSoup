#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

struct anime
{
    string title;
    int popularity;
    vector<string> genres;
    anime();

    anime(string inTitle, string inPopularity, vector<string> inGenre)
    {
        title = inTitle;
        //had to use stringstream to convert to int?
        //https://www.techiedelight.com/convert-string-to-int-cpp/
        istringstream(inPopularity) >> popularity;
        genres = (inGenre);
    }

};