/*
    Rishi Chandna (rdc180001)
    Louis Fernandes (lef180000)
*/
#include "EMail.h"

EMail::EMail()
{
    sender = "";
    recipient = "";
    title = "";

    //ctor
}

EMail::EMail(string _content, string _sender, string _recipient, string _title) : Document(_content) {
    sender = _sender;
    recipient = _recipient;
    title = _title;
}

EMail::~EMail()
{
    //dtor
}

std::ostream& operator<<(std::ostream& os, const EMail& email) {
    os << "From: " << email.Getsender() << endl;
    os << "To: " << email.Getrecipient() << endl;
    os << "Subject: " << email.Gettitle() << endl << endl;
    os << email.Getcontent() << endl;
    return os;
}
