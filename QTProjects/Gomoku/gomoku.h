#ifndef GOMOKU_H
#define GOMOKU_H

#define HEIGHT 20
#define WIDTH 20

#define WHITE 1;
#define BLACK 2;

#include<vector>
#include<string>
#include<utility>
#include<memory>
#include<map>
#include<tr1/functional>

using std::vector;
using std::string;
using std::pair;
using std::shared_ptr;
using std::map;



//棋盘类
typedef pair<unsigned, unsigned> Position;
typedef vector<pair<int, int>> Direction;

class Checkerboard
{
friend class Judge;
friend class HumanPlayer;
friend class ComputerPlayer;

public:
    Checkerboard()
        : width(WIDTH),
          height(HEIGHT),
          status(height, vector<int>(width, 0)) {} //初始化棋盘状态为0

    ~Checkerboard();

    void SetCurrentPlayerID(unsigned id);

    void PrintCBoard();

    void UpdateCBoard(Position pos);

    void PrintMessage(string msg);

private:
    bool PosIsAvilable(Position pos);

    bool PosOutOfRange(Position pos);

private:
    //棋盘规格
    unsigned width;
    unsigned height;

    vector<vector<int>> status; //棋盘中每个落点位置状态,0表示没棋子，1表示黑子，2表示白子

    //当前回合落子情况
    unsigned cur_player_side;
    Position cur_pos;

    static const Direction directions;   //顺时针八个方向上的增量数组
};


//玩家基类
class Player
{
public:
    Player(unsigned id, unsigned ng, unsigned nw, shared_ptr<Checkerboard>& checkerboard) :
        player_id(id),
        number_of_total_games(ng),
        number_of_win(nw),
        ptr_to_checkerboard(checkerboard){}

    ~Player(){}

    //采用策略模式，只要传入一个功能为“落子函数”即可
    typedef std::tr1::function<Position (void)> ChoosePosFunc;
    Position GetNextPos(ChoosePosFunc cpf);

    void PutAPiece(Position &pos);

protected:
    //用户基本游戏信息
    unsigned player_id;
    unsigned player_side;
    unsigned number_of_total_games;
    unsigned number_of_win;

    //指向公共的棋盘对象
    shared_ptr<Checkerboard> ptr_to_checkerboard;
};


//用户玩家
class HumanPlayer : public Player
{
public :
    HumanPlayer(unsigned id, unsigned nc, unsigned nw, shared_ptr<Checkerboard> &checkerboard) :
        Player(id, nc, nw, checkerboard){}

    //获取用户落子位置信息
    Position GetPosFromKeyBoard();

};


//电脑玩家
class ComputerPlayer : public Player
{
public :
    ComputerPlayer(shared_ptr<Checkerboard> &checkerboard) :
        Player(0, 0, 0, checkerboard){}   //电脑玩家的id号特定为0

    Position GetPosFromAI();
private:

};


//裁判
typedef unsigned ID;
typedef unsigned Side;
class Judge
{
public:
    Judge(){}
    ~Judge(){}

    void SetPlayersMap(pair<Side, ID> &player_info);

    bool IsWin(Position piece_pos);

    void AnnounceWinerAndFinishGame();

private:
    //功能实现辅助函数

    int CalculatePiecesInCurrentDirection(Position piece_pos, unsigned dire);

    void IncPos(Position &cur_pos, unsigned dire);

private:

    //映射用户ID到棋子方（棋子颜色）
    map<ID, Side> player_side;

    //指向公共的棋盘对象
    shared_ptr<Checkerboard> ptr_to_checkerboard;
};

#endif // GOMOKU_H
