#include "gomoku.h"
#include<algorithm>

#define INFINITY 50000

using CBG::Chessboard;
using CBG::PlayerInformation;
using CBG::Player;
using CBG::ComputerPlayer;
using CBG::AI;
using CBG::HumanPlayer;
using CBG::Judge;
using CBG::State;
using CBG::Side;

/******************************Chessboard****************************/

void Chessboard::printChessboard()
{
    cout << endl;
    for (int y = 0; y < chessboard_size_.height; ++y)
    {
        for (int x = 0; x < chessboard_size_.width; ++x)
        {
            if (chessboard_states_[y][x] == NONE)
                cout << '*';
            else if(chessboard_states_[y][x] == BLACK)
                cout << '1';
            else if (chessboard_states_[y][x] == WHITE)
                cout << '2';
            cout << ' ';

        }
        if (y == 0)
            cout << 'x';
        cout << endl;
    }
    cout << 'y' << endl;
    //TODO 通过qt输出棋盘
}

void Chessboard::updateChessboard(const Position &pos, Side gameSide)
{
    if (posIsAvilable(pos))
    {
        //TODO更新棋盘
        PositionInformation_of_just_drop_ = PositionInformation(gameSide, pos);
        chessboard_states_[pos.second][pos.first] = gameSide;
        printChessboard();
    }
}

CBG::PositionInformation Chessboard::getPositionInformationOfJustDrop()
{
    return PositionInformation_of_just_drop_;
}

bool Chessboard::posOutOfRange(const Position &pos)
{
    return !(pos.first >=0 && pos.first < chessboard_size_.width          //水平方向未越界
             && pos.second >=0 && pos.second < chessboard_size_.height);    //竖直方向未越界
}

bool Chessboard::posIsAvilable(const Position &pos)
{
    return (!posOutOfRange(pos)
            && chessboard_states_[pos.second][pos.first] == NONE);     //该位置上没有棋子
}

std::map<unsigned, int> Chessboard::score_sheet_ = {
    {HUO | LEN_1, 5},
    {HUO | LEN_2, 50},
    {CHONG | LEN_3, 50},
    {HUO | LEN_3, 100},
    {CHONG | LEN_4, 100},
    {JIN_3_3, 1000},
    {HUO | LEN_4, 1500},
    {JIN_3_4, 1500},
    {JIN_4_4, 1500},
    {HUO | LEN_5, 50000},
    {SI | LEN_5, 50000},
    {CHONG | LEN_5, 50000},
    {LEN_5S, 50000},
    {WIN, 50000}};



/******************************Player****************************/

PlayerInformation Player::default_player_ = PlayerInformation(0, 0, 0);

void Player::PutAPiece()
{
    //采用策略模式(NVI，通过非虚接口调用protect虚函数)
    Position next_pos = GetNextPos();
    ptr_to_Chessboard_ -> updateChessboard(next_pos, game_side_);
}



/**********HumanPlayer********/

Position HumanPlayer::GetNextPos()
{
    return GetNextPosFromIO();
}

Position HumanPlayer::GetNextPosFromIO()
{
    cout << player_information_.player_id <<"! 请输入坐标：" << endl;
    int x, y;
    cin >> x >> y;
    return Position(x, y);
}



/******************************ComputerPlayer****************************/

Position ComputerPlayer::GetNextPos()
{
    //默认使用简单AI
    //return ai_.getPositionBySimpleWay();
    return ai_.GetPosByAI();
//    return GetPosByHardWay();
//    if (game_difficulty == NORMAL)
//        return GetPosBySimpleWay();
//    else
//        return GetPosByHardWay();
}

void ComputerPlayer::SetDifficulty(Difficulty diff)
{
    game_difficulty = diff;
}



/******************************AlphaBeta****************************/

