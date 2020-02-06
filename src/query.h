#include<string>
#include<vector>
#include<sstream>

using namespace std;

class Query{
private:
	

public:
	vector<int> init(vector<int> tm, vector<vector<double> > weight){
	
		vector<int> tmpl = tm;
		
		cout<<tm.size()<<endl;
	
		// query based on the query word
		int docuLength = weight[0].size();
		int queryNumber = tmpl.size();
 		vector<double> qResult(docuLength,0);
		for( int i=0; i<queryNumber; i++){
			for(int j=0;j<docuLength;j++){
				qResult.at(j) += weight.at( tmpl.at(i) ).at(j);
			}
		}
		
		cout<<"This is the query result: "<<endl;
		cout<<"==========================================="<<endl;
		for(int i = 0; i < docuLength; i++){
			cout<<qResult[i]<<" ";
		}
		cout<<endl;
		cout<<"==========================================="<<endl<<endl;
		
		// sort query result and return the ranked list of documents
		int siz = qResult.size();
		double max;
		int index;
		vector<int> rankList;
		while(siz--){
			max = -1;
			index = 0;
			for(int i = 0; i < docuLength; i++){
				if( qResult.at(i) > max ){
					max = qResult.at(i);
					index = i;
				}
			}
			rankList.push_back( index );
			qResult[ index ] = -1;
		}
	
	
		//cout<<"This is the ranked list of document: "<<endl;
		//cout<<"==========================================="<<endl;
		//for(int i=0; i<docuLength; i++){
		//	cout<< rankList.at(i) <<" ";
		//}	
		//cout<<endl;
		//cout<<"==========================================="<<endl;
		return rankList;
	}
};