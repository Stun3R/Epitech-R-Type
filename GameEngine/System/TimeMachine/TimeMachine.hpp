/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created Sadyx83,
*/

#ifndef TIMEMACHINE_CPP
#define TIMEMACHINE_CPP

#include "../System.hpp"

using FrameTime = float;


class TimeMachine {
    public:
    TimeMachine();
    ~TimeMachine();

    FrameTime   const noexcept getTime();
    void        const setOffset();
    FrameTime   const timeFromOffset();

    private:
    FrameTime   _lastFt;
    FrameTime   _offset;
};

#endif //TIMEMACHINE_CPP