#include "books.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <ctime>


std::string getOlderTime(std::string dateOne, std::string dateTwo){
    std::string one = dateOne;
    std::string two = dateTwo;
    std::string delimiter = "/";

    std::string dayOne = dateOne.substr(0, dateOne.find(delimiter));
    dateOne.erase(0, dateOne.find(delimiter) + delimiter.length());

    std::string monthOne = dateOne.substr(0, dateOne.find(delimiter));
    dateOne.erase(0, dateOne.find(delimiter) + delimiter.length());

    std::string yearOne = dateOne.substr(0, dateOne.find(delimiter));
    dateOne.erase(0, dateOne.find(delimiter) + delimiter.length());

    std::string dayTwo = dateTwo.substr(0, dateTwo.find(delimiter));
    dateTwo.erase(0, dateTwo.find(delimiter) + delimiter.length());

    std::string monthTwo = dateTwo.substr(0, dateTwo.find(delimiter));
    dateTwo.erase(0, dateTwo.find(delimiter) + delimiter.length());

    std::string yearTwo = dateTwo.substr(0, dateTwo.find(delimiter));
    dateTwo.erase(0, dateTwo.find(delimiter) + delimiter.length());
    if(std::stoi(yearOne) < std::stoi(yearTwo)){
        return one;
    }else if(std::stoi(yearOne) > std::stoi(yearTwo)){
        return two;
    }else{
        if(std::stoi(monthOne) < std::stoi(monthTwo)){
            return one;
        }else if(std::stoi(monthOne) > std::stoi(monthOne)){
            return two;
        }else{
            if(std::stoi(dayOne) < std::stoi(dayTwo)){
                return one;
            }else if(std::stoi(dayOne) > std::stoi(dayTwo)){
                return two;
            }
        }
    }

    return one;
}

Book getOldestBook(std::vector<Book> books, int N){
    int indexOfOldest = 0;
    std::string largestDate = books.at(0).getDate();

    if(books.size() <= 1){
        return largestDate;
    }
    
    for(int i = 1; i < N; i++){
        if(getOlderTime(books.at(i).getDate(), largestDate) != largestDate){
            largestDate = books.at(i).getDate();
            indexOfOldest = i;
        }
    }

    return books.at(indexOfOldest);
}

int getNumBooks(std::string author, std::vector<Book> books, int N){
    int count = 0;

    for(int i = 0; i < N; i++){
        if(author == books[i].getAuthorName()){
            count++;
        }
    }

    return count;
}

int main(){
    std::string line;
    std::string title;
    std::string date;
    std::string author;
    std::string length;
    std::string delimiter = ",";

    std::vector<Book> books;

    std::unordered_map<std::string, std::string> authorGenre = {
        {"Steven King", "Horror"}, 
        {"Rudyard Kipling", "Adventure"}, 
        {"Isaac Asimov", "Science Fiction"}, 
        {"Suzanne Collins", "YA Fiction"}, 
    };

    int count = 0;

    while(true){
        std::cout << "Enter a book (TITLE,DATE,AUTHOR,LENGTH) or enter 'q' to quit: ";
        getline(std::cin, line);

        if(line == "q"){
            break;
        }

        count++;

        try{
            title = line.substr(0, line.find(delimiter));
            line.erase(0, line.find(delimiter) + delimiter.length());
        }catch(std::exception &err){
            std::cout << "Error: " << err.what();
            throw std::domain_error("Issue finding title from input");
        }

        try{
            date = line.substr(0, line.find(delimiter));
            line.erase(0, line.find(delimiter) + delimiter.length());
        }catch(std::exception &err){
            std::cout << "Error: " << err.what();
            throw std::domain_error("Issue finding date from input");
        }

        try{
            author = line.substr(0, line.find(delimiter));
            line.erase(0, line.find(delimiter) + delimiter.length());

            if(author != "Steven King" && author != "Rudyard Kipling" && author != "Isaac Asimov" && author != "Suzanne Collins"){
                throw std::invalid_argument("Invalid author entered");
            }
        }catch(std::exception &err){
            std::cout << "Error: " << err.what();
            throw std::domain_error("Issue finding author from input");
        }

        try{
            length = line.substr(0, line.find(delimiter));
            line.erase(0, line.find(delimiter) + delimiter.length());
        }catch(std::exception &err){
            std::cout << "Error: " << err.what();
            throw std::domain_error("Issue finding length from input");
        }

        Book book(title, date, author, length);
        books.push_back(book);
    }

    if(count == 1){
        std::cout << '\n' << books.at(0).getTitle() << ", written by " << authorGenre[books.at(0).getAuthorName()] << " writer " << books.at(0).getAuthorName() << " on " << books.at(0).getDate() << " is " << books.at(0).getLength() << " pages long." << std::endl;
    }else{
        // find author with most books
    
        int kingCount = getNumBooks("Steven King", books, books.size());
        int kiplingCount = getNumBooks("Rudyard Kipling", books, books.size());;
        int asimovCount = getNumBooks("Isaac Asimov", books, books.size());;
        int collinsCount = getNumBooks("Suzanne Collins", books, books.size());;

        std::vector<int> numBooks;
        numBooks.push_back(kingCount);
        numBooks.push_back(kiplingCount);
        numBooks.push_back(asimovCount);
        numBooks.push_back(collinsCount);
        int maxNum = *max_element(numBooks.begin(), numBooks.end());
        
        std::vector<std::string> authorsWithMostBooks;

        if(kingCount == maxNum){
            authorsWithMostBooks.push_back("Steven King");
        }if(kiplingCount == maxNum){
            authorsWithMostBooks.push_back("Rudyard Kipling");
        }if(asimovCount == maxNum){
            authorsWithMostBooks.push_back("Isaac Asimov");
        }if(collinsCount == maxNum){
            authorsWithMostBooks.push_back("Suzanne Collins");
        }

        std::vector <Book> booksByAuthor;
        for(int i = 0; i < books.size(); i++){
            if(std::find(authorsWithMostBooks.begin(), authorsWithMostBooks.end(), books.at(i).getAuthorName()) != authorsWithMostBooks.end()){
                booksByAuthor.push_back(books.at(i));
            }
        }
        
        Book finalBook = getOldestBook(booksByAuthor, booksByAuthor.size());

        std::cout << '\n' << finalBook.getTitle() << ", written by " << authorGenre[finalBook.getAuthorName()] << " writer " << finalBook.getAuthorName() << " on " << finalBook.getDate() << " is " << finalBook.getLength() << " pages long." << std::endl;
    }

    
    return 0;
}