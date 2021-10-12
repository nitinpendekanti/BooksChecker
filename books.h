#include <string>

class Book{
    private:
    std::string title;
    std::string date;
    std::string author;
    std::string length;

    public:
    Book(std::string title = "", std::string date = "", std::string author = "", std::string length = ""); //Constructor
    std::string getAuthorName(); // Accessor for Author attribute
    std::string getDate(); // Accessor for Date attribute
    std::string getTitle(); // Accessor for title attribute
    std::string getLength(); // Accessor for length attribute
};