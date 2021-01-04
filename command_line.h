#include <iostream>
#include "performance_reporter.h"

using namespace std;

#ifndef COMMAND_LINE
#define COMMAND_LINE


enum UserOperation{
    fnd,
    del,
    put,
    ini,
    res,
    exs,
    exn,
    sav,
    upd,
    unknown
};


/*
Class UserCommand

Class represents DTO used for calling Dictionary Services. Consists of two elements:
# command - takes values 'r'  for read/find or 'w' for insert
# payload - searched string or dictionary entry to be inserted
*/

class UserCommandDTO{

    public:
        UserOperation getOperation(){return this->operation;}
        string getPayload(){return this->payload;}

        void setOperation(UserOperation _operation){ this->operation = _operation;}
        void setPayload(string _payload){ this->payload = _payload;}

    private:    
        UserOperation operation;
        string payload;
};

/*
Interface between Dictionary and User Interface. This DTO definition should be global.
*/

class DictQueryDTO{

    public:
        string getKey(){return this->key;}
        string getValue(){return this->value;}

        void setKey(int _key){ this->value = _key;}
        void setValue(string _value){ this->value = _value;}

    private:    
        string key;
        string value;
};

/*
Class Parser

Enables Parse method which converts entry string into UserCommand object. Contains parsing logic.
TBD: Exception handling, space truncating etc. 

*/

class Parser{
     
    public:
        UserCommandDTO ParseUserEntry(string);

    private:
        UserCommandDTO user_command;
        string keyword;
        string payload;
        void SetParseError();
        void NoArgCheck(string _entry){ if(_entry.size()>3) cout <<endl <<"operation " <<keyword << " must have no arguments";}
        string ParseFilename(string); 
        
};


/*
Class DictServiceInvoker
Encapsulates Dictonary Services Client Logic.

*/

class DictServiceInvoker{

    public:
        int ExecuteUserCommand(DictQueryDTO&, UserCommandDTO, PerformanceReporter &);

};



/*
Class CommandLine
Enables main User Interface method GetUserCommand. Presents prompt, parses input and calls dictionary services: find and insert.

*/

class CommandLine{

    public:
        int ProcessUserCommand();

    private:
        Parser parser;
        string _input;
        DictQueryDTO query_result;
        UserCommandDTO user_command;
        DictServiceInvoker invoker;
        PerformanceReporter performance_reporter;

        void PromptEntry(){cout <<endl <<"[Paralel_Dictionary] Enter Command: ";};
        string GetInput();
  
};


#endif