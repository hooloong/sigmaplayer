#ifndef SIGMA_MEDIA_PLAYER_H
#define SIGMA_MEDIA_PLAYER_H

#include "ISigmaPlayer.h"
#include "SigmaMediaPlayerImpl.h"

struct SigmaMediaPlayer : public ISigmaPlayer {
    SigmaMediaPlayer();
	virtual ~SigmaMediaPlayer();
#if 0
    virtual Error_Type_e setUID(uid_t uid);
#endif

    virtual Error_Type_e setDataSource(const char *url);

    virtual Error_Type_e prepare();
    virtual Error_Type_e start();
    virtual Error_Type_e stop();
    virtual Error_Type_e pause();
	virtual Error_Type_e resume();
    virtual bool isPlaying();
    virtual Error_Type_e seekTo(uint64_t timeMS);
    virtual Error_Type_e reset();
    virtual Error_Type_e setParameter(int key, const void * request);
    virtual Error_Type_e getParameter(int key, void *reply);
	virtual Error_Type_e sendEvent(int msg, int ext1=0, int ext2=0);
	
private:
    SigmaMediaPlayerImpl *mPlayer;

	Mutex               mNotifyLock;
	
    SigmaMediaPlayer(const SigmaMediaPlayer &); 
    SigmaMediaPlayer &operator=(const SigmaMediaPlayer &);

};

#endif

