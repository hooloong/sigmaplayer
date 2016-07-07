#ifndef SIGMA_IPLAYER_H
#define SIGMA_IPLAYER_H

#include <RefBase.h>
#include <KeyedVector.h>

#include "SIGM_Types.h"

class ISigmaPlayer: public VirtualLightRefBase {
public:
    ISigmaPlayer(){};                                                     \
    virtual ~ISigmaPlayer(){}; 

    virtual Error_Type_e        setDataSource(const char *url) = 0;

    virtual Error_Type_e        prepare() = 0;
    virtual Error_Type_e        start() = 0;
    virtual Error_Type_e        stop() = 0;
    virtual Error_Type_e        pause() = 0;
    virtual bool        isPlaying() = 0;
    virtual Error_Type_e        seekTo(int msec) = 0;

	virtual Error_Type_e        reset() = 0;

    virtual Error_Type_e        setParameter(int key, const void * request) = 0;
    virtual Error_Type_e        getParameter(int key, void * reply) = 0;

};

#endif
