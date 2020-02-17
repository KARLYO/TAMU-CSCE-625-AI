// ConsoleApplication2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。


#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<string>

#include <functional>
using namespace std;

	const int d[9][4] = {
			//u,r,d,l
			{-1,1,3,-1},//0
			{-1,2,4,0},//1
			{-1,-1,5,1},//2
			{0,4,6,-1},//3
			{1,5,7,3},//4
			{2,-1,8,4},//5
			{3,7,-1,-1},//6
			{4,8,-1,6},//7
			{5,-1,-1,7}//8
		};

string index_to_string[4] = { "up","right","down","left" };

void bfs(string& start, string& end)
{
  unordered_map<string, vector<string>> parent;
  vector<string> result;
	vector<string> q;  q.push_back(start);
	parent[start] = vector<string>{"",""};

while (!q.empty())
	{
	 
		string current = q.front();
		
		
		if (current==end) {
			
			string temp=end;
			result.clear();
			while (parent.find(temp)!=parent.end())
			{
				

				result.push_back(parent[temp][1]);
			    
				temp = parent[temp][0];

			}
			reverse(result.begin(),result.end());
		for (auto a : result) { std::cout << a << " "; } std::cout << std::endl;
			return;
}

       int pos = current.find('0');
		for (int i = 0; i < 4; i++)
		{
			if (d[pos][i] == -1) continue;
		
			swap(current[pos],current[d[pos][i]]);
			if (parent.find(current) == parent.end()) {
				parent[current] = vector<string>{ q.front(),index_to_string[i] };
				q.push_back(current);
			}

			swap(current[pos], current[d[pos][i]]);

}

		q.erase(q.begin());

}

std::cout << "no valid result!" << std::endl;
return;


}
 


void dfs(string& start, string& end, unordered_map<string, vector<string>>& parent)
{

	if (start == end)
	{
		vector<string> result;
		string temp = end;
		//result.clear();
		while (parent.find(temp) != parent.end())
		{


			result.push_back(parent[temp][1]);

			temp = parent[temp][0];

		}
		reverse(result.begin(), result.end());
		for (auto a : result) { std::cout << a << " "; } std::cout << std::endl;
		return;

	}

	
	for (int i = 0; i < 4; i++)
	{
		auto pos=start.find('0');
		string tempp(start);
		swap(start[i], start[d[pos][i]]);

		if (parent.find(start) == parent.end()) 
			parent[start] = vector<string>{ tempp,index_to_string[i] };
		
		dfs(start,end,parent);
       
		swap(start[i], start[d[pos][i]]);

	}
	return;

}

class node {
public:

	string s;
	int h1;
	int h2;
	int f;
	string parent;
	string how;
	node() {}
	node(string stri): s(stri){}
	node(string stri, int H1, int H2, string par) :s(stri), h1(H1), h2(H2), parent(par) {
		f = h1 + h2;
	}
};


void Astar(string& start, string&  end) {
	

	vector<node> open;  
	vector<node> close;

	auto update_h1 = [&](node& now) {
		string n = now.s;
		int hamming = 0;
		for (int i = 0; i < n.size(); i++)
		{

			if (n[i] == end[i] && n[i] != 0) hamming++;
		}

		return 8 - hamming;
	};

	auto update_h2 = [&](node& st) {

		int mahattan = 0;
		string n = st.s;
		for (int i = 1; i <= 8; i++)
		{
			int pos_n = n.find(std::to_string(i));
			int pos_end = end.find(std::to_string(i));
			if (pos_n == pos_end)  continue;


			int x = abs(pos_n % 3 - pos_end % 3);
			int y = abs(pos_n / 3 - pos_end / 3);
			mahattan += x + y;
		}
		return mahattan;
	};


	auto in_open = [&](string& stri) {
		for (int i=0;i<open.size();i++)
		{
			if (open[i].s == stri)
				return true;

		}
		return false;
	};
	 
	auto in_close = [&](string& stri) {
		for (int i = 0; i < close.size(); i++)
	{
		if (close[i].s == stri)
			return true;

	}
	return false; 
	};

	node star(start);
	star.h1 = update_h1(star);
	star.h2 = update_h2(star);
	star.f = star.h1 + star.h2;


	open.push_back(star);

	while (!open.empty())
	{
		std::sort(open.begin(), open.end(), [](node& a, node& b) {return a.f < b.f; });
		
		node current = open.front();
		string cur = current.s;
		if (cur == end)
		{
			vector<string> res;
			res.push_back(current.how);
		
            string par = current.parent;

			while (par != start) {
				
				std::vector<node>::iterator Res = find_if(close.begin(), close.end(), [&](node& me) {return me.s == par; });
				if (Res != close.end())
				{
					res.push_back(Res->how);
					par = Res->parent;
             }
			}
			reverse(res.begin(),res.end());
			for (auto re : res) { cout << re << " "; } cout << endl; return;
		}
        int pos = cur.find('0');
		for (int i = 0; i < 4; i++)
		{

			if (d[pos][i] == -1) continue;

			swap(cur[pos], cur[d[pos][i]]);
			if (in_close(cur) || in_open(cur)) { swap(cur[pos], cur[d[pos][i]]); continue; };
			
			node next;
			next.s = cur;  
			next.h1 = update_h1(next); next.h2 = update_h2(next); next.f = next.h1 + next.h2;
			
			next.parent = current.s;       next.how = index_to_string[i];
            open.push_back(next);
			swap(cur[pos], cur[d[pos][i]]);
		
		}

		open.erase(open.begin());

		close.push_back(current);

}

	return;
}



int main()
{


	
	unordered_map<string, vector<string>> par;
	string start("013425786"); string end2("123456780");
	Astar(start,end2);
}

