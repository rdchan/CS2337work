/*
    Rishi Chandna (rdc180001)
    Louis Fernandes (lef180000)
*/
#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <string>
#include <iostream>

using namespace std;
class Document
{
    public:
        Document();
        Document(string);
        virtual ~Document();

        std::string Getcontent() const { return content; }
        void Setcontent(std::string val) { content = val; }
        friend std::ostream& operator<<(std::ostream&, const Document&);

    protected:

    private:
        std::string content;
};

#endif // DOCUMENT_H
