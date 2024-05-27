//****************************************************************************
// File   : applicFactory.hpp
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

class ApplicFactory {
    private:
        static ApplicFactory* instance;
    
    public:        
        static ApplicFactory* getInstance(void) {
            if (instance == nullptr) {
                instance = new ApplicFactory();
            }
            return instance;
        }
    private: 
        ApplicFactory ();
};

extern ApplicFactory* instance;