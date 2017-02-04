#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
using namespace std;

struct Person{
	string name;
	bool status;
	Person(){}
	Person(string sname,bool stat){
		name = sname;
		status = stat;
	}
};

vector<Person> currentList;
map<string, bool> Index;
map<string, int> posIndex; 
char op[1010];

inline void cls(){
	system("clear");
}

inline void loadData(){
	ifstream fin("blackList.data");
	currentList.clear();
	Index.clear();
	posIndex.clear();
	string sname;
	int cpos = 0;
	while(fin>>sname){
		if(!Index[sname]){
			Index[sname] = true;
			posIndex[sname] = cpos++;
			currentList.push_back(Person(sname,true));
		}
	}
}

inline vector<string> parseNames(string k){
	string x;
	vector<string> v;
	k += ',';
	for(int i=0;i<k.size();++i){
		if(k[i] == ','){

			v.push_back(x);
			x = "";
			continue;
		}else{
			x += k[i];
		}
	}
	return v;
}

inline void addUser(){
	puts("输入用户名，以逗号分隔:P");
	string name;
	int cpos = currentList.size();
	cin>>name;
	vector<string> nameList = parseNames(name);
	for(int i=0;i<nameList.size();++i){
		name = nameList[i];
		if(!Index[name]){
			Index[name] = true;
			posIndex[name] = cpos++;
			currentList.push_back(Person(name,true));
		}else{
			currentList[posIndex[name]].status = true;
		}
	}
}

inline void delUser(){
	cls();
	puts("输入用户名，以逗号分隔:P");
	string name;
	cin>>name;
	vector<string> nameList = parseNames(name);
	for(int i=0;i<nameList.size();++i){
		name = nameList[i];
		if(Index[name]){
			int pos = posIndex[name];
			currentList[pos].status = false;
		}
	}
}

inline void showInfo(){
	cls();
	puts("黑名单命令列表:");
	printf("1: 添加用户 \n2. 删除用户\n3. 保存修改\n4. 打印名单\n5. 退出");
	puts("");
}

inline void save(){
	string pyout = "blackList = [";
	system("rm blackList.data");
	system("touch blackList.data");
	ofstream stubfout("blackList.data");
	for(int i = 0;i < currentList.size();++i){
		if(currentList[i].status){
			stubfout<<currentList[i].name<<endl;
			pyout += "\'" + currentList[i].name + "\'" + ",";
		}
	}
	pyout.pop_back();
	pyout += "]";
	system("rm blackList.py");
	system("touch blackList.py");
	ofstream fout("blackList.py");
	fout<<pyout;
}

inline void printList(){
	cls();
	for(int i=0;i<currentList.size();++i){
		Person cur = currentList[i];
		cout<<cur.name<<"	";
		if(cur.status){
			cout<<"已拉黑";
		}else{
			cout<<"不在名单中";
		}
		puts("");
	}
}

int main(){
	loadData();
	showInfo();
	while(cin>>op){
		switch(op[0]){
			case '1':{
				addUser();
				break;
			}
			case '2':{
				delUser();
				break;
			}
			case '3':{
				save();
				loadData();
				break;
			}
			case '4':{
				printList();
				break;
			}
			default:{
				exit(0);
			}
		}
		puts("输入任意字符继续");
		cin>>op;
		showInfo();
	}
	return 0;
}