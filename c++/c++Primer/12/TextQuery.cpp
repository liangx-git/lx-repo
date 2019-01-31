#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<map>
#include<memory>
#include<sstream>
#include<fstream>

using namespace std;

class QueryResult
{
friend ostream& print_QueryResult(ostream &out, const QueryResult &result);

public:
	QueryResult(string _key = "", shared_ptr<vector<string>> _data = nullptr, shared_ptr<set<size_t>> _line_numbers = nullptr) :
		key(_key), data(_data), line_numbers(_line_numbers) {}
	~QueryResult() = default;

private:
	string key;
	shared_ptr<vector<string>> data;
	shared_ptr<set<size_t>> line_numbers;
};

class TextQuery
{
public:
	TextQuery() = default;
	
	void create(istream &infile);

	QueryResult query(const string &key);

private:
	shared_ptr<vector<string>> data;
	map<string, shared_ptr<set<size_t>>> wm;
};

void TextQuery::create(istream &infile)
{
	string line_string;
	while (getline(infile, line_string))
	{
		data -> push_back(line_string);
		string word_string;
		istringstream line_in(line_string);
		int line_number = data -> size() - 1;
		while (line_in >> word_string)
		{
			auto &ret = wm[word_string];
			if (!ret)	//单词指向行号的智能指针为空时
			{
				ret.reset(new set<size_t>());
			}
			ret -> insert(line_number);
		}
	}
}

QueryResult TextQuery::query(const string &key)
{
	static shared_ptr<set<size_t>> nodata(new set<size_t>());
	auto result = wm.find(key);
	if (result != wm.end())
	{
		return QueryResult(key, data, wm[key]);
	}
	return QueryResult(key, data, nodata);
}

ostream& print_QueryResult(ostream &out, const QueryResult &result)
{
	out << result.key << "出现了" << result.line_numbers -> size() << "次" << endl;
	for (auto line : *result.line_numbers)
	{
		out << "第" << line << "行:";
		out << *(result.data -> begin() + line) << endl;
	}
	return out;
}

int main()
{
	TextQuery tq;
	ifstream infile("./test.txt");
	tq.create(infile);
	//auto result = tq.query("word");
	//print_QueryResult(cout,result) << endl;
	return 0;
}



