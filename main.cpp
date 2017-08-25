#include <iostream>
#include <cmath>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <algorithm> //sort

using namespace std;

void print_parsed_results(int cases, vector<int> tgtSum, vector<vector<int> >* set) {
	for (int i = 0; i < cases; i++) {
		cout << "CASE " << i << endl;
		cout << "tgt sum: " << tgtSum[i] << endl;
		cout << "set:" << endl;
		for (int j = 0; j < (*set)[i].size(); j++) {
			cout << (*set)[i][j] << ", ";
		}
		cout << endl << endl;
	}
}

/* //code taken from online,
//http://comproguide.blogspot.com/2013/10/subset-sum-problem.html
bool subset_sum2(int tgtSum, const vector<int> set) {



	//create and initialize the map
	bool map[tgtSum+1][set.size()+1];
	for (int i = 0; i < set.size()+1; i++) {
		map[0][i] = true;
	}
	for (int i = 0; i < tgtSum; i++) {
		map[i][0] = false;
	}
	
	//double loop, assigning 
	for (int i = 0; i < tgtSum; i++) {
		for (int j = 1; j < set.size()+1; j++) {
			//cout << i << " " << j << endl;
			map[i][j] = map[i][j-1];
			if ((!map[i][j]) && i >= set[j-1]) {
				map[i][j] = map[i-set[j-1]][j-1];
			}
		}
	}
	return map[tgtSum][set.size()];
} */

//base code taken from lecture, modified and debugged until working
bool subset_sum(int tgtSum, const vector<int> set){

	//initialize
	bool T[tgtSum+1];
	for (int i = 0; i < tgtSum; i++)
		T[i] = false;
	T[0] = true;
	
	//perform magic
	for (int i = 0; i < set.size(); i++) {
		//it was driving my crazy until i added the = to <=
		for (int j = 0; j <= tgtSum - set[i]; j++) {
			if (T[j] == true) {
				T[j + set[i]] = true;
				if (j + set[i] == tgtSum)
					 return true;
			}
		}
	}
	return false;
}


//assign data stuctures, parse data directly from file, call functions on it
int main() {

	ifstream txt;
	
	//holds num cases in txt file
	int cases;
	//holds a sum to be added to tgtsum vector
	int thisTgtSum;
	//will hold the int to be placed into the set
	string temp = "";
	//cant parse a getline into an int, so this will hold the line as a string
	string getlineTemp;
	//vector of tgtsums
	vector<int> tgtSum;
	//vector of sets
	vector< vector<int> >* set = new vector< vector<int> >();
	
	txt.open("subset.txt");
	if (txt.is_open()) {
		//get # cases
		getline(txt,getlineTemp);
		cases = atoi(getlineTemp.c_str());
		//loop for each case
		for (int i = 0; i < cases; i++) {
			//get the tgt sum for this case, push it to tgt sum array
			getline(txt,getlineTemp);
			thisTgtSum = atoi(getlineTemp.c_str());
			tgtSum.push_back(thisTgtSum);
			//get the set for this case, parse each int out, add it to the set for this case
			getline(txt,getlineTemp);
			vector<int> v;
			for (int j = 0; j < strlen(getlineTemp.c_str()); j++) {
				if (getlineTemp[j] == ' ') {
					v.push_back(atoi(temp.c_str()));
					//cout << "whole temp found, case " << i << " as " << temp << endl;
					//clear temp
					temp = "";
				} else {
					temp += getlineTemp[j];
				}
			}
			v.push_back(atoi(temp.c_str()));
			//cout << "whole temp found, case " << i << " as " << temp << endl;
			//clear temp
			temp = "";
			//cout << "length of vector for case " << i << " is " << v.size() << endl;
			set->push_back(v);
		}
		txt.close();
	} else {
		cout << "couldn't open input file!" << endl;
		return 0;
	}
	
	print_parsed_results(cases, tgtSum, set);
	
	//print the case, and the result from running subset sum on that case
	for (int i = 0; i < cases; i++) {
		cout << "Case " << i << ": ";
		if (subset_sum(tgtSum[i],(*set)[i])) {
			cout << "true" << endl;
		} else {
			cout << "false" << endl;
		}	
	}
	
}