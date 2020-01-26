/*
    Rishi Chandna (rdc180001)
    Louis Fernandes (lef180000)
*/

#include <iostream>

#include "Document.h"
#include "EMail.h"
#include "File.h"

using namespace std;

bool containsKeyword(Document* doc, string key) {

    if(dynamic_cast<EMail*>(doc)) {
        EMail* email = dynamic_cast<EMail*>(doc);
        if(email->Getcontent().find(key)!=string::npos) { return true; }
        if(email->Getrecipient().find(key)!=string::npos) { return true; }
        if(email->Getsender().find(key)!=string::npos) { return true; }
        if(email->Gettitle().find(key)!=string::npos) { return true; }
    } else if(dynamic_cast<File*>(doc)) {
        File* file = dynamic_cast<File*>(doc);
        if(file->Getcontent().find(key) != string::npos) { return true;}
        if(file->Getfilename().find(key) != string::npos) { return true; }
        if(file->Getpathname().find(key) != string::npos) { return true; }
    } else {
        if(doc->Getcontent().find(key)!= string::npos) { return true;}
    }
    return false;
}
int main()
{
    Document doc("what's up doc");

    EMail email("Hi Professor Smith, how doing", "rishi and louis", "professor_smith", "greetings");

    File file("this is my file content", "C:/Users/OOf/Bad/bad.txt", "bad.txt");
    cout << boolalpha;
    cout << "my document: " << doc;
    cout << "doc contains \"my\":" << containsKeyword(&doc, "my") << endl;
    cout << "doc contains \"up\":" << containsKeyword(&doc, "up") << endl;
    cout << "*******" << endl;

    cout << "my email: " << endl << email << endl;
    cout << "email contains \"louis\":" << containsKeyword(&email, "louis") << endl;
    cout << "email contains \"Grade Inquiry\":" << containsKeyword(&email, "Grade Inquiry") << endl;
    cout << "*******" << endl;
    cout << "my file: " << file;
    cout << "file contains \"bad\":" << containsKeyword(&file, "bad") << endl;
    cout << "file contains \"hello\":" << containsKeyword(&file, "hello") << endl;

    return 0;
}
