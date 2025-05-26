#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

using namespace std;
#include <exception>

//exception for writing to file
class FileWriteException : public exception
{
public:
    virtual const char* what() const throw()
    {
        return "Couldn't write to file!";
    }
};

//exception for reading from file
class FileReadException : public exception
{
public:
    virtual const char* what() const throw()
    {
        return "Couldn't read from file!";
    }
};


#endif // EXCEPTIONS_H
