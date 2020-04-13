//
//  CommandProcessor.cpp
//  Assignment4
//
//  Created by rick gessner on 2/15/20.
//

#include "CommandProcessor.hpp"


namespace ECE141 {

  CommandProcessor::CommandProcessor() {}
  CommandProcessor::CommandProcessor(const CommandProcessor &aCommand) {
      *this = aCommand;
  }
  CommandProcessor& CommandProcessor::operator=(const CommandProcessor &aCommand) {
      *this = aCommand;
      return *this;
}

  bool CommandProcessor::run(std::string &aCommand, Model &aModel, std::ostream &anOutput) {
    //STUDENT -- Run your query and send your output to the output stream ...
      ModelQuery theQuery = aModel.query();
      anOutput << "Write your results here...\n";
      int index;
      std::string commands = aCommand;

      while ((index = commands.find(" ")) != -1){
          std::string command = commands.substr(0, index);
          commands = commands.substr(index + 1);
          std::vector<std::string> param;

          if (command.find("(") != -1){
              index = command.find("(");
              try{
                  param.push_back(command.substr(index + 1, command.find(")") - index - 1));
              }
              catch (...){
                  return false;
              }
              command = command.substr(0, index);
          }

          if (commands.c_str()[0] == '"'){
              index = commands.find(" ");
              param.push_back(commands.substr(1, index - 2));
              commands = commands.substr(index + 1);
          }

//          anOutput << command  << " " << param[0] << "\n";
//          anOutput << command.substr(0, 3) << std::endl;
//          anOutput << commands << "\n";

          if (strcmp(command.c_str(), "within") == 0){
              theQuery.within(param[0]);
          }
          else if (strcmp(command.c_str(), "before") == 0){
              theQuery.before(param[0]);
          }
          else if (strcmp(command.c_str(), "after") == 0){
              theQuery.after(param[0]);
          }
          else if (strcmp(command.c_str(), "all") == 0){
              theQuery.all(param[0]);
          }
          else if (strcmp(command.c_str(), "first") == 0){
              theQuery.first(param[0]);
          }
          else if (strcmp(command.c_str(), "last") == 0){
              theQuery.last(param[0]);
          }
          else if (strcmp(command.c_str(), "nth") == 0){
              try{
                  int n = std::stoi(param[0]);
                  std::string s = "*";
                  if (param.size() > 1)
                      s = param[1];
                  theQuery.nth(s, n);
              }
              catch(...) {
                  return false;
              }
          }
          else{
              return false;
          }
      }


      try{
          std::string command = commands.substr(0, commands.find("("));
          std::string param = "";

          if ((index = commands.find("\"")) != -1)
              param = commands.substr(commands.find("\"") + 1, commands.find_last_of("\"") - commands.find("\"") - 1);

//          anOutput << command  << " " << param << "\n";

          if (strcmp(command.c_str(), "count") == 0){
              if (strcmp(param.c_str(), "") != 0)
                  return false;
              anOutput << theQuery.count() << std::endl;
          }
          else if (strcmp(command.c_str(), "sum") == 0){
              anOutput << theQuery.sum(param) << std::endl;
          }
          else if (strcmp(command.c_str(), "avg") == 0){
              anOutput << theQuery.avg(param) << std::endl;
          }
          else if (strcmp(command.c_str(), "get") == 0){
              if (strcmp(param.c_str(), "") == 0){
                  ModelCollection* collection = theQuery.get();
                  anOutput << (*collection)  << std::endl;
              }

              else{
                  anOutput << theQuery.get(param) << std::endl;
              }
          }
          else{
              return false;
          }
      }
      catch (...){
          return false;
      }

      return true;
  }

}
