
#include<string>
#include<fstream>
#include<map>
#include<vector>

#include"stemming.h"
#include"stopWord.h"

using namespace std;

class Scanner{
private:
	

	
public:
	bool scan(){
		ifstream input;
		ofstream output;
	
		// index - document
		vector<string> nameOfDoc;
		int numberOfDoc;
		
		// index - term
		vector<string> term;
		vector<string>::iterator s_It;
		int numberOfTerm;

		// map term to frequency
		map<string,int> tf ;
		map<string,int>::iterator m_It;

		//map indexOfterm to frequancy
		map<int,int> itf;
		map<int,int>::iterator m2_It;



		/*
		============================
			1.Read documents start
		===============================
		*/
		
		//read document index 
		input.open("IndexOfDoc.txt");
		if(input){
			while(!input.eof()){
				int index;
				string doc;
				input >> index;
				input >> doc;

				nameOfDoc.push_back(doc);
			}
		}
		input.close();
		numberOfDoc = nameOfDoc.size();

		/*
		==============================
			2. Scan each document, return "term-fre"  table of each document;
			   Use this "t-f" table to update "term-index" table
			   Change "term-fre" to "indexOfterm-fre" by using "term-index"  
		===============================
		*/


		//scan each document
	
		int i = 0;
		//if test.txt exists, clear it
		output.open("test.txt");
		
		output.close();

		while(i<numberOfDoc){

			// " term - frequency " in each document
			tf = begin(".\\Library\\" + nameOfDoc[i]);
			
			// update " term - index " table 
			// change " term - frequancy " to 
			//		  " term index - frequancy"
			for( m_It = tf.begin(); m_It != tf.end(); m_It++){
				for( unsigned int i = 0; i < term.size(); i++){
					if ( m_It->first == term[i] ){
						itf.insert(pair<int,int>(i,m_It->second));
						break;
					}
				}
				term.push_back( m_It->first );
				itf.insert(pair<int,int>(term.size()-1,m_It->second));
			}
		
			//write result to file, style:
			// document index -- term index -- frequancy
		
			output.open("test.txt",ios::app);
			for( m2_It = itf.begin(); m2_It != itf.end(); m2_It++){
				output << i << " "				//document's index
					<< m2_It->first << " "		//term's index
					<< m2_It->second << " "		//term's frequency
					<< endl;
			}
			itf.clear();
			output.close();

			i++;
		}


		
		/*
		=================================================
			3. Scanner ends!!!
				Result: test.txt
				
		=================================================
		*/

		

		//get the inverted term index
		numberOfTerm = term.size();
		int m = numberOfTerm;
		int n = numberOfDoc;
		vector<vector<double> > weightTable(m, vector<double>(n,0));
		input.open("test.txt");
		if(input){
			while( !input.eof() ){
				int doc;
				int term;
				int tf;
				input >> doc;
				input >> term;
				input >> tf;

				weightTable[term][doc] = tf;		
			}	
		}		
		input.close();
	
		//use weightTable to caculate idf
		for( int i = 0; i < m; i++){
			//for each term, count = how many doc have this term
			int count = 0;	 
			for( int j = 0; j < n; j++){
				if( weightTable[i][j] > 0 ){
					count++;
				}
			}
			//count inverse document frequncy
			double idf = log((double)n/count)/log(2.0);
			//weight = term frequency * inverse documetn frequency
			for( int j = 0; j < n; j++){
				weightTable[i][j] *= idf;				
			}
		}
	

		//normalized weight table
		double len = 0;
		for(int j=0;j<n;j++){
			for(int i=0;i<m;i++){
				len += weightTable.at(i).at(j)*weightTable.at(i).at(j);
			}
			len = pow(len,0.5);

			for(int i=0;i<m;i++){
				weightTable.at(i).at(j)=weightTable.at(i).at(j) / len;
			}

			len = 0;
		
		}

		// write normalized weight table to result.txt
		output.open("result.txt");
	
		for( int i = 0; i < m; i++){
			for( int j = 0; j < n; j++){
				output << weightTable[i][j] << " ";
			}
			output << endl;
		}
		output.close();


		output.open("IndexOfTerm.txt");
		// first line: count(term) + count(document)
		for(s_It =term.begin(); s_It!=term.end(); s_It++ ){
			output << *s_It <<endl;
		}
		output.close();


		return true;
	}


	map<string,int> begin(string file){

		ifstream input;
		string tmp;
		map<string,int> m;
		map<string, int>::iterator m_It;
		Stem stem;
		StopWord sw;


		input.open(file);
		if(input){
			
			while( !input.eof() ){
				input >> tmp;

				//clean tmp
				tmp = clean(tmp);
				//return true is tmp is a stop word
				if( sw.isStop(tmp) ){
					//do nothing!
				}
				else{
					// do the stemming
					tmp = stem.stemming(tmp);

					m_It = m.find(tmp);
					if(m_It == m.end() ){ 	
						m.insert( pair<string,int>(tmp,1) );
					}
					else{
						m[tmp]++;
					}
				
				}
			
			}// while( !input.eof() ){  end 

			//for(m_It = m.begin(); m_It != m.end(); m_It++){
			//	cout << m_It->first << " " 
			//		<< m_It->second << endl;
			//}

			
			input.close();
			return m;
		}
		else{
			input.close();
			return m;
		}
		
	
	}//end begin

	//  A->a     It's -> its
	string clean(string input){
		string tmp;
		int le = input.length();
		for( int i = 0; i < le; i++ ){
			char c = input[i];
			if( 'a'<=c && c<='z' ){
				tmp += c;
			}
			else if ( 'A'<=c && c<='Z' ){
				tmp += c - 'A' + 'a';
			}

		}

		return tmp;
	}
};