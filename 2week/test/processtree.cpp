/*
*NOTE:
*Take care of the issue about memory leak
*because you request for heap but didn't freed them in the main.
*There won't be any problem unless you modulize this code for other use.
*/
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;

vector<struct process*>::iterator 
find_parent(vector<struct process*>::iterator first, vector<struct process*>::iterator last, const unsigned int& number);
vector<struct process*>::iterator 
find_id(vector<struct process*>::iterator first, vector<struct process*>::iterator last, const unsigned int& number);

struct process{
	unsigned int pid;
   unsigned int parent_id;
   vector<unsigned int> sibling_id;
   vector<unsigned int> child_id;
};

int main(){

   vector<struct process*> the_process;
	vector<struct process*>::iterator it;
   vector<struct process*>::iterator parent;
   struct process* oneprocess;
	ifstream file;
	file.open("psOutput.log");

   if(!file.is_open())exit(-1);
   char oneline[1024];
   file.getline(oneline,1024);
   while(file.getline(oneline,1024)){
//cout << oneline<<endl;
//cout << "begin\n";
      size_t i = 0;
		int space = 0;
		string id = "";
//cout << "oneline[i]=" << oneline[i]<<endl;
		while(oneline[i] != '/'){
			if(oneline[i] == ' ' && oneline[i+1] != ' '){
   			space++;
				switch(space){
					case 2:{
						unsigned int number = stoul(id,nullptr,0);
						id = "";
						it = find_id(the_process.begin(), the_process.end(), number);
						if(it == the_process.end()){
							process* the = new process();
                     the -> pid = number;
							the -> parent_id = number;
							the_process.push_back(the);
							oneprocess = the_process.back();
						}
						break;
					}
					case 3:{
						unsigned int number = stoul(id,nullptr,0);
						id = "";
						oneprocess -> parent_id = number;
						if(number > 0){
                  	parent = find_id(the_process.begin(), the_process.end(), number);
                  	if(parent == the_process.end())cerr << "error: no parent!!\n";
                  	(*parent) -> child_id.push_back(oneprocess -> pid);
						}	
						break;
					}
					case 4:{
						unsigned int number = stoul(id,nullptr,0);
						if(number != oneprocess -> pid){//cout <<"test1"<<endl;
							oneprocess -> sibling_id.push_back(number);}
					   break;
					}
					
				}
			}	
			i++;
			if(oneline[i] == ' ')continue;
			if(space >= 1)id += oneline[i];
         if(space == 4)break;
 
         
		}
   }

   for(size_t i =0; i < the_process.size();i++){
		cout << "PID: " << the_process[i] -> pid << " PPID: " << the_process[i] -> parent_id << " \nsibling:";
		for(size_t j = 0;j < the_process[i] -> sibling_id.size();j++)
			cout << " " << the_process[i] -> sibling_id[j];
		cout << "\nchild:";
      for(size_t j = 0;j < the_process[i] -> child_id.size();j++)
			cout << " " << the_process[i] -> child_id[j];
		cout << endl;
   }
   return 0;
}

vector<struct process*>::iterator
find_id(vector<struct process*>::iterator first, vector<struct process*>::iterator last, const unsigned int& number){
	while(first != last){
		if((*first) -> pid == number)return first;
		first++;
	}
	return last;
} 


