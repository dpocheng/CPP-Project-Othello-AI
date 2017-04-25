// pochengOthelloAI.hpp
//
// ICS 46 SPRING 2015
// Project #2: Black and White

#ifndef POCHENGOTHELLOAI_HPP
#define POCHENGOTHELLOAI_HPP

#include "OthelloAI.hpp"


namespace pocheng
{
    class PochengOthelloAI : public OthelloAI
    {
    public:
        int evaluation(const OthelloGameState& state);
        int functionForSearch(const OthelloGameState& state, int depth, int num);
        int search(const OthelloGameState& state, int depth);
        virtual std::pair<int, int> chooseMove(const OthelloGameState& state);

    private:
        bool currentGameUser;
        int ret_col, ret_row;
    };
}

#endif // POCHENGOTHELLOAI_HPP
