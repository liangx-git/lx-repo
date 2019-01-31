#include <QCoreApplication>
#include "gomoku.h"

using CBG::Chessboard;
using CBG::PlayerInformation;
using CBG::Player;
using CBG::ComputerPlayer;
using CBG::AI;
using CBG::HumanPlayer;
using CBG::Judge;
using CBG::State;
using CBG::Side;
using CBG::ChessboardSize;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ChessboardSize cb_size( WIDTH,HEIGHT);
    shared_ptr<Chessboard> ptr_cb = std::make_shared<Chessboard>(cb_size);
    ptr_cb -> printChessboard();
    shared_ptr<Player> player_1 = std::make_shared<HumanPlayer>(ptr_cb,CBG::BLACK);  //玩家1
    //shared_ptr<Player> player_2 = std::make_shared<HumanPlayer>(ptr_cb, 2, Checkerboard::WHITE);  //玩家2
    shared_ptr<Player> computer_player = std::make_shared<ComputerPlayer>(ptr_cb);
    Judge judge(ptr_cb);    //裁判
    while (true)
    {
        //用户玩家1
        player_1 -> PutAPiece();
        if (judge.isWin())
            judge.announceWiner();

        //电脑玩家
        computer_player -> PutAPiece();
        if (judge.isWin())
            judge.announceWiner();

        //用户玩家2
//        player_2 -> PutAPiece();
//        if(judge.IsWin())
//            judge.AnnounceWinerAndFinishGame();
    }

    return a.exec();
}
