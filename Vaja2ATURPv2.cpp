// vaja1ATURP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector> 
#include <sstream> 
#include <string>
using namespace std;

struct Person;
struct Candy;

struct Relation {
    Candy* candy;
    Person* person;

    Relation(Candy* can, Person* per)
    {
        candy = can;
        person = per;
    }
};

struct Person {
    int index;
    int state = 0;
    int linkcount = 0;

    vector<Relation*> relations;

    Person(int i) {
        index = i;
    }

    void pushRel(Candy* dest) {

        Relation* temp = new Relation(dest, this);
        this->relations.push_back(temp);
    }
};

struct Candy {
    int index;
    int state = 0;
    int num = 0;

    vector<Relation*> relations;

    Candy(int i) {
        index = i;
    }

    void pushRel(Person* dest) {

        Relation* temp = new Relation(this, dest);
        this->relations.push_back(temp);
    }
};



vector<int> retL;
vector<int> retG;
vector<int> result;
vector<bool> cikel;
vector<Candy*> candies;
vector<Person*> people;
int countG = 1;
int countL = 9;

bool getLinkCount(Person* curr, vector<Candy*> stack, int depth)
{
    curr->state = 1;
    depth++;
    int relcount = curr->relations.size();
    int recret = 0;
    for (size_t i = 0; i < relcount; i++)
    {
        bool flag = 0;
        for (int n = 0; n != stack.size(); n++)
        {
            if (stack.at(n) == curr->relations.at(i)->candy)
                flag = 1;
        }
        if (flag == 0)
            stack.push_back(curr->relations.at(i)->candy);
    }

    int numrels = 0;

    int stacksize = stack.size();
    for (int i = 0; i != stacksize; i++)
    {
        numrels += stack.at(i)->num;
    }
    if (numrels < depth)
    {
        return 1;
    }

    int peoplesize=people.size();
    for (size_t i = curr->index+1; i < peoplesize; i++)
    {
        if (people.at(i)->state == 0)
            recret = getLinkCount(people.at(i), stack, depth);
        if (recret == 1)
            return 1;
    }

    curr->state = 0;
    depth--;


    return 0;
}


bool checkMarrige()
{
    int retval = 1;
    vector<Candy*> tempstack;
    int peoplesize = people.size();
    for (int i = 0; i != peoplesize; i++)
    {
        retval = getLinkCount(people.at(i), tempstack, 0);
        if (retval == 1)
            return 1;
    }
    return 0;
}

int main()
{
    int numA;
    int numB;
    int countS = 0;
    int countL = 0;


    int countN = 0;
    int countM = 0;
    cin >> countS;
    cin >> countL;




    for (int i = 0; i != countS; i++)
    {
        Candy* tempcandy = new Candy(i);
        candies.push_back(tempcandy);
    }
    for (int i = 0; i != countL; i++)
    {
        Person* tempperson = new Person(i);
        people.push_back(tempperson);
    }

    for (int i = 0; i != countS; i++)
    {
        int candiecount = 0;
        cin >> candiecount;
        candies.at(i)->num = candiecount;
    }
    string cleaner;
    getline(cin, cleaner);

    for (int i = 0; i != countL; i++)
    {
        string line;
        getline(cin, line);
        int tempint;
        stringstream tempstream(line);
        while (tempstream >> tempint)
        {
            people.at(i)->pushRel(candies.at(tempint - 1));
            people.at(i)->linkcount += candies.at(tempint - 1)->num;
        }
    }



    bool possible = checkMarrige();




    for (int i = 0; i != countS; i++)
    {
        cout << candies.at(i)->index << ": " << candies.at(i)->num << "\n";
    }
    cout << "\n";
    for (int i = 0; i != countL; i++)
    {
        cout << people.at(i)->index << " : " << people.at(i)->linkcount << "\n";
        for (size_t n = 0; n < people.at(i)->relations.size(); n++)
        {
            cout << people.at(i)->relations.at(n)->person->index << "<->" << people.at(i)->relations.at(n)->candy->index << "\n";
        }
        cout << "\n";
    }
    if (possible == 0)
        cout << "\nDA\n\n";
    else
        cout << "\nNE\n\n";

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
