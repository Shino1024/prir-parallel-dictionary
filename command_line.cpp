
#include "command_line.h"

UserCommandDTO Parser::ParseUserEntry(string _entry){
    keyword = _entry.substr(0,3);

    if (keyword == "res"){ user_command.setOperation(res); NoArgCheck(_entry);}
    else if (keyword == "sav") { user_command.setOperation(sav); NoArgCheck(_entry);}
    else if (keyword == "exs") { user_command.setOperation(exs); NoArgCheck(_entry);}
    else if (keyword == "exn") { user_command.setOperation(exn); NoArgCheck(_entry);}
    else{
        if (keyword == "ini") {user_command.setOperation(ini);}
        else if (keyword == "fnd") {user_command.setOperation(fnd);}
        else if (keyword == "put") {user_command.setOperation(put);}
        else if (keyword == "del") {user_command.setOperation(del);}
        else if (keyword == "upd") {user_command.setOperation(upd);}
        else { 
            SetParseError();
            return user_command;
        }

        if(_entry.substr(3,1)!=" "){
            cout<< endl <<"Space required after keyword";
            SetParseError();
            return user_command;
        }
        payload = _entry.substr(4,_entry.size()-4);
        user_command.setPayload(payload);
    }
    return user_command;
}

void Parser::SetParseError()
{
    user_command.setOperation(unknown);
    user_command.setPayload("Invalid entry.\n");
};

string Parser::ParseFilename(string _entry){
    string filename;
    
    filename = _entry;

    cout << "\nFilenameParser: "<<filename;

    return filename;

}; 



int DictServiceInvoker::ExecuteUserCommand(QueryResultDTO& _result, UserCommandDTO _user_command, PerformanceReporter & _performance_reporter){
    
    switch (_user_command.getOperation())
    {
        case fnd:
            cout <<endl <<"operation find";
            break;
        case put:
            cout <<endl <<"operation put";
            break;
        case res:
            cout <<endl <<"operation reset dictionary";
            break;
        case exs:
            cout <<endl <<"operation exit and save";
            break;
        case exn:
            cout <<endl <<"operation exit no save";
            break;
        case sav:
            cout <<endl <<"operation save";
            break;
        case ini:
            cout <<endl <<"operation init from file; filename: " <<_user_command.getPayload() <<endl;
            break;
    };

    cout <<endl;
   
    return 0;
}

int CommandLine::ProcessUserCommand(){  
    PromptEntry();
    _input = GetInput();
    performance_reporter.logTime(PerformanceReporter::cp_1);

    user_command = parser.ParseUserEntry(_input);
    cout <<endl <<"Command entered:" <<user_command.getOperation() <<" " <<user_command.getPayload() <<endl;

    invoker.ExecuteUserCommand(query_result, user_command, performance_reporter);

    performance_reporter.logTime(PerformanceReporter::cp_4);
    performance_reporter.show_time_report();
    return 0;
}


string CommandLine::GetInput(){
    string input_string;        
    getline(cin, input_string);
    return input_string;
}