Position AI::GetPosByAI()
{
    deque<Position> range_for_drop_piece = calculateRangeForNextDropPiece((ptr_to_Chessboard_ -> PositionInformation_of_just_drop_).pos, ptr_to_Chessboard_ -> chessboard_states_);
    int best_score = 0;
    Position best_pos;
    for (auto pos : range_for_drop_piece)
    {
        //vector<vector<Side>> temp_status (ptr_to_Chessboard_ -> chessboard_states_);
        //temp_status[pos.second][pos.first] = game_side_;
        int new_score = AlphaBeta(pos, 3, -INFINITY, INFINITY, computer_side_, ptr_to_Chessboard_ -> chessboard_states_);
        if (new_score > best_score)
        {
            best_score = new_score;
            best_pos = pos;
        }
    }
    return best_pos;
}

int AI::AlphaBeta(Position pos, int depth, int alp, int beta, Side side, vector<vector<Side>> chessboard_states)
{
    if (depth == 0 || !hasNextChildPos(chessboard_states))
        return evaluateScore(pos, chessboard_states);

    chessboard_states[pos.second][pos.first] = side;
    if (side == computer_side_)   //极大值方
    {
        deque<Position> range_of_MaxSide_drop = calculateRangeForNextDropPiece(pos, chessboard_states);
        for (auto child_pos : range_of_MaxSide_drop)
        {
            alp = std::max(alp, AlphaBeta(child_pos, depth - 1, alp, beta, reverseSide(side), chessboard_states));
            if (beta <= alp)    //剪枝
                break;
        }
        return alp;
    }
    else
    {
        deque<Position> range_of_MinSide_drop = calculateRangeForNextDropPiece(pos, chessboard_states);
        for (auto child_pos : range_of_MinSide_drop)
        {
            beta = std::min(beta, AlphaBeta(child_pos, depth - 1, alp, beta, reverseSide(side), chessboard_states));
            if (beta <= alp)    //剪枝
                break;
        }
        return beta;
    }
}

//为了减少时间复杂度，只考虑对方落棋点为中心7*7范围落点
deque<Position> AI::calculateRangeForNextDropPiece(Position pos, const vector<vector<Side>> &chessboard_states)
{
    int beg_x = (pos.first - 3) >= 0 ? (pos.first - 3) : 0;
    int end_x = (pos.first + 3) < (ptr_to_Chessboard_ -> chessboard_size_.width) ? (pos.first + 3) : (ptr_to_Chessboard_ -> chessboard_size_.width);
    int beg_y = (pos.second - 3) >= 0 ? (pos.second - 3) : 0;
    int end_y = (pos.second + 3) < (ptr_to_Chessboard_ -> chessboard_size_.height) ? (pos.second + 3) : (ptr_to_Chessboard_ -> chessboard_size_.height);
    deque<Position> pos_to_drop;
    for (int y = beg_y; y <= end_y; ++y)
    {
        for (int x = beg_x; x <= end_x; ++x)
        {
            if (chessboard_states[y][x] == NONE)
                pos_to_drop.push_back(std::make_pair(x, y));
        }
    }
    return pos_to_drop;
}

/*
int AI::AlphaBeta(Position pos, int depth, int alp, int beta, Side side, vector<vector<Side>> chessboard_states)
{
    if (depth == 0 || !hasNextChildPos(chessboard_states))
        return evaluateScore(pos);

    if (side == game_side_)   //极大值方
    {
        for (int y = 0; y < ptr_to_Chessboard_ -> chessboard_size_.height; ++y)
        {
            for (int x = 0; x < ptr_to_Chessboard_ -> chessboard_size_.width; ++x)
            {
                if (chessboard_states[y][x] != NONE)
                    continue;
                Position child_pos(x, y);
                alp = std::max(alp, AlphaBeta(child_pos, depth - 1, alp, beta, reverseSide(side), updateChessboardStates(copy_chessboard_states_, child_pos, side)));
                if (beta <= alp)    //剪枝
                    break;
            }
        }
        return alp;
    }
    else
    {
        for (int y = 0; y < ptr_to_Chessboard_ -> chessboard_size_.height; ++y)
        {
            for (int x = 0; x < ptr_to_Chessboard_ -> chessboard_size_.width; ++x)
            {
                if (chessboard_states[y][x] != NONE)
                    continue;
                Position child_pos(x, y);
                beta = std::min(beta, AlphaBeta(child_pos, depth - 1, alp, beta, reverseSide(side), updateChessboardStates(copy_chessboard_states_, child_pos, side)));
                if (beta <= alp)    //剪枝
                    break;
            }
        }
        return beta;
    }
}
*/

