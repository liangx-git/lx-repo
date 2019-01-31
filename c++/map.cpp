#include<iostream>
#include<vector>
#include<utility>
#include<queue>
#include<set>
#include<memory>
#include<string>

using namespace std;

typedef pair<int, int> Point;
struct PathNode
{
	PathNode *preNode;
	Point point;
	PathNode(PathNode *p = nullptr, Point pos = Point(0, 0)) : preNode(p), point(pos){};
};

bool point_is_availble(const vector<vector<int>> &map, const vector<vector<int>> &map_state, const Point &point)
{
	int rows = map_state.size();
	int cols = map_state[0].size();
	if ((point.first < 0 || point.first >= rows) 
		|| (point.second < 0 || point.second >= cols)
		|| map_state[point.first][point.second] == 1)
		return false;

	if(map[point.first][point.second] == 1)
		return false;
	
	return true;
}

bool reach_destination(Point end, Point curr)
{
	return end == curr;
}

PathNode* find_shortest_path(const vector<vector<int>> &map, Point begin, Point end)
{
	int rows = map.size();
	int cols = map[0].size();
	vector<vector<int>> map_state(rows, vector<int>(cols, 0));
	set<Point> direction{Point(-1, 0), Point(0, 1), Point(1, 0), Point(0, -1)};
	map_state[0][0] = 1;
	queue<PathNode *> record;
	record.push(new PathNode(nullptr, begin));
	PathNode *pre_PathNode = nullptr;
	while(!record.empty())
	{
		pre_PathNode = record.front();
		Point current_point = pre_PathNode -> point;
		record.pop();
		for (auto dire : direction)
		{
			Point next_point(current_point.first + dire.first, current_point.second + dire.second);
			if (!point_is_availble(map, map_state, next_point))
				continue;

			map_state[next_point.first][next_point.second] = 1;
			PathNode *next_PathNode = new PathNode(pre_PathNode, next_point);
			record.push(next_PathNode);

			if (reach_destination(end, next_point))
				return next_PathNode;
		}
	}
	return nullptr;
}

void print_path(vector<vector<int>> & map, PathNode *begin)
{
	PathNode *p = begin;
	while (p != nullptr)
	{
		map[(p -> point).first][(p -> point).second] = 2;
		p = p -> preNode;
	}

	int rows = map.size();
	int cols = map[0].size();
	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < cols; ++c)
			cout << map[r][c] << " ";
		cout << endl;
	}
	cout << endl;
}

int main()
{
	vector<vector<int>> map = {{1, 1, 0, 0, 1, 1, 1, 0, 0, 0},
				   {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
				   {1, 0, 0, 0, 1, 1, 1, 0, 0, 0},
				   {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
				   {1, 0, 0, 0, 1, 1, 1, 0, 0, 0},
				   {1, 1, 0, 0, 1, 1, 1, 0, 0, 0},
				   {1, 1, 0, 0, 1, 1, 1, 0, 0, 0},
				   {1, 1, 0, 0, 1, 1, 1, 0, 0, 0},
				   {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
				   {1, 1, 0, 0, 1, 1, 1, 0, 0, 0}};
	PathNode *path = find_shortest_path(map, Point(0, 2), Point(9, 9));
	print_path(map, path);

	return 0;
}
