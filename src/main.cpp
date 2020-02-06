#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<iomanip>
#include<cmath>
#include<map>
#include<iostream>

#include"scanner.h"
#include"query.h"


using namespace std;

int main(){

	vector<vector<double> > weight;
	vector<string> term;
	vector<string> nameOfDoc;

	// scanner to scan documents
	Scanner scanner;
	if(scanner.scan()){
		ifstream input;
		stringstream ss;
		//the first line of result.txt 
		//which sotres total number of terms and documents
		string firstLine;
		// total number of terms
		int numberOfTerm;
		//total number of documents
		int numberOfDoc;


		
		input.open("IndexOfTerm.txt");
		while(!input.eof()){
			string t1;
			input>>t1;
			term.push_back(t1);
		}
		input.close();
		
		input.open("IndexOfDoc.txt");
		while(!input.eof()){
			string t2;
			int i;
			input >> i;
			input >> t2;
			nameOfDoc.push_back(t2);
		}
		input.close();

		numberOfTerm = term.size();
		numberOfDoc = nameOfDoc.size();



		input.open("result.txt");			
		
			
		//weight table, the size of weight table read from result.txt
		
		for( int i = 0; i < numberOfTerm; i++){
			vector<double> dv;
			double d;
			for( int j = 0; j < numberOfDoc; j++){
				input>>d;
				dv.push_back(d);
			}
			weight.push_back(dv);
		}

		input.close();


	}

	
	
	
	Query q;
	
	//store query word;
	string query;
	
	while(1){
		// acquire the query word
		cout<<"pleas input the query word"<<endl;
	
		getline(cin,query);
		
		stringstream ss;
		ss<<query;
		vector<string> tmpl;
		vector<string>::iterator s_It;
		vector<int> tm;
		string tmp;
		while(!ss.eof()){
			ss>>tmp;
			tmpl.push_back(tmp);
		}
		int numberOfTerm = term.size();
		for( s_It = tmpl.begin(); s_It != tmpl.end(); s_It++){
			for(int i = 0; i < numberOfTerm; i++){
				if( *s_It == term[i] ){
					tm.push_back(i);
				}
			}
		}

		//do the query
		vector<int> re = q.init(tm,weight);
		vector<int>::iterator i_It;
		cout <<"Ranked documents name are: "<<endl;
		cout << "==========================" << endl;
		for( i_It = re.begin(); i_It != re.end(); i_It++){
			cout << nameOfDoc[ *i_It ] << endl;
		}
		cout << "==========================" << endl;
		cout<<endl;
	}



	system("pause");
	return 0;
}