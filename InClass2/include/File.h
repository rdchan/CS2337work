/*
    Rishi Chandna (rdc180001)
    Louis Fernandes (lef180000)
*/
#ifndef FILE_H
#define FILE_H

#include <Document.h>
#include <string>
#include <iostream>

using namespace std;

class File : public Document
{
    public:
        File();
        File(string, string, string);
        virtual ~File();

        string Getpathname() const { return pathname; }
        void Setpathname(string val) { pathname = val; }
        string Getfilename() const { return filename; }
        void Setfilename(string val) { filename = val; }
        friend std::ostream& operator<<(std::ostream&, const File&);

    protected:

    private:
        string pathname;
        string filename;
};

#endif // FILE_H