bool AI::hasNextChildPos(const vector<vector<CBG::Side> > &chessboard_states)
{
    int width = ptr_to_Chessboard_ -> chessboard_size_.width;
    int height = ptr_to_Chessboard_ -> chessboard_size_.height;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (chessboard_states[y][x] == NONE)
                return true;
        }
    }
    return false;
}

//vector<vector<CBG::Side> > AI::updateChessboardStates(const vector<vector<CBG::Side> > &chessboard_states, Position pos, CBG::Side side)
//{
//    vector<vector<Side> > temp_status(chessboard_states);
//    temp_status[pos.second][pos.first] = side;
//    return temp_status;
//}

//void AI::updateCopyChessboardStates()
//{
//    copy_chessboard_states_.assign(ptr_to_Chessboard_ -> chessboard_states_.begin(), ptr_to_Chessboard_ -> chessboard_states_.end());
//}

int AI::evaluateScore(const Position &pos, const vector<vector<Side>> &chessboard_states)
{
    int computer_player_score = evaluateScoreOfOneSide(pos, computer_side_, chessboard_states);
    int human_player_score = evaluateScoreOfOneSide(pos, reverseSide(computer_side_), chessboard_states);
    return computer_player_score > human_player_score ? computer_player_score : human_player_score;
}

int AI::evaluateScoreOfOneSide(const Position &pos, Side side, const vector<vector<Side>> &chessboard_states)
{
    int score = 0;
    map<State, int> all_direction_states;
    getAllDirectionStates(pos, side, all_direction_states, chessboard_states);
    for (auto &state : all_direction_states)    //第一次循环找到存在的长连、3_3禁手和4_4禁手
    {
        if ((state.first & 0x00ff) >= LEN_5S)   //查找长连
        {
            score += Chessboard::score_sheet_[LEN_5S];
            state.second = 0;
        }
        else if (state.first & (HUO | LEN_3) //查找3_3禁手
                && state.second == 2)
        {
            score += Chessboard::score_sheet_[JIN_3_3];
            state.second = 0;
        }
        else if (state.first & (HUO | LEN_4)     //查找4_4禁手
                 && state.second == 2)
        {
            score += Chessboard::score_sheet_[JIN_4_4];
            state.second = 0;
        }
    }

    //计算剩余得分情况
    for (auto state : all_direction_states)
    {
        if (state.second != 0
                && (ptr_to_Chessboard_ -> score_sheet_).find(state.first) != (ptr_to_Chessboard_ -> score_sheet_).end())    //在score_sheet中能找到该state评分
            score += ptr_to_Chessboard_ ->score_sheet_[state.first];
    }
    return score;
}

