#include "books.h"

Book::Book(std::string title, std::string date, std::string author, std::string length){
    this->title = title;
    this->date = date;
    this->author = author;
    this->length = length;
}

std::string Book::getAuthorName(){
    return this->author;
}

std::string Book::getDate(){
    return this->date;
}

std::string Book::getTitle(){
    return this->title;
}

std::string Book::getLength(){
    return this->length;
}
