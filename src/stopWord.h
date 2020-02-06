#ifndef _H_STOPWORD_
#define _H_STOPWORD_

#include<string>
#include<vector>
#include<fstream>
using namespace std;

class StopWord{
private:
	vector<string> list;
public:
	StopWord(){
		ifstream input;
		input.open("stop.txt");
		if(input){
			while(!input.eof()){
				string tmp;
				input >> tmp;
				list.push_back(tmp);
			}
		}
		input.close();
		

	}

	bool isStop(string input){
		vector<string>::iterator s_It;
		for(s_It = list.begin(); s_It != list.end(); s_It++){
			if(*s_It == input)
				return true;
		
		}
		return false;
	}
};


#endif