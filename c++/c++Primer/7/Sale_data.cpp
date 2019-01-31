#include<iostream>
#include<string>

using namespace std;

class Sale_data
{
friend Sale_data add(const Sale_data &lhe, const Sale_data &rhe);
friend istream &read(istream &in, Sale_data &item);
friend ostream &print(ostream &out, const Sale_data &item);

public:
	Sale_data() = default;
	
	Sale_data(const string &_ISBN) : ISBN(_ISBN), units_sold(0), revenue(0){};
	
	Sale_data(const string &_ISBN, unsigned _units_sold, double _revenue) : 
		ISBN(_ISBN), units_sold(_units_sold), revenue(_revenue){};
	
	Sale_data(istream &in);

	Sale_data &combin(const Sale_data &rhe);

	string isbn() const 
	{
		return ISBN;
	}

private:
	string ISBN;
	unsigned units_sold;
	double revenue;
};

Sale_data &Sale_data::combin(const Sale_data &rhe)
{
	ISBN += rhe.ISBN;
	units_sold += rhe.units_sold;
	revenue += rhe.revenue;

	return *this;
}

//辅助函数
Sale_data add(const Sale_data &lhe, const Sale_data &rhe)
{
	Sale_data temp(lhe);
	temp.combin(rhe);

	return temp;
}

istream &read(istream &in, Sale_data &item)
{
	in >> item.ISBN >> item.units_sold >> item.revenue;
	return in;
}

ostream &print(ostream &out, const Sale_data &item)
{
	out << item.ISBN << " " << item.units_sold << " " << item.revenue << " ";
	return out;
}


int main()
{

	return 0;
}
