#include "command_line.h"


UserCommandDTO Parser::ParseUserEntry(string _entry){

    stringstream iss(_entry);
    iss >> keyword;
    
    if (keyword == "reset"){ user_command.setOperation(find_entry); Parser::NoArgCheck(_entry,keyword);}
    else if (keyword == "save") { user_command.setOperation(save); Parser::NoArgCheck(_entry,keyword);}
    else if (keyword == "saveexit") { user_command.setOperation(save_and_exit); Parser::NoArgCheck(_entry,keyword);}
    else if (keyword == "exit") { user_command.setOperation(exit_program); Parser::NoArgCheck(_entry,keyword);}
    else{
        if (keyword == "init")
        {
            user_command.setOperation(init);
            user_command.setPayload(Parser::ParseFilename(Parser::ExtractPayload(_entry, keyword)));
            return user_command;
        }
        else if (keyword == "find") {user_command.setOperation(find_entry);}
        else if (keyword == "put") {user_command.setOperation(put_entry);}
        else if (keyword == "delete") {user_command.setOperation(delete_entry);}
        else if (keyword == "update") {user_command.setOperation(update_entry);}
        else { 
            SetParseError();
            return user_command;
        }

        if(_entry.substr(keyword.size(),1)!=" "){
            cout<< endl <<"Space required after keyword";
            SetParseError();
            return user_command;
        }
        payload = Parser::ExtractPayload(_entry, keyword);
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
    
    stringstream iss(_entry);

    iss >> filename;

    cout << "FilenameParser: "<<filename;

    return filename;

}; 

void Parser::NoArgCheck(string _entry, string _keyword){
    if(_entry.size()>_keyword.size()) cout <<endl <<"[Warnnig] Operation " <<_keyword << " must have no arguments. Arguments ignored";

}



int DictServiceInvoker::ExecuteUserCommand(DictQueryDTO& _result, UserCommandDTO _user_command, PerformanceReporter & _performance_reporter){
    
    std::pair<std::string, dictionary::DictionaryError> search_result;

    switch (_user_command.getOperation())
    {
        case find_entry:
            cout <<endl <<"operation find - not yet implemented";
            search_result = dictionary.find(_user_command.getPayload());
            cout <<endl <<"Result: " <<search_result.first <<endl;
            break;
        case put_entry:
            cout <<endl <<"operation put - not yet implemented";
            break;
        case reset:
            cout <<endl <<"operation reset dictionary - not yet implemented";
            break;
        case save_and_exit:
            cout <<endl <<"operation exit and save - not yet implemented";
            break;
        case exit_program:
            cout <<endl <<"operation exit no save";
            return 1;
         case save:
            cout <<endl <<"operation save - not yet implemented";
            break;
        case init:
            cout <<endl <<"operation init from file - not yet implemented; filename: " <<_user_command.getPayload() <<endl;
            DictServiceInvoker::InitDictionaryFromFile(_user_command.getPayload());
            
            break;
    };

    cout <<endl;
   
    return 0;
}

int DictServiceInvoker::InitDictionaryFromFile(string _filename){

    //extern file::FileReader file_reader;

    file::FileReader file_reader{_filename};
    bool read_file_result = file_reader.read_file();
    const auto read_data = file_reader.get_buffer();
    
    cout <<endl <<"InitFromFile data:\n"<<read_data <<endl;

    serialization::DictDeserializer dict_deserializer{read_data};

    bool deserialization_result = dict_deserializer.deserialize();
    if (!deserialization_result) {
        return 1;
    }

    dictionary::Dictionary dictionary{dict_deserializer.get_dictionary()};
    


    return 0;

}


int CommandLine::ProcessUserCommands(){  
    
    int exit_flag = 0;

    do{
        PromptEntry();
        _input = GetInput();
        //performance_reporter.logTime(PerformanceReporter::cp_1);

        user_command = parser.ParseUserEntry(_input);
        cout <<endl <<"Command entered:" <<user_command.getOperation() <<" " <<user_command.getPayload() <<endl;

        exit_flag = invoker.ExecuteUserCommand(query_result, user_command, performance_reporter);

        //performance_reporter.logTime(PerformanceReporter::cp_4);
        //performance_reporter.show_time_report();
    }while(exit_flag == 0);
    return 0;
}


string CommandLine::GetInput(){
    string input_string;        
    getline(cin, input_string);
    return input_string;
}






