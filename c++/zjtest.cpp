#include<iostream>
#include<vector>
#include<map>
#include<utility>

using namespace std;

struct Info
{
    int m_num;
    int m_money;
    int m_index;
    Info (int num = 0, int money = 0, int index = 0) : m_num(num), m_money(money), m_index(index){};
    
};

int MaxValue(int num, int money, vector<pair<int, int>> &weapeons, int index)
{
    if (num == 0)    //装备上限满了
        return 0;
    else if (money < weapeons[index].first)    //不够钱买装备了
        return 0;
    //else if (records.find(Info(num, money, index)) != records.end())
    //    return records[Info(num, money, index)];
    else if (money >= weapeons[index].first && num == 1)
        return weapeons[index].second;
    else
    {
        int max = 0;
        for (int i = 0; i < weapeons.size(); ++i)
        {
                int val = MaxValue(num - 1, money - weapeons[i].first, weapeons, i) + weapeons[i].second;
                if (val > max)
                    max = val;
        }
        //Info info(num, money, index);
        //records[info] = max;
        
        return max;
        
    }
    
}

int main()
{
    int n;
    int m;
    cin >> n >> m;
    vector<pair<int, int>> weapeons;
    int x, y;
    while (cin >> x >> y)
    {
        weapeons.push_back(make_pair(x, y));
    }
    int max = 0;
    for (int i = 0; i < weapeons.size(); ++i)
    {
        int val = MaxValue(m, n, weapeons, i);
        if (val > max)
            max = val;
    }
    cout << max;
    
    return 0;
}
