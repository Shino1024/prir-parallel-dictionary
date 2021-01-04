#include <iostream>

using namespace std;

/*
Class UserCommand

Class represents DTO used for calling Dictionary Services. Consists of two elements:
# command - takes values 'r'  for read/find or 'w' for insert
# payload - searched string or dictionary entry to be inserted
*/

class UserCommandDTO{

    public:
        char getOperation(){return this->operation;}
        string getPayload(){return this->payload;}

        void setOperation(char _operation){ this->operation = _operation;}
        void setPayload(string _payload){ this->payload = _payload;}

    private:    
        char operation;
        string payload;
};

/*
Interface between Dictionary and User Interface. This DTO definition should be global.
*/

class QueryResultDTO{

    public:
        int getKey(){return this->key;}
        string getValue(){return this->value;}

        void setKey(int _key){ this->value = _key;}
        void setValue(string _value){ this->value = _value;}

    private:    
        int key;
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

};


/*
Class DictServiceInvoker
Encapsulates Dictonary Services Client Logic.

*/

class DictServiceInvoker{

    public:
        int ExecuteDictQuerry(QueryResultDTO&, UserCommandDTO);

};



/*
Class CommandLine
Enables main User Interface method GetUserCommand. Presents prompt, parses input and calls dictionary services: find and insert.

*/

class CommandLine{

    public:
        int GetUserCommand();

    private:
        Parser parser;
        string _input;
        UserCommandDTO user_command;

        void PromptEntry();
        string GetInput();
  
};