/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created Sadyx83,
*/

#include "TimeMachine.hpp"

TimeMachine::TimeMachine()
{
    auto    timePoint(chrono::high_resolution_clock::now());
    this->_lastFt = chrono::duration_cast<chrono::duration<float, milli>>(timePoint).count();
}

TimeMachine::~TimeMachine()
{
}

FrameTime    TimeMachine::getTime()
{
    auto    timePoint(chrono::high_resolution_clock::now());
    this->_lastFt = chrono::duration_cast<chrono::duration<float, milli>>(timePoint).count();
    return (this->_lastFt);
}

void        TimeMachine::setOffset()
{
    auto    timePoint(chrono::high_resolution_clock::now());
    this->_offset = chrono::duration_cast<chrono::duration<float, milli>>(timePoint).count();
}

FrameTime   TimeMachine::timeFromOffset()
{
    auto    timePoint(chrono::high_resolution_clock::now());
    auto    ft = chrono::duration_cast<chrono::duration<float, milli>>(timePoint).count();
    return (ft - this->_offset);
}