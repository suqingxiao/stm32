
/* File generated by gen_cfile.py. Should not be modified. */

#ifndef SERVEROBJECT_H
#define SERVEROBJECT_H

#include "data.h"

/* Prototypes of function provided by object dictionnary */
UNS32 serverobject_valueRangeTest (UNS8 typeValue, void * value);
const indextable * serverobject_scanIndexOD (CO_Data *d, UNS16 wIndex, UNS32 * errorCode);

/* Master node data struct */
extern CO_Data serverobject_Data;
extern INTEGER32 up_roll;		/* Mapped at index 0x2004, subindex 0x00*/
extern INTEGER32 up_pitch;		/* Mapped at index 0x2008, subindex 0x00*/
extern INTEGER32 up_yaw;		/* Mapped at index 0x200B, subindex 0x00*/
extern INTEGER32 down_roll;		/* Mapped at index 0x2011, subindex 0x00*/
extern INTEGER32 down_pitch;		/* Mapped at index 0x2015, subindex 0x00*/
extern INTEGER32 down_yaw;		/* Mapped at index 0x2019, subindex 0x00*/

#endif // SERVEROBJECT_H
