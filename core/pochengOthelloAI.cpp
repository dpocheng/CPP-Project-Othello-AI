// pochengOthelloAI.cpp
//
// ICS 46 Spring 2015
// Project #2: Black and White

#include <iostream>
#include <vector>
#include <algorithm>

#include <ics46/factory/DynamicFactory.hpp>
#include "pochengOthelloAI.hpp"


ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, pocheng::PochengOthelloAI, "pocheng OthelloAI (Required)");


int pocheng::PochengOthelloAI::evaluation(const OthelloGameState& state)
{
    int ret_pts;

    if (state.isBlackTurn())
    {
        ret_pts = state.blackScore() - state.whiteScore();
    }
    else
    {
        ret_pts = state.whiteScore() - state.blackScore();
    }

    return ret_pts;
}


int pocheng::PochengOthelloAI::functionForSearch(const OthelloGameState& state, int depth, int num)
{
    std::vector<int> sea_vec;
    for (int col = 0; col < state.board().width(); col++)
    {
        for (int row = 0; row < state.board().height(); row++)
        {
            if (state.isValidMove(col, row) == 1)
            {
                std::unique_ptr<OthelloGameState> new_sta = state.clone();
                new_sta->makeMove(col, row);
                sea_vec.push_back(search((*new_sta->clone()), depth-1));

                if (num == 1)
                {
                    if (sea_vec.back() >= *max_element(sea_vec.begin(), sea_vec.end()))
                    {
                        ret_col = col;
                        ret_row = row;
                    }
                }
                else
                {
                    if (sea_vec.back() >= *min_element(sea_vec.begin(), sea_vec.end()))
                    {
                        ret_col = col;
                        ret_row = row;
                    }
                }
            }
        }
    }
    return 0;
}


int pocheng::PochengOthelloAI::search(const OthelloGameState& state, int depth)
{
    if (depth == 0)
    {
        return evaluation(state);
    }
    else
    {
		if (state.isBlackTurn() == currentGameUser)
		{
		    functionForSearch(state, depth, 1);
		}
		else
		{
		    functionForSearch(state, depth, 0);
		}

        return 0;
    }
}


std::pair<int, int> pocheng::PochengOthelloAI::chooseMove(const OthelloGameState& state)
{
    currentGameUser = state.isBlackTurn();
    search((*state.clone()), 2);
    return std::pair<int, int> (ret_col, ret_row);
}
