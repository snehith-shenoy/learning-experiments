#include "Memory.h"



Memory::Memory(sc_module_name nm): sc_module(nm),dataMem(MEM_SIZE){}


bool Memory::load (std::string file_name)
{
  unsigned int i = 1;
  ifstream obj;
  std::string line;
  uint16 capture;
  vector<string> token;

  obj.open (file_name, ios::in | ios::app | ios::out);

  while(getline(obj, line))
  {
    if (line[0] != '#') {
      if ((line[0] == 'A') || (line[0] == 'D')) {
        stringstream word (line);
        string new_words;
        while(word >> new_words)
          token.push_back(new_words);
      }
    }
  }

  while (i < token.size())
  {
    if (token[i-1] == "A")
    {
      capture = stoi(token[i], nullptr, 0);
      i++;

    } else if (token[i-1] == "D") {
      dataMem[capture] = (uint16)stoi(token[i], nullptr, 16);
      std::cout<<"Data loaded: "<<hex<<dataMem[capture]<<"  @ "<<hex<<capture<<std::endl;


      capture++;
      i++;
    } else
      i++;
  }

  return 1;
}
