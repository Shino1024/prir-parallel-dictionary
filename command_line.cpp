#include "command_line.h"
#define SNAPSHOT_FILENAME "dictionary_snapshot.csv"



UserCommandDTO Parser::ParseUserEntry(string _entry){

    stringstream iss(_entry);
    iss >> keyword;
    user_command.setPayload("");

    if (keyword == "reset"){ user_command.setOperation(reset); Parser::NoArgCheck(_entry,keyword);}
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

        payload = Parser::ExtractPayload(_entry, keyword);

        if(payload.size()<1){
            SetParseError();
            cout<<"[ERROR]: Argument required!";
            return user_command;
        }
        
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

DictQueryDTO Parser::ParseDictionaryEntry(string _entry){
    DictQueryDTO query;
    string key;        
    stringstream iss(_entry);

    iss >> key;

    
    query.setKey(key);
    query.setValue(Parser::ExtractPayload(_entry,key));
    
    cout <<endl <<"[ParseDictionaryEntry] Key: "<<query.getKey() <<" Value: " <<query.getValue();

    return query;

}; 



void Parser::NoArgCheck(string _entry, string _keyword){
    if(_entry.size()>_keyword.size()) cout <<endl <<"[Warnnig] Operation " <<_keyword << " must have no arguments. Arguments ignored";

}



int DictServiceInvoker::ExecuteUserCommand(DictQueryDTO& _result, UserCommandDTO _user_command, PerformanceReporter & _performance_reporter){
    
    //std::pair<std::string, dictionary::DictionaryError> search_result;

    switch (_user_command.getOperation())
    {
        case find_entry:
            {
                cout <<endl <<"operation find";
                _performance_reporter.logTime(PerformanceReporter::cp_2);
                auto search_result = dictionary.find(_user_command.getPayload());
                _performance_reporter.logTime(PerformanceReporter::cp_3);
                cout <<endl <<"Result: " <<search_result.first <<endl;
                break;
            }
        case put_entry:
            {
                cout <<endl <<"operation put";
                auto query = Parser::ParseDictionaryEntry(_user_command.getPayload());
                PutDictionaryEntry(query);

                break;
            }
        case delete_entry:
            {
                cout <<endl <<"operation delete";
                if(dictionary.remove(_user_command.getPayload())== dictionary::DictionaryError::NonexistentKeyError)
                    cout <<endl <<"ERROR: Key not found\n";
                break;
            }

        case update_entry:
            {
                cout <<endl <<"operation update";
                auto query = Parser::ParseDictionaryEntry(_user_command.getPayload());
                if(dictionary.update(query.getKey(), query.getValue())== dictionary::DictionaryError::NonexistentKeyError)
                    cout <<endl <<"ERROR: Key not found\n";
                break;
            }
        
        case reset:
            cout <<endl <<"operation reset dictionary";
            dictionary.clear();

            break;
        case save_and_exit:
            cout <<endl <<"operation exit and save\n";
            SaveDictionary();
            return 1;
        case exit_program:
            cout <<endl <<"operation exit without saving\n";
            return 1;
         case save:
            cout <<endl <<"operation save\n";
            SaveDictionary();
            break;
        case init:
            cout <<endl <<"operation init from file; filename: "; //<<_user_command.getPayload() <<endl;
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
        cout <<endl <<"[ERROR]:Initialization from file failed\n";
        return 1;
    }

    this->dictionary = dict_deserializer.get_dictionary();

    return 0;
}

int DictServiceInvoker::PutDictionaryEntry(DictQueryDTO _query){
    if(this->dictionary.insert(_query.getKey(), _query.getValue()) == dictionary::DictionaryError::AlreadyExistingKeyError){
        cout <<endl <<"ERROR: Key already exist\n";
        return 1;
    }
    return 0;
   
};

int DictServiceInvoker::SaveDictionary(){
    serialization::DictSerializer dict_serializer{this->dictionary};
    dict_serializer.serialize();
    const std::string serialized_dictionary_data{dict_serializer.get_data()};

    const std::string file_filename{SNAPSHOT_FILENAME};

    file::FileWriter mock_file_writer{file_filename};

   
    mock_file_writer.set_buffer(serialized_dictionary_data);
    bool write_file_result = mock_file_writer.write_file();
    
    return 0;


}



int CommandLine::ProcessUserCommands(){  
    
    int exit_flag = 0;

    
    invoker.InitDictionaryFromFile(SNAPSHOT_FILENAME);

    do{
        PromptEntry();
        _input = GetInput();
        performance_reporter.logTime(PerformanceReporter::cp_1);

        user_command = parser.ParseUserEntry(_input);
        cout <<endl <<"Command entered:" <<user_command.getOperation() <<" " <<user_command.getPayload() <<endl;

        exit_flag = invoker.ExecuteUserCommand(query_result, user_command, performance_reporter);

        performance_reporter.logTime(PerformanceReporter::cp_4);
        performance_reporter.show_time_report();
    }while(exit_flag == 0);
    return 0;
}


string CommandLine::GetInput(){
    string input_string;        
    getline(cin, input_string);
    return input_string;
}






