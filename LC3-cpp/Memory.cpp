#include "Memory.h"

Memory::status_t Memory::read(uint16 addr, uint16 &data)
{

		data = Memory::dataMem[addr];
		return BUS_OK;

}

Memory::status_t Memory::write(uint16 addr, uint16 data)
{

	Memory::dataMem[addr] = data;
		return BUS_OK;
}



bool Memory::load (std::string file_name)
{
  int i = 1;
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
  //for (int j = 0; j < token.size(); j++)
    //cout<<token[j]<<endl;

  while (i < token.size())
  {
    if (token[i-1] == "A")
    {
      capture = stoi(token[i], nullptr, 0);
      i++;
      //cout<<"capture "<<hex<<capture<<endl;
    } else if (token[i-1] == "D") {
      dataMem[capture] = (uint16)stoi(token[i], nullptr, 16);
      std::cout<<"Data loaded: "<<hex<<dataMem[capture]<<"at: "<<hex<<capture<<std::endl;
      //cout<<hex<<stoi(token[i], nullptr, 16)<<endl;
      //cout<<"mem["<<capture<<"] "<<hex<<mem[capture]<<endl;

      capture++;
      i++;
    } else
      i++;
  }
 // for (uint16 j = 0x3000; j < 0xFFFF; j++)
   // cout<<hex<<mem[j]<<endl;
  return 1;
}
