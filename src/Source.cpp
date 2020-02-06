#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>
#include <ctime>

using namespace std;


class booleanIR
{
private:
	unordered_map<string, vector<int>> mymap;
	unordered_map<string, int>  docIndex;
	unordered_map<int, string>  indexDoc;
	vector<int> allDoc;
public:
	booleanIR(string file)
	{
		ifstream input(file);
		while(!input){
				cout<<"no file!!!!!!!!" << endl;
				string qq;
				cin >> qq;
				input.open(qq);
		}
		string get;
		string term, doc;
		int tf;
		int count = 0;
		while (getline(input, get))
		{
			string::size_type pos1, pos2;

			pos2 = get.find(' ');
			pos1 = 0;
			doc = get.substr(pos1, pos2 - pos1);
			if (docIndex.find(doc) == docIndex.end())
			{
				docIndex[doc] = count;
				indexDoc[count] = doc;
				allDoc.push_back(count);
				count++;
			}

			pos1 = pos2 + 1;
			pos2 = get.find(' ', pos1);
			term = get.substr(pos1, pos2 - pos1);

			pos1 = pos2 + 1;
			pos2 = get.find(' ', pos1);
			tf = atoi(get.substr(pos1, pos2 - pos1).c_str());
			if (tf != 0)
			{
				if (mymap.find(term) != mymap.end())
				{
					mymap.at(term).push_back(docIndex.at(doc));
				}
				else
				{
					mymap[term].push_back(docIndex.at(doc));
				}
			}

		}
		sort(allDoc.begin(), allDoc.end());
		allDoc.erase(unique(allDoc.begin(), allDoc.end()), allDoc.end());
	}

	vector<int> RetrivalAnd(vector<int> vec1, vector<int> vec2)
	{
		vector<int>result;
		auto it1 = vec1.begin(), it2 = vec2.begin();
		while (it1 != vec1.end() && it2 != vec2.end())
		{
			if (*it1 == *it2)
			{
				result.push_back(*it1);
				it1++;
				it2++;
			}
			else if (*it1 < *it2)
				it1++;
			else it2++;
		}
		return result;
	}

	vector<int> RetrivalOr(vector<int> vec1, vector<int> vec2)
	{
		vector<int>result;
		auto it1 = vec1.begin(), it2 = vec2.begin();
		while (it1 != vec1.end() && it2 != vec2.end())
		{
			if (*it1 == *it2)
			{
				result.push_back(*it1);
				it1++;
				it2++;
			}
			else if (*it1 < *it2)
			{
				result.push_back(*it1);
				it1++;
			}
			else
			{
				result.push_back(*it2);
				it2++;
			}
		}
		while (it1 != vec1.end())
			{
				result.push_back(*it1);
				it1++;
			}
		while (it2 != vec2.end())
		{
			result.push_back(*it2);
			it2++;
		}
		return result;		
		/*vec2.insert(vec2.begin(), vec1.begin(), vec1.end());
		sort(vec2.begin(), vec2.end());
		vec2.erase(unique(vec2.begin(), vec2.end()), vec2.end());
		return vec2;*/
	}

	vector<int> RetrivalNot(vector<int>vec1, vector<int>vec2)
	{

		vector<int>result;
		auto it1 = vec1.begin(), it2 = vec2.begin();
		while (it1 != vec1.end() && it2 != vec2.end())
		{
			if (*it1 == *it2)
			{
				it1 = vec1.erase(it1);
				if (it1 == vec1.end())
					return vec1;
				it2++;
			}
			else if (*it1 < *it2)
				it1++;
			else it2++;

		}
		return vec1;

	}

	vector<int> Retrieval(string terms)
	{
		vector<int>result;
		queue<string> contain;
		string temp1, temp2, temp3;
		string::size_type pos1, pos2;
		result = allDoc;
		terms.erase(0, terms.find_first_not_of(" "));
		terms.erase(terms.find_last_not_of(" ") + 1);
		pos2 = terms.find(' ');
		pos1 = 0;
		while (string::npos != pos2)
		{
			temp1 = terms.substr(pos1, pos2 - pos1);
			if (temp1 == "and" || temp1 == "AND")
			{
				contain.push("a");
			}
			else if (temp1 == "or" || temp1 == "OR")
			{
				contain.push("o");
			}
			else if (temp1 == "not" || temp1 == "NOT")
			{
				contain.push("x");
			}
			else{
				contain.push(temp1);
			}
			pos1 = pos2 + 1;
			pos2 = terms.find(' ', pos1);
		}
		contain.push(terms.substr(pos1));
		/*		while (!contain.empty())
		{
		cout << contain.front() << " ";
		contain.pop();
		}*/
		temp2 = contain.front();
		if (temp2 == "a" || temp2 == "o")
			contain.pop();
		if (temp2 == "x")
		{
			contain.pop();
			result = RetrivalNot(allDoc, mymap.at(contain.front()));
			contain.pop();
		}
		while (!contain.empty())
		{
			temp2 = contain.front();
			contain.pop();
			if (temp2 == "a")
			{
				result = RetrivalAnd(mymap.at(contain.front()), result);
				contain.pop();
			}
			else if (temp2 == "o")
			{
				if (mymap.find(contain.front()) != mymap.end())
				{
					result = RetrivalOr(mymap.at(contain.front()), result);
				}
				contain.pop();
			}
			else if (temp2 == "x")
			{
				result = RetrivalNot(result, mymap.at(contain.front()));
				contain.pop();
			}
			else
			{
				result = RetrivalAnd(mymap.at(temp2), result);
			}
		}



		return result;
	}
	void getResult(vector<int> result)
	{
		for (int i = 0; i < result.size(); i++)
		{
			cout << i+1 << ": " << indexDoc.at(result[i]) << " " << endl;;

		}
		
	}
};




void main()
{
	
	double startime,endtime;
	string term1;
	string file;
	cout << "Please input the name of the file."<<endl;	
	cin >> file;
	booleanIR a(file);
	string retrieval;
	vector<int> b, c, d, e;
	/*string term = "real and rates"; // 0,3
	string term2 = "rates";//1,3,4
	vector<string> result, result1;
	b = { 0, 1, 2, 3, 4 };
	c = { 0, 3 };
	d = { 1, 2, 3 };*/
	while (1)
	{
		cout << "Please input the terms will be queried using space to separate" << endl;
		getline(cin, term1);
		startime = clock();
		if (term1 == "exit")
			break;

		try
		{
			e = a.Retrieval(term1);
			if (!e.empty())
			{
			/*	for (int i = 0; i < e.size(); i++)
					cout << e[i] << " ";*/
				a.getResult(e);
				endtime = clock();
				cout <<"retrieval time:"<< (endtime - startime) / CLOCKS_PER_SEC*1000 <<"ms"<< endl;
				startime = 0;
				endtime = 0;
			}
			else
				cout << "no result return1" << endl;
		}
		catch (exception)
		{
			cout << "no result return2" << endl;
		};
	}

}