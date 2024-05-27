//****************************************************************************
// File   : sTimer.hpp
// Last Updated for Version: 0.0.1
// Date of the Last Update:  2018-02-01
//
//                          L a h c e n   M E J J A D
//                    -----------------------------------------
//                      embedded    systems   architect
//
//
// Contact information:
// lmejjad@gmail.com
//****************************************************************************

#pragma once


class STimeEvt {
    public:
        STimeEvt (void) {
        }
        virtual void tick(void) = 0;
};


#endif // STIMER_HPP_