void AI::getAllDirectionStates(const Position &pos, Side side, map<State, int> &all_direction_States, const vector<vector<Side>> &chessboard_states)
{
    //顺时针遍历pos位置的八个小方向上遍历记录连续棋子数，以及末尾位置情况
    vector<pair<int, bool>> temp;
    for (int d = 0; d < 8; ++d)
    {
        int len = calculatePiecesInCurrDirection(pos, side, d, chessboard_states);
        bool end_is_empty = false;
        if (endPositionIsEmpty(pos, d, len, chessboard_states))
            end_is_empty = true;
        temp.push_back(std::make_pair(len, end_is_empty));
    }

    //根据temp信息计算在pos点的四个大方向上的State信息
    for(int d = 0; d < 4; ++d)
    {
        unsigned short state = 0;
        //两端情况
        if (temp[d].second == true
                && temp[d + 4].second == true)
            state |= HUO;     //活
        else if (temp[d].second == false
                 && temp[d + 4].second == false)
            state |= SI;      //死
        else
            state |= CHONG;   //冲

        //计算大方向上的长度
        state |= 1 << (temp[d].first + temp[d +4].first + 1 - 1);
        ++all_direction_States[State(state)];
    }
}

int AI::calculatePiecesInCurrDirection(const Position &pos, Side s, int dire, const vector<vector<Side>> &chessboard_states)
{
    int piece_counts = 0;
    Position cur_pos = pos;
    for (movePosition(cur_pos, dire);
         !(ptr_to_Chessboard_ -> posOutOfRange(cur_pos))     //确保坐标点在棋盘中
           && (s == chessboard_states[cur_pos.second][cur_pos.first]
               || CHECK == chessboard_states[cur_pos.second][cur_pos.first]);
         movePosition(cur_pos, dire))
    {
        ++piece_counts;
    }
    return piece_counts;
}

Side AI::reverseSide(Side s)
{
    return s ==WHITE ? BLACK : WHITE;
}

bool AI::endPositionIsEmpty(const Position &pos, int dire, int len, const vector<vector<Side>> &chessboard_states)
{
    Position end_pos = pos;
    for (int i = 0; i <= len; ++i)
        movePosition(end_pos, dire);
    if (ptr_to_Chessboard_ -> posOutOfRange(end_pos)
            || chessboard_states[end_pos.second][end_pos.first] != NONE)
        return false;
    return true;
}

void AI::movePosition(Position &pos, int dire)
{
    pos.first += directions[dire].first;
    pos.second += directions[dire].second;
}



/******************************Judge****************************/


bool Judge::isWin()
{
    Position cur_pos = ptr_to_Chessboard_ ->PositionInformation_of_just_drop_.pos;
    //存储四个大方向上连续棋子的个数,用于遍历四个方向后判断是否有五子相连
    vector<int> pieces_of_all_direction(4, 0);

    //顺时针遍历八个方向上遍历记录连续棋子数
    for (int d = 0; d < 8; ++d)
    {
        pieces_of_all_direction[d % 4] += calculatePiecesInCurrDirection(cur_pos, d);
    }

    //检索四个方向上是否有五子相连（不包括当前位置，四个即满足）
    for (auto nums : pieces_of_all_direction)
    {
        if (nums >= 4)
            return true;
    }
    return false;
}

int Judge::calculatePiecesInCurrDirection(const Position &pos, int dire)
{
    Side player_side = ptr_to_Chessboard_ ->PositionInformation_of_just_drop_.side;
    int piece_counts = 0;
    Position cur_pos = pos;
    movePosition(cur_pos, dire);
    while (!ptr_to_Chessboard_ -> posOutOfRange(cur_pos)     //确保坐标点在棋盘中
           && player_side == ptr_to_Chessboard_ -> chessboard_states_[cur_pos.second][cur_pos.first])
    {
        ++piece_counts;
        movePosition(cur_pos, dire);
    }
    return piece_counts;
}

void Judge::movePosition(Position &pos, int dire)
{
    pos.first += directions[dire].first;
    pos.second += directions[dire].second;
}

//void Judge::registerPlayersSide(pair<Side, ID> & playersSide)
//{
//    player_side[player_info.first] = player_info.second;
//}

void Judge::announceWiner()
{
    //TODO
    //cout << "player" << ptr_to_Chessboard_ -> cur_side << "is winer!" << endl;
}

void Judge::finishGame()
{
    //TODO
    exit(0);
}





