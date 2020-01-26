/*
    Rishi Chandna (rdc180001)
    Louis Fernandes (lef180000)
*/
#ifndef EMAIL_H
#define EMAIL_H

#include <Document.h>
#include <string>
#include <iostream>

using namespace std;

class EMail : public Document
{
    public:
        EMail();
        EMail(string, string, string, string);
        virtual ~EMail();

        string Getsender() const { return sender; }
        void Setsender(string val) { sender = val; }
        string Getrecipient() const { return recipient; }
        void Setrecipient(string val) { recipient = val; }
        string Gettitle() const { return title; }
        void Settitle(string val) { title = val; }
        friend std::ostream& operator<<(std::ostream&, const EMail&);

    protected:

    private:
        string sender;
        string recipient;
        string title;
};

#endif // EMAIL_H
