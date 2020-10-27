
/* File generated by gen_cfile.py. Should not be modified. */

#ifndef SERVEROBJECT_H
#define SERVEROBJECT_H

#include "data.h"

/* Prototypes of function provided by object dictionnary */
UNS32 serverobject_valueRangeTest (UNS8 typeValue, void * value);
const indextable * serverobject_scanIndexOD (CO_Data *d, UNS16 wIndex, UNS32 * errorCode);

/* Master node data struct */
extern CO_Data serverobject_Data;
extern UNS16 Controlword;		/* Mapped at index 0x6040, subindex 0x00*/
extern UNS16 Statusword;		/* Mapped at index 0x6041, subindex 0x00*/
extern INTEGER8 Modes_of_operation;		/* Mapped at index 0x6060, subindex 0x00*/
extern INTEGER32 Velocity_sensor_actual_value;		/* Mapped at index 0x6069, subindex 0x00*/
extern INTEGER32 Velocity_actual_value;		/* Mapped at index 0x606C, subindex 0x00*/
extern INTEGER16 Current_actual_value;		/* Mapped at index 0x6078, subindex 0x00*/
extern INTEGER32 Target_position;		/* Mapped at index 0x607A, subindex 0x00*/
extern INTEGER32 Target_velocity;		/* Mapped at index 0x60FF, subindex 0x00*/

#endif // SERVEROBJECT_H