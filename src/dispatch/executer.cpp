#include "executer.hpp"

#include <ssce/clock.hpp>
#include <structures/dfs/dfs.hpp>

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>

namespace dispatch {
Executer::Executer(const char* input, const char* output, const char* commands, ICommandable* o) {
  in.open(input);
  if(!in.is_open()){
    std::cout<<"Could not open input file: "<<input<<std::endl;
    std::exit(1);
  }
  out.open(output);
  if(!out.is_open()){
    std::cout<<"Could not open output file: "<<output<<std::endl;
    std::exit(1);
  }
  cmd.open(commands);
  if(!cmd.is_open()){
    std::cout<<"Could not open command file: "<<commands<<std::endl;
    std::exit(1);
  }
  obj = o;
}
Executer::~Executer() {
  this->in.close();
  this->out.close();
  this->cmd.close();
}
enum COMMANDS {
  READ_DATA,
  WRITE_INDEX,
  INSERT_LINK,
  DELETE_LINK,
  FIND_NEIGHBORS,
  FIND_NUM_CONNECTED_COMPONENTS
};
struct Command {
  COMMANDS id;
  int data[2];
};
static const char* COMMANDS_STR[] = {"READ_DATA", "WRITE_INDEX", "INSERT_LINK",
                                     "DELETE_LINK", "FIND_NEIGHBORS",
                                     "FIND_NUM_CONNECTED_COMPONENTS"};
#define COMMANDS_STR_SIZE (sizeof(COMMANDS_STR)/sizeof(char*))

static bool decodeNextCommand(std::ifstream &cmd, Command* current) {
  if(cmd.eof() || current==NULL){
    return false;
  }
  //Read next line and decode the command.
  std::string s;
  std::getline(cmd, s);
  if(s.empty()){
    return false;
  }
  //Try decode.
  for(int i = 0; i<(int)COMMANDS_STR_SIZE; i++){
    size_t index = s.find(COMMANDS_STR[i]);
    if(index!=std::basic_string<char>::npos) {
      //Valid command.
      current->id = (COMMANDS) i;
      //Extra data.
      if(i==INSERT_LINK || i==DELETE_LINK) {
        //Both strings also happen to have the same length...
        std::string num = s.substr(sizeof("INSERT_LINK"));
        std::istringstream nums(num);
        int a, b;
        nums>>a>>b;
        current->data[0] = a;
        current->data[1] = b;
      }
      else if(i == FIND_NEIGHBORS) {
        std::string num = s.substr(sizeof("FIND_NEIGHBORS"));
        std::istringstream nums(num);
        nums>>current->data[0];
        current->data[1] = -1;
      }
      else {
        current->data[0] = -1;
        current->data[1] = -1;
      }
      //Done
      return true;
    }
  }
  //Decode fail.
  std::cout<<"Invalid command: "<<s<<std::endl;
  return false;
}

std::ostream& operator<<(std::ostream& stream, const Command& c){
  stream<<COMMANDS_STR[c.id];
  if(c.id==INSERT_LINK || c.id==DELETE_LINK){
    stream<<"("<<c.data[0]<<", "<<c.data[1]<<")";
  }
  else if(c.id == FIND_NEIGHBORS) {
    stream<<"("<<c.data[0]<<")";
  }
  return stream;
}

void Executer::run(bool time){
  ssce::Clock t;
  Command c;
  while(decodeNextCommand(this->cmd, &c)){
    if(time) {
      std::cout<<"Executing command: "<<c<<std::endl;
      t.start();
    }
    bool result = false;
    switch(c.id) {
      case READ_DATA:
        result = obj->readData(this->in);
        break;
      case WRITE_INDEX:
        result = true;
        std::cout<<"I thought this was removed."<<std::endl;
        break;
      case INSERT_LINK:
        result = obj->addLink(c.data[0], c.data[1]) && obj->addLink(c.data[1], c.data[0]);
        break;
      case DELETE_LINK:
        result = obj->delLink(c.data[0], c.data[1]) && obj->delLink(c.data[1], c.data[0]);
        break;
      case FIND_NEIGHBORS:{
          int* array = NULL;
          int count = obj->getNeighbors(c.data[0], &array);
          result = count != -1;
          for(int i=0; i<count; i++) {
            if(i > 0) {
              this->out << " ";
            }
            this->out << array[i];
          }
          this->out << std::endl;
          delete[] array;
        }
        break;
      case FIND_NUM_CONNECTED_COMPONENTS:
        int count = calculateConnectivity(obj);
        result = count != -1;
        this->out << count << std::endl;
        break;
    }
    if(!result) {
      std::cout<<"Could not execute command: "<<c<<std::endl;
      exit(1);
    }
    if(time) {
      t.stop();
      std::cout<<"Execution took "<<std::setprecision(5)<<t.delta<<" milliseconds."<<std::endl;
    }
  }
}
}