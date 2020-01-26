/*
    Rishi Chandna (rdc180001)
    Louis Fernandes (lef180000)
*/
#include "Document.h"
#include <string>

Document::Document()
{
        content = "";//ctor
}

Document::Document(string _s) {
    content = _s;
}

Document::~Document()
{
    //dtor
}

std::ostream& operator<<(std::ostream& os, const Document& doc) {
    os << doc.Getcontent() << endl;
    return os;
}
