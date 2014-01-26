#ifndef GLOBAL_H_
#define GLOBAL_H_

#ifndef bool
#define bool unsigned char
#define true 1
#define false 0
#endif

#include "map.h"

#define INPUT_PRESS 1
#define INPUT_RELEASE 0

typedef enum {Unknown, Spark, Hl101} eBoxType;
typedef enum {eKeyRemoteControl, eKeyFrontPanel} eKeyType;

typedef struct Context_s {
  void* /* RemoteControl_t */  *r; /* instance data */
  int                          fd; /* filedescriptor of fd */

} Context_t;

typedef struct {
  unsigned int delay;
  unsigned int period;

} tLongKeyPressSupport;

int getInternalCode(tButton * cButtons, const char cCode[3]);

int getInternalCodeHex(tButton * cButtons, const unsigned char cCode);

int printKeyMap(tButton * cButtons);

int checkTuxTxt(const int cCode);

void sendInputEvent(const int cCode);
void sendInputEventT(const unsigned int type, const int cCode);

int getEventDevice();

int selectRemote(Context_t  *context, eBoxType type);

void setInputEventRepeatRate(unsigned int delay, unsigned int period);

#endif
