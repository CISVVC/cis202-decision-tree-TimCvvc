/*
 File: main.cpp
 Description: This program will create a decision tree for an animal guessing game.
 Created: 5/15/20
 Author: Tim Chester
 email: chestert@student.vvc.edu
*/

#include <iostream>
#include <fstream>
#include <string>
#include "binary_tree.h"

void write(ostream& out, const Binary_tree& tree, int level);
std::string leading_trim(const std::string& str);

Binary_tree read(istream& in)
{
    std::string data;

    int level;

    in >> level;

    std::getline(in, data);
    data = leading_trim(data); //trims leading white space in front of the data

    if (level == -1)
    {
        return Binary_tree();
    }

    Binary_tree left, right;
    left = read(in);

    right = read(in);

    return Binary_tree(data, left, right);
}

void write(ostream& out, const Binary_tree& tree, int level)
{
    if (tree.empty())
    {
        out << -1 << "\n";
        return;
    }

    out << level << ' ' << tree.data() << "\n";

    write(out, tree.left(), level + 1);

    write(out, tree.right(), level + 1);
}

/**
    Trims leading blank spaces
    @param str string to be trimmed
*/
std::string leading_trim(const std::string& str)
{
    size_t start = str.find_first_not_of(" ");
    return (start == std::string::npos) ? "" : str.substr(start);
}


/*
 * helper function that will help with definite or indefinite
 * articles in a string
 */
std::string article(const std::string& entry)
{
    std::string article = "a";
    if (std::string("aeiou").find(entry[0]) != std::string::npos)
    {
        article = "an";
    }
    return article;
}

int main(int argc, char** argv)
{
    Binary_tree root; //contents of the file are written to root. The Beginning of the tree.

    //takes an argument from the command line as the filename
    if (argc > 1)
    {
        std::cout << "The first argument is: " << std::endl;
        std::cout << argv[1] << std::endl;
    }

    fstream qfile(argv[1]);

    //root is initialized by the file here
    if (qfile.is_open())
    {
        root = read(qfile);
        qfile.close();
    }

    Binary_tree question_tree = root; //question_tree will be the current working Binary_tree

    cout << "This is an animal guessing game. Think of an animal and I will try to guess it." << std::endl;

    while (!question_tree.empty())
    {
        std::string response; //generic response to hold user input

        //question_tree will be set to left if response is yes, and right if response is no
        Binary_tree left = question_tree.left();
        Binary_tree right = question_tree.right();

        //out puts the question or answer to the user
        if (question_tree.left().empty() && question_tree.right().empty()) //checks if the current data is an answer rather than a question
        {
            cout << "It is " << article(question_tree.data()) << " " << question_tree.data() << " ";
        }
        else
        {
            cout << question_tree.data() << " ";
        }
        cin >> response;

        if (question_tree.left().empty() && question_tree.right().empty()) //if the data is an answer
        {
            if (response == "y" || response == "Y")
            {
                cout << "I guessed it!" << std::endl << "Would you like to play again? ";
                cin >> response;
                if (response == "y" || response == "Y")
                {
                    question_tree = root;
                }
                else
                {
                    break;
                }
            }
            else //the program will add new questions to get better for next time
            {
                cout << "I give up. What is it? ";
                cin >> response;

                cout << "Please give me a question that is true for " << article(response) << " " << response << " and false for " << article(question_tree.data()) << " " << question_tree.data() << std::endl;
                string question;
                cin.ignore();
                getline(cin, question);

                question_tree.insert(question, response, question_tree.data()); //inserts the new question in the place of the original answer

                cout << "Okay" << std::endl << "May I try again? ";
                cin >> response;
                if (response == "y" || response == "Y")
                {
                    question_tree = root;
                }
                else
                {
                    break;
                }
            }
        }
        else if (response == "y" || response == "Y") //the else if and else statements iterate through the tree depending on the users input. y = left, n = right.
        {
            question_tree = left;
        }
        else
        {

            question_tree = right;
        }
    }

    //writes the new tree to the file
    qfile.open(argv[1]);
    write(qfile, root, 0);
    qfile.close();
}