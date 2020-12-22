
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
Class Parser

Enables Parse method which converts entry string into UserCommand object. Contains parsing logic.
TBD: Exception handling, space truncating etc. 

*/

class Parser{
     
    public:
        UserCommandDTO ParseUserEntry(string _entry){
            keyword = _entry.substr(0,3);
            
            if(keyword == "get") user_command.setOperation('r');
                else if (keyword == "put") user_command.setOperation('w');
                    else
                    { 
                        ReturnParseError();
                        return user_command;
                    }

            if(_entry.substr(3,1)!=" "){
                cout<< endl <<"Space required after keyword";
                ReturnParseError();
                return user_command;
            }

            payload = _entry.substr(4,_entry.size()-4);

            user_command.setPayload(payload);

            return user_command;
        }

    private:
        UserCommandDTO user_command;
        string keyword;
        string payload;
        void ReturnParseError()
        {
                user_command.setOperation('e');
                user_command.setPayload("Invalid entry. Type get [searched string] or put [string to be inserted]\n");
        };

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
Class DictServiceInvoker

Encapsulates Dictonary Services Client Logic.

*/

class DictServiceInvoker{

    public:
        int ExecuteDictQuerry(QueryResultDTO& _result, UserCommandDTO _user_command){
            if(_user_command.getOperation() == 'r')
            {
                /*
                    Dictionary find / search invocation
                */
            }else if(_user_command.getOperation() == 'w')
                /*
                    Dictionary find / search invocation
                */

            return 0;
        }


};



/*
Class CommandLine

Enables main User Interface method GetUserCommand. Presents prompt, parses input and calls dictionary services: find and insert.

*/

class CommandLine{

    public:
        int GetUserCommand(){  
            PromptEntry();
            _input = GetInput();
            user_command = parser.ParseUserEntry(_input);
            cout <<endl <<user_command.getOperation() <<" " <<user_command.getPayload();
            return 0;
        }

    private:
        Parser parser;
        string _input;
        UserCommandDTO user_command;

        void PromptEntry(){
            cout <<endl <<"[Paralel_Dictionary] Enter Command: ";
        }

        string GetInput(){
            string input_string;        
            getline(cin, input_string);
            return input_string;
        }
  
};





