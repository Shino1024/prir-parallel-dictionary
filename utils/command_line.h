#ifndef PRIR_COMMAND_LINE
#define PRIR_COMMAND_LINE

#include <iostream>
#include "performance_reporter.h"
#include <bits/stdc++.h>
#include <utils/file.h>
#include <vector>
#include <dictionary/dictionary.h>
#include <utils/serialization.h>
#include <parallel/finder.h>

using namespace std;

enum UserOperation{
    find_entry,
    parallel_find_entry,
    delete_entry,
    put_entry,
    init,
    reset,
    save_and_exit,
    exit_program,
    save,
    update_entry,
    unknown,
};


/*
Class UserCommand

Class represents DTO used for calling Dictionary Services. Consists of two elements:
# command - takes values 'r'  for read/find or 'w' for insert
# payload - searched string or dictionary entry to be inserted
*/

class UserCommandDTO {

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

class DictQueryDTO {

    public:
        string getKey(){return this->key;}
        string getValue(){return this->value;}

        void setKey(string _key){this->key = _key;}
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

class Parser {
     
    public:
        UserCommandDTO ParseUserEntry(string);
        static DictQueryDTO ParseDictionaryEntry(string _entry);

    private:
        UserCommandDTO user_command;
        string keyword;
        string payload;
        void SetParseError();
        static void NoArgCheck(string, string);
        static string ParseFilename(string); 
        static string ExtractPayload(string _entry, string _keyword){return _entry.substr(_keyword.size()+1,_entry.size()-_keyword.size());};
        
};


/*
Class DictServiceInvoker
Encapsulates Dictonary Services Client Logic.

*/

class DictServiceInvoker {

    
    public:
        int ExecuteUserCommand(DictQueryDTO&, UserCommandDTO, PerformanceReporter &);
        int InitDictionaryFromFile(string);
        int SaveDictionary();
        int PutDictionaryEntry(DictQueryDTO);
    private:
        dictionary::Dictionary dictionary;
        parallel::Finder finder{dictionary};

};



/*
Class CommandLine
Enables main User Interface method GetUserCommand. Presents prompt, parses input and calls dictionary services: find and insert.

*/

class CommandLine {

    public:
        int ProcessUserCommands();

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

#endif // PRIR_COMMAND_LINE
