#include<iostream>
#include<fstream>
#include<regex>
#include<vector>
#include<string>
#include<map>
#include<iomanip>
#include<algorithm>
#include<sstream>

using namespace std;


//倒排索引位置信息结点
struct Node
{
	unsigned int windex;
	Node *next;
	Node(unsigned int wi = 0, Node *nt = nullptr) :  windex(wi), next(nt){};
};

//关键字的碰撞目录信息结点
struct Head
{
	unsigned int findex;
	unsigned int rate;	//关键字在统一文本中出现的频率
	Node* head;	//指向索引信息量表头结点指针
	Head(unsigned f = 0, unsigned int r = 0, Node* h = nullptr) : findex(f), rate(r), head(h){};
};


class InvertTool
{
public:
	InvertTool(){};

	~InvertTool(){};

	//通过files批量创建倒排索引
	bool Init(vector<string> files);

	//添加file的倒排索引
	bool Add(string file);

	//查找是否存在关键字对应的倒排索引
	bool Find(string key);

	//将关键字对应的内容输出到屏幕
	void Print(string key);

	//输出对应文章的倒排索引到磁盘文件中
	bool Write(string file = "out.txt");

private:

	//判断字符串是否是合法关键字
	bool IsWord(string word);

	//一次执行一个关键字的插入
	bool _Add(string word, unsigned int findex, unsigned int windex);

	//查找关键字在碰撞目录中的序号
	int SearchFindex(const vector<Head> &v, unsigned int findex);
private:
	map<unsigned int, string> m_contents;	//文章目录
	map<string, vector<Head> *> m_indexs;	//倒排索引

	static regex reg;	//用于IsWord函数中使用

};

regex InvertTool::reg = regex("[a-zA-Z][a-zA-Z0-9]+");

bool InvertTool::Init(vector<string> files)
{
	for (auto file : files)
	{
		if (!Add(file))
			return false;
	}
	return true;
}

bool InvertTool::Add(string file)
{
	//打开源文件
	ifstream in(file);
	if (!in.is_open())
		return false;

	//fi表示当前文本序号，wi表示关键字在文本中序号
	unsigned int fi = m_contents.size();	
	unsigned int wi = 0;
	m_contents[fi] = file;	//将新增文章名称字符串保存到m_contents中 

	string line;
	while (getline(in, line))	//以行为单位从磁盘中读入字符串
	{	
		istringstream strm(line);	//使用字符串流处理字符
		string word;
		while (strm >> word)
		{
			++wi;
			if (!IsWord(word))	//对于不合法的字符串不做处理
				break;	
				
			if (!_Add(word, fi, wi))	//调用_Add将关键字放到倒排索引中
				return false;
		}
	}
	in.close();

	return true;
}

bool InvertTool::_Add(string word, unsigned int findex, unsigned int windex)
{
	Node *pNew = new Node(windex);
	if (pNew == nullptr)
		return false;
	if (Find(word))	//关键字在map中存在，发生碰撞
	{
		auto pVec = m_indexs[word];
		int i = SearchFindex(*pVec, findex);
		if (i != -1)	//当前文本序号存在于当前关键字的碰撞目录中
		{
			(*pVec)[i].rate += 1;	//该关键字在该文本中出现频数加1

			//将新结点添加到索引链表末尾
			Node* p = (*pVec)[i].head;
			while (p -> next != nullptr)
				p = p -> next;
			p -> next = pNew;
		}
		else	//当前文本序号不存在于当前关键字的碰撞目录中,新增目录项
		{
			(*pVec).push_back(Head(findex, 1, pNew));
		}
	}
	else
	{
		m_indexs[word] = new vector<Head>();	//在索引表中新增关键字项
		if(m_indexs[word] == nullptr)
			return false;
		auto pVec = m_indexs[word];
		(*pVec).push_back(Head(findex, 1, pNew));
	}
	return true;
}

int InvertTool::SearchFindex(const vector<Head> &v, unsigned int findex)
{
	int len = v.size();
	for (int i = 0; i < len; ++i)
	{
		if (v[i].findex == findex)
			return i;
	}

	return -1;
}

