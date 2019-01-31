#include<iostream>
#include<vector>
#include<string>
#include<memory>
#include<set>
#include<map>
#include<fstream>
#include<sstream>

using namespace std;

class QueryResult
{
public:
	QueryResult(const string &_word, shared_ptr<set<size_t>> _lines, shared_ptr<vector<string>> _file)
		: word(_word), lines(_lines), file(_file){}

	string word;
	shared_ptr<set<size_t>> lines;
	shared_ptr<vector<string>> file;
};

class QueryText
{
public:
	QueryText(ifstream &in);
	QueryResult query(const string &word) const;

private:
	using size_type = vector<string>::size_type;
	map<string, shared_ptr<set<size_type>>> line_of_word;
	shared_ptr<vector<string>> file;
};


QueryText::QueryText(ifstream &in) : file(new vector<string>)
{
	string line_content;
	int line_no = 0;
	while (getline(in, line_content))
	{
		file -> push_back(line_content);

		istringstream iss(line_content);
		string word;
		while (iss >> word)
		{
			auto &lines = line_of_word[word];
			if (!lines)
				lines.reset(new set<size_t>);
			lines -> insert(line_no);
		}
		++line_no;
	}
}

QueryResult QueryText::query(const string &word) const
{
	static shared_ptr<set<size_t>> nodata(new set<size_t>);
	auto loc = line_of_word.find(word);
	if (loc == line_of_word.end())
		return QueryResult(word, nodata, file);
	else 
		return QueryResult(word, loc -> second, file);
}

int main()
{
	string file("./text.txt");
	ifstream fin(file);
	QueryText qText(fin);
	cout << "输入查询单词：" << endl;
	string input;
	cin >> input;
	QueryResult qr = qText.query(input);
	cout << qr.word << endl;
	for (auto val : *qr.lines)
		cout << val << " ";
	cout << endl;
	return 0;
}
