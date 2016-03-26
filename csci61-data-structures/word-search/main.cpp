#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <hash_table.h>
#include <ctime>
#include <cstdio>

using namespace std;

int main()
{
    clock_t start;
    double duration;
    start = clock();
    // CREATE HASH TABLE FROM DICTIONARY "WORDS.TXT"
    string line;
    hash_table dict (50000);
    ifstream myfile ("words.txt");

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            // remove punctuation
            line.erase(remove_if(line.begin(), line.end(), static_cast<int(*)(int)>(&ispunct)), line.end());
            // switch to upper case
            transform(line.begin(), line.end(),line.begin(), ::toupper);
            dict.insert(line);
        }
        myfile.close();
    }
    else
        cout << "Failed to open dictionary file!" << endl;

    // COPY WORD SEARCH FROM FILE TO VECTOR
    vector< vector <string> > puzzle;
    ifstream myPuzzle ("puzzle.txt");
    string temp1;
    if (myPuzzle.is_open())
    {
        while (getline(myPuzzle, temp1))
        {
            istringstream ss(temp1);
            vector <string> record;
            string temp2;
            while (ss >> temp2)
            {
                record.push_back(temp2);
            }
            if (record.size() != 0)
                puzzle.push_back(record);
        }
    }
    else
        cout << "Failed to open puzzle file!" << endl;

    // CHECK POSSIBLE STRINGS AGAINST HASH TABLE
    string query;
    map<string, vector<int> > answers;
    vector< vector<string> >::iterator temprow=puzzle.begin();
    const int maxRow = (*temprow).size();
    const int maxCol = puzzle.size();

    for (int col = 0; col < maxCol; ++col)
    {
        for (int row = 0; row < maxRow; ++row)
        {
            for (int colMove = -1; colMove <= 1; ++colMove)
            {
                for (int rowMove = -1; rowMove <=1; ++rowMove)
                {
                    if (colMove!=0 || rowMove!=0)
                    {
                        query = "";
                        int col2 = col;
                        int row2 = row;
                        while ((col2>=0 && col2<maxCol) && (row2>=0 && row2<maxCol))
                        {
                            query+=puzzle[col2][row2];
                            if (dict.find(query))
                            {
                                vector<int> tempV;
                                tempV.push_back(col+1);
                                tempV.push_back(row+1);
                                tempV.push_back(col2+1);
                                tempV.push_back(row2+1);
                                answers.insert(std::pair<string, vector<int> >(query, tempV));
                            }
                            col2+=colMove;
                            row2+=rowMove;
                        }
                    }
                }
            }
        }
    }
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;

    // WRITE WORDS TO FILE
    ofstream myfile2;
    myfile2.open ("output.txt");
    for (map<string, vector<int> >::iterator i = answers.begin(); i != answers.end(); ++i)
    {
        myfile2 << i->first << " at (";
        int count = 0;
        for (vector<int>::iterator it = i->second.begin(); it != i->second.end(); ++it)
        {
            ++count;
            if (count == 1 || count == 3)
                myfile2 << *it << ", ";
            if (count == 2)
                myfile2 << *it << ") to (";
            if (count == 4)
                myfile2 << *it << ")";
        }
        myfile2 << endl;
    }
    myfile2.close();

    cout << "There are " << answers.size() << " unique words in your " << maxCol << "x" << maxRow << " word search puzzle. This took "
            << duration << " seconds." << endl;
    return 0;
}
