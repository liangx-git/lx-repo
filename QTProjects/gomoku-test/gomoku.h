#ifndef GOMOKU_H
#define GOMOKU_H

#define HEIGHT 15
#define WIDTH  15

#include "gomoku.h"

#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include<memory>
#include<map>
#include<tr1/functional>
#include<deque>


using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::pair;
using std::shared_ptr;
using std::map;
using std::deque;


typedef pair<int, int> Position;    //坐标(x, y)
typedef vector<pair<int, int>> Direction;


namespace CBG   //ChessboardGame作用域
{

//五子棋中的黑方和白方
enum Side
{
    NONE  = 0,
    BLACK = 1,
    WHITE = 2,

    //剪枝算法中使用
    PREPARE = 4,
    CHECK = 8
};


//使用16位位向量表示棋局情况，通常组合两端情况和长度可以得到棋局情况,特殊情况需要组合
enum State
{
    //前八位,表示连子两端情况
    HUO     = 0x0000,
    SI      = 0x0100,
    CHONG   = 0x0200,
    //后八位
    LEN_1   = 0X0001,
    LEN_2   = 0X0002,
    LEN_3   = 0X0004,
    LEN_4   = 0X0008,
    LEN_5   = 0X0010,
    LEN_5S  = 0X0020,
    //特殊情况
    JIN_3_3 = 0X0400,
    JIN_3_4 = 0X0800,
    JIN_4_4 = 0X1000,
    WIN     = 0x8000,
};


static const Direction directions{{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};   //顺时针八个方向上的增量数组


struct PositionInformation
{
    Side side;
    Position pos;

    PositionInformation(Side s, Position p):
        side(s),
        pos(p){}

};


struct ChessboardSize
{
    int width;
    int height;
    ChessboardSize(int w, int h):
        width(w),
        height(h){}
};


//棋盘类
class Chessboard
{
friend class AI;
friend class Judge;

public:
    Chessboard(ChessboardSize chessboardSize):
        chessboard_size_(chessboardSize),
        chessboard_states_(chessboard_size_.height, vector<Side>(chessboard_size_.width, NONE)),
        PositionInformation_of_just_drop_(PositionInformation(NONE, Position(0, 0))){}

    ~Chessboard(){}

    void printChessboard();
    void updateChessboard(const Position &pos, Side gameSide);
    void printNotificationMessage(const string &msg);

private:
    PositionInformation getPositionInformationOfJustDrop();
    bool posIsAvilable(const Position &pos);
    bool posOutOfRange(const Position &pos);

private:
    ChessboardSize chessboard_size_;
    vector<vector<Side>> chessboard_states_;
    PositionInformation PositionInformation_of_just_drop_;

    static map<unsigned, int> score_sheet_;
};


//数据库中保存的用户信息
struct PlayerInformation
{
    int player_id;
    int number_of_total_games;
    int number_of_win;

    PlayerInformation(int playerId, int numOfTotalGame, int numOfWin):
        player_id(playerId),
        number_of_total_games(numOfTotalGame),
        number_of_win(numOfWin){}
};


//玩家基类
class Player
{
public:
    Player(shared_ptr<Chessboard> pChessboard,
           Side s = NONE,
           PlayerInformation playerInformation = default_player_):
        ptr_to_Chessboard_(pChessboard),
        game_side_(s),
        player_information_(playerInformation){}

    virtual ~Player(){}

    void PutAPiece();

protected:
    //子类中重载该函数，实现策略模式，不同子类使用不同落子方案
    virtual Position GetNextPos() = 0;

protected:
    shared_ptr<Chessboard> ptr_to_Chessboard_;

    Side game_side_;

    PlayerInformation player_information_;

    static PlayerInformation default_player_;
};


//用户玩家
class HumanPlayer : public Player
{
public :
    //玩家默认初始化为黑方
    HumanPlayer(shared_ptr<Chessboard> &Chessboard,
                Side side = BLACK,
                PlayerInformation playerInfo = default_player_):
        Player(Chessboard,side, playerInfo){}

    virtual ~HumanPlayer(){}

protected:
    //@override
    virtual Position GetNextPos();

private:
    Position GetNextPosFromIO();

};



class AI
{
public:
    AI(Side computer_side,
              shared_ptr<Chessboard> ptr_to_Chessboard):
        computer_side_(computer_side),
        ptr_to_Chessboard_(ptr_to_Chessboard),
        copy_chessboard_states_(ptr_to_Chessboard -> chessboard_states_){}

    ~AI(){}

    Position getNextPositionToDrop();

    Position GetPosByAI();

private:
    deque<Position> calculateRangeForNextDropPiece(Position pos,  const vector<vector<Side>> &chessboard_states);

    int AlphaBeta(Position pos, int depth, int alp, int beta, Side side, vector<vector<Side>> chessboard_states);

    bool hasNextChildPos(const vector<vector<CBG::Side> > &chessboard_states);

   //vector<vector<Side>> updateChessboardStates(const vector<vector<CBG::Side> > &chessboard_states, Position pos, Side side);

    //对当前局面评分
    //void updateCopyChessboardStates();

    int evaluateScore(const Position &pos, const vector<vector<Side>> &chessboard_states);

    int evaluateScoreOfOneSide(const Position &pos, Side side, const vector<vector<Side>> &chessboard_states);

    void getAllDirectionStates(const Position &pos, Side side, map<State, int> &all_direction_States, const vector<vector<Side>> &chessboard_states);

    int calculatePiecesInCurrDirection(const Position &pos, Side s, int dire, const vector<vector<Side>> &chessboard_states);

    bool endPositionIsEmpty(const Position &pos, int dire, int len, const vector<vector<Side>> &chessboard_states);

    void movePosition(Position &pos, int dire);

    Side reverseSide(Side s);

private:
    Side computer_side_;
    shared_ptr<Chessboard> ptr_to_Chessboard_;
    vector<vector<Side>> copy_chessboard_states_;
};



enum Difficulty
{
    NORMAL = 1,
    HARD   = 2
};

//电脑玩家
class ComputerPlayer : public Player
{
public :
    //电脑玩家默认为白方
    ComputerPlayer(shared_ptr<Chessboard> ptr_Chessboard) :
        Player(ptr_Chessboard, WHITE),
        game_difficulty(NORMAL),
        ai_(WHITE, ptr_Chessboard){}

    virtual ~ComputerPlayer(){}

    void SetDifficulty(Difficulty diff);

protected:
    //override
    virtual Position GetNextPos();

private:
    /*
    //困难难度
    Position GetPosByHardWay();

    //AlphaBeta深搜剪枝
    int AlphaBeta(Position pos, int depth, int alp, int beta, Side side, vector<vector<Side>> status);

    bool HasNextChildPos(const vector<vector<Side>> &status);

    Position GetNextChildPos(Side s, const vector<vector<Side>> &status);

    void SetPosCheck(vector<vector<Side>> &status, const Position &pos);

    vector<vector<Side>> UpdateStatus(const vector<vector<Side>> &status, const Position &pos, Side side);

    //简单难度
    Position GetPosBySimpleWay();

    //对当前局面评分
    int Evaluate(const Position &pos, vector<vector<Side>> status);

    int EvaluateOneSide(const Position &pos, Side side, vector<vector<Side>> status);

    void GetAllDireStateInfo(const Position &pos, Side side, vector<vector<Side>> status, map<State, int> &state_info);

    Side ReverseSide(Side s);

    int CalcPiecesInCurrDirection(const Position &pos, Side s, int dire ,vector<vector<Side>> status);

    bool EndPosIsEmpty(const Position &pos, int dire, int len, vector<vector<Side>> status);

    void MovePos(Position &pos, int dire);
    */

private:
    Difficulty game_difficulty;
    AI ai_;
};





//裁判
typedef int ID;
class Judge
{
public:
    Judge(shared_ptr<Chessboard> ptrChessboard):
        ptr_to_Chessboard_(ptrChessboard){}

    ~Judge(){}

    //void registerPlayersSide(pair<Side, ID> &playersSide);

    bool isWin();

    void announceWiner();

    void finishGame();

private:
    //功能实现辅助函数

    int calculatePiecesInCurrDirection(const Position &pos, int dire);

    void movePosition(Position &pos, int dire);

private:
    //映射用户ID到棋子方（棋子颜色）
    //map<Side, ID> players_side_;

    shared_ptr<Chessboard> ptr_to_Chessboard_;
};


//负责从数据库中获取用户信息，以及用户信息写入数据库
class Recorder;

}   //end CBG

#endif // GOMOKU_H
