#include <iomanip>
#include <iostream>
#include <vector>
#include "aniMisoSetup.h"
#include <fstream>
using namespace std;

int main() {

    // 1) make object
    aniMisoSetup aniMiso;

    cout << std::fixed << setprecision(2);

    // 2) loads data
    //automatically builds anime heap, based on popularity rank
    aniMiso.loadFile("animes.csv");

    // 3) opening message and first menu options
    aniMiso.welcomeMessage();

    char option = '0';
    bool chosenDSA = false;

    while (option != '4') {

        aniMiso.printMenu();
        cin >> option;

        switch (option) {
            case '1':
                //choose DSA
                chosenDSA = aniMiso.chooseDSA();
                //print top 10
                aniMiso.optionOne(chosenDSA);
                break;
            case '2':
                //choose DSA
                chosenDSA = aniMiso.chooseDSA();
                // prompts user for more input for specified genre
                aniMiso.optionTwo(chosenDSA);
                option = '0';
                break;
            case '3':
                //choose DSA
                chosenDSA = aniMiso.chooseDSA();
                //search for title
                aniMiso.optionThree(chosenDSA);
                option = '0';
                break;
            case '4':
                break;
            default:
                option = '0';
                cout << "oop, that's not an option. try again!\n\n";
                break;
        }
    }

    cout << "thank you! hope you enjoyed your bowl of AniMiso Soup!";


    return 0;
}