bool InvertTool::Find(string key)
{
	if (m_indexs.find(key) != m_indexs.end())
		return true;
	return false;
}

void InvertTool::Print(string key)
{
	cout << setiosflags(ios::left);
	auto pVec = m_indexs[key];
	if (pVec == nullptr)
	{
		cout << ">>关键字(" << key << ")不存在索引中" << endl;
		return;
	}
	cout << setw(15) << ">>文章序号" << setw(10) << "频数" << setw(10) << "位置" << endl;
	for (auto val : *pVec)
	{
		cout << ">>" << setw(10) << val.findex << setw(8) << val.rate;
		Node* p = val.head;
		while (p != nullptr)
		{
			cout << p -> windex;
			p = p -> next;
			if (p != nullptr)
				cout << ", ";
		}
		cout << endl;
	}
}
	
bool InvertTool::Write(string file)
{
	if (m_contents.empty())	//字典内容为空
		return false;

	ofstream out(file, ofstream::out);
	if (!out.is_open())
		return false;
	
	//先将m_contents内容输出
	out << setiosflags(ios::left) << endl; //全局左对齐 
	out << "**************************文件目录**********************************：" << endl;
	out << setw(12) << "序号" << "文章名" << endl;
	for (auto val : m_contents)
		out << setw(10) << val.first << val.second << endl;
	out << endl;

	//输出倒排索引
	out << "**************************倒排索引**********************************：" << endl;
	out << setw(20) << "关键字" << setw(15) << "文章号" << setw(13) << "频数" << setw(20) << "位置" <<endl;
	for (auto val : m_indexs)
	{
		out << setw(20) << val.first;
		auto pH = val.second;
		int i = 0;
		for (auto val : *pH)
		{
			if (i++ != 0)
				out << setw(20) << ' ';
			out << setw(10) << val.findex << setw(10) << val.rate << " ";
			Node* p = val.head;
			while (p != nullptr)
			{	
				out << p -> windex;
				p = p -> next;
				if (p != nullptr)
					out << ", ";
			}
			out << endl;
		}
	}
	out.close();

	return true;
}

bool InvertTool::IsWord(string word)
{
	if (regex_match(word.c_str(), reg))
		return true;
		
	return false;

}

int main(int argc, char* argv[])
{

	InvertTool itool;
	if (argc > 1)	//从命令参数中获取文件名
	{
		vector<string> files;
		for (int i = 1; i < argc; ++i)
			files.push_back(argv[i]);
		if (itool.Init(files) && itool.Write())
			cout << ">>已创建倒排索引" << endl;
		else
			cout << ">>创建倒排索引失败！" << endl;
	}
	else
	{
		cout << ">>请输入文件名(Ctrl+d结束输入)：" << endl;
		string file;
		while (cin >> file)
		{
			itool.Add(file);
		}
		if (itool.Write())
			cout << ">>已创建倒排索引" << endl;
		else
			cout << ">>创建倒排索引失败！" << endl;

		cin.clear();
	}

	while (true)
	{
		cout << endl;
		cout << "**********************" << endl;
		cout << "1.添加新文本" << endl;
		cout << "2.查找关键字" << endl;
		cout << "3.其它任意键退出程序" << endl;
		cout << "**********************" << endl;
		cout << endl;
		int select;
		cin >> select;
		switch(select)
		{
			case 1:
			{
				cout << ">>输入文本路径：" << endl;
				string path = " ";
				cin >> path;
				if (itool.Add(path) && itool.Write())
					cout << ">>添加成功并创建倒排索引!" << endl;
				else
					cout << ">>文件(" << path << ")打开 失败！" << endl;
				break;
			}
			case 2:
			{
				cout << ">>请输入要关键字" << endl;
				string word = " ";
				Node* p = nullptr;
				cin >> word;
				if (itool.Find(word))
					itool.Print(word);
				else
					cout << ">>不存在!" << endl;
				break;
			}
			default:
				exit(0);
		}	
	}


	return 0;
}
