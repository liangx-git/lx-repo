#include"gomoku.h"

/**********Checkerboard********/
void Checkerboard::SetCurrentPlayerID(unsigned id)
{
    current_player_id = id;
}

void Checkerboard::PrintCBoard()
{
    //TODO 输出棋盘
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {

        }
    }

void Checkerboard::UpdateCBoard(Position pos)
{
    if (PosIsAvilable(pos))
    {
        //TODO更新棋盘
    }
}

bool Checkerboard::PosOutOfRange(Position pos)
{
    return !(pos.first >=0 && pos.first < width          //水平方向未越界
            && pos.second >=0 && pos.second < height);    //竖直方向未越界
}
\

bool Checkerboard::PosIsAvilable(Position pos)
{
    return (!PosOutOfRange(pos)
            && status[pos.second][pos.first] == 0);     //该位置上没有棋子
}


//静态变量初始化
const Direction Checkerboard::directions{{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};


/**********Player********/

Position Player::GetNextPos(ChoosePosFunc cpf)
{
    return cpf();
}

void Player::PutAPiece(Position &pos)
{
    //TODO
}


/**********HumanPlayer********/


Position HumanPlayer::GetPosFromKeyBoard()
{

}


/**********ComputerPlayer********/



/**********Judge********/



bool Judge::IsWin(Position piece_pos)
{
    //存储四个大方向上连续棋子的个数,用于遍历四个方向后判断是否有五子相连
    vector<int> pieces_of_all_direction(4, 0);

    //顺时针遍历八个方向上遍历记录连续棋子数
    for (int d = 0; d < 8; ++d)
    {
        pieces_of_all_direction[i % 4] += CalculatePiecesInCurrentDirection(piece_pos, d);
    }

    //检索四个方向上是否有五子相连（不包括当前位置，四个即满足）
    for (auto nums : pieces_of_all_direction)
    {
        if (nums >= 4)
            return true;
    }
    return false;
}

int Judge::CalculatePiecesInCurrentDirection(Position piece_pos, unsigned dire)
{
    Side player_side = ptr_to_checkerboard ->cur_player_side;
    int piece_counts = 0;
    Position cur_pos = piece_pos;
    IncPos(cur_pos, dire);
    while (ptr_to_checkerboard->PosIsAvilable(cur_pos)
           && player_side == ptr_to_checkerboard -> status[cur_pos.second][cur_pos.first])
    {
        ++piece_counts;
        IncPos(cur_pos, dire);
    }
    return piece_counts;
}

void Judge::IncPos(Position &cur_pos, unsigned dire)
{
    cur_pos.first += Checkerboard::directions[dire].first;
    cur_pos.first += Checkerboard::directions[dire].second;
}

void Judge::SetPlayersMap(pair<Side, ID> & player_info)
{
    player_side[player_info.first] = player_info.second;
}


void Judge::AnnounceWinerAndFinishGame()
{
    //TODO
}

