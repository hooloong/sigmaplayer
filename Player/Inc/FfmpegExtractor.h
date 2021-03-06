#ifndef FFMPEG_EXTRACTOR_H_

#define FFMPEG_EXTRACTOR_H_

#include "MediaExtractor.h"
#include "MediaBuffer.h"
#include "MediaSource.h"
#include "SigmaMediaPlayerImpl.h"

#include <Vector.h>
#include <List.h>

#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <Threads.h>
#include <Condition.h>

#include "SIGM_Types.h"

#define INITIAL_STREAM_BUF_SIZE 512 * 1024
#define DEBUGFILE "./ffmpeg.es"

#ifdef __cplusplus  
extern "C"   
{  
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libavutil/avutil.h"
}
#endif

#ifdef WIN32
#pragma comment(lib,"avutil.lib")  
#pragma comment(lib,"avcodec.lib")  
#pragma comment(lib,"avformat.lib")  
#pragma comment(lib,"swscale.lib") 
#endif

class String8;

struct FfmpegSource;

struct FfmpegExtractor : public MediaExtractor {
		FfmpegExtractor(const sp<DataSource> &source);

		virtual size_t countTracks();

		virtual sp<MediaSource> getTrack(size_t index);

		virtual sp<MetaData> getTrackMetaData(size_t index, uint32_t flags);

		virtual sp<MetaData> getMetaData();

		virtual void setTrackActive(int trackIndex, bool enable);

		virtual MediaBuffer * getNextEncFrame(int trackIndex,int64_t seekTime, int seekMode);

		virtual void seekTo(int trackIndex,int64_t time_us);
		
		static bool mIsAvRegistered;

		protected:
			virtual ~FfmpegExtractor();

		private:
			Mutex mLock;
			Mutex mAListLock;
			Mutex mVListLock;
			int mVListSize;
			int mAListSize;

			friend struct FfmpegSource;
			off_t mCurrentOffset;
			struct TrackEncFrame{
					MediaBuffer * encFrame;
				};
			//In general mTrackNum & mDemuxRefTracknum will be same
			//but in case if encounter unsupported codec then next track index will differ
			struct TrackInfo {
					unsigned long mTrackNum; //with reference to stagefright
					unsigned long mDemuxRefTracknum; //with ref to ffmpef demuxer

					sp<MetaData> mMeta;
				};

			Vector<TrackInfo> mTracks;
			bool mEof; // EOF reached? 
			sp<DataSource> mDataSource;
			bool mExtractedThumbnails;

			int mCurrentVideoTrack;
			uint8_t mVideoCodecSpecificData[400];
			int mVideoCodecSpecificDataSize;
			bool mIsVideoCodecSpecificDataValid;
			int mFirstFrame;
			bool mIsVsdTobeSent;
			int64_t mVideoFirstPts;
			int64_t mVideoLastPts;

			/*Pts interpolation*/
			uint64_t mVideoTrackLatestPts;
			uint64_t mVideoTrackFrameCountSinceLastPts;

			List<TrackEncFrame *> encVideoFrameList;

			int mCurrentAudioTrack;
			uint8_t mAudioCodecSpecificData[100];
			int mAudioCodecSpecificDataSize;
			bool mIsAudioCodecSpecificDataValid;
			bool mIsAsdTobeSent;
			int64_t mAudioFirstPts;
			int64_t mAudioLastPts;

			/*Pts interpolation*/
			uint64_t mAudioTrackLatestPts;
			uint64_t mAudioTrackFrameCountSinceLastPts;

			List<TrackEncFrame *> encAudioFrameList;

			int mCurrentSubtitleTrack;
			List<TrackEncFrame *> subFrameList;
			int mCurrentDrmTrack;
			char mStreamBuf[INITIAL_STREAM_BUF_SIZE];
			int addTracks();
			void findThumbnails();
			int64_t computeTrackDuration(int track); 

			AVFormatContext *pFormatCtx;
			AVInputFormat	*pInputFileFormat; 
			AVBitStreamFilterContext * pFilter;

			FfmpegExtractor(const FfmpegExtractor &);
			FfmpegExtractor &operator=(const FfmpegExtractor &);

			//debug only
			struct avcontext{
					char mUri[400];
					AVFormatContext * context;  
			};

			static Vector<avcontext> mContexts;


};


struct FfmpegSource : public MediaSource {
		FfmpegSource(
						const sp<FfmpegExtractor> &extractor,  size_t trackindex, size_t demuxreftrackindex);

		virtual Error_Type_e start(MetaData *params);
		virtual Error_Type_e stop();

		virtual sp<MetaData> getFormat();

		virtual Error_Type_e read(
						MediaBuffer **buffer, const ReadOptions *options);

		virtual bool threadLoop();

		virtual int  requestExitAndWait();

		virtual Error_Type_e pause();

		virtual Error_Type_e resume();

		virtual Error_Type_e seekTo(uint64_t timeMS);

		private:
		enum Type {
				AVC,
				AAC,
				WMV,
				WMA,
				RV,
				RA,
				VP6,
				VP8,
				VP9,
				HEVC,
				MP1,
				MP2,
				MP3,
				AC3,
				MPEG4,
				EAC3,
				OTHER
		};

		enum Status{
			NONE              = 0,
			PAUSE_PENDING     = 1,
			PAUSED            = 2,    
			RESUME_PENDING    = 4,
			RESUMED           = 8,
			EOS               = 16,
			INVALID
		};

		sp<FfmpegExtractor> mExtractor;
		size_t mTrackIndex;
		size_t mDemuxRefTrackIndex;
		Type mType;
		bool isVideo;
		
		MediaBuffer *mBuffer;
		bool bEOS;
	
#ifdef DEBUGFILE
		FILE * mFile;
#endif
		mutable Mutex mLock;
		uint32_t  mStatus;
		Condition mCondition;
		MediaSource::ReadOptions mOptions;

		//virtual ~FfmpegSource(){};
		FfmpegSource(const FfmpegSource &);
		FfmpegSource &operator=(const FfmpegSource &);
};

bool SniffFfmpeg(
			const sp<DataSource> &source, String8 *mimeType, float *confidence);


#endif  // FFMPEG_EXTRACTOR_H_

