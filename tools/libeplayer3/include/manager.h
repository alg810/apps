#ifndef MANAGER_H_
#define MANAGER_H_

#include <stdio.h>
#include <stdint.h>

typedef enum {
    MANAGER_ADD,
    MANAGER_LIST,
    MANAGER_GET,
    MANAGER_GETNAME,
    MANAGER_SET,
    MANAGER_GETENCODING,
    MANAGER_DEL,
    MANAGER_GET_TRACK,
    MANAGER_INIT_UPDATE
} ManagerCmd_t;

typedef enum {
    eTypeES,
    eTypePES
} eTrackTypeEplayer;

typedef struct Track_s {
    char *                Name;
    char *                Encoding;
    int                   Id;

    /* new field for ffmpeg - add at the end so no problem
    	 * can occur with not changed srt saa container
    	 */
    char*                 language;

    /* length of track */
    long long int         duration;
    unsigned int          frame_rate;
    unsigned int          TimeScale;
    long long int         pts;

    /* for later use: */
    eTrackTypeEplayer     type;
    int                   width;
    int                   height;

    /* context from ffmpeg */
    AVFormatContext *avfc;
    /* stream from ffmpeg */
    void               *  stream;
    /* codec extra data (header or some other stuff) */
    void               *  extraData;
    int		              extraSize;

    /* If player2 or the elf do not support decoding of audio codec set this.
     * AVCodec is than used for softdecoding and stream will be injected as PCM */
    int                   inject_as_pcm;

    int			  pending;
} Track_t;

struct Context_s;
typedef struct Context_s Context_t;

typedef struct Manager_s {
    char * Name;
    int (* Command) (Context_t *, ManagerCmd_t, void *);
    char ** Capabilities;

} Manager_t;

typedef struct ManagerHandler_s {
    char * Name;
    Manager_t * audio;
    Manager_t * video;
    Manager_t * subtitle;
    Manager_t * dvbsubtitle;
    Manager_t * teletext;
} ManagerHandler_t;

void freeTrack(Track_t* track);
void copyTrack(Track_t* to, Track_t* from);

#endif
