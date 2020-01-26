/*
    Rishi Chandna (rdc180001)
    Louis Fernandes (lef180000)
*/
#include "File.h"

File::File()
{
    pathname = "";
    filename = "";
}

File::File(string _content, string _pathname, string _filename) : Document(_content) {
    pathname = _pathname;
    filename = _filename;
}

File::~File()
{
    //dtor
}

std::ostream& operator<<(std::ostream& os, const File& file) {
    os << "Path: " << file.Getpathname() <<  endl;
    os << "Filename: " << file.Getfilename() << endl;
    os << "Content: " << file.Getcontent() << endl;
    return os;
}
