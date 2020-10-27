
/* File generated by gen_cfile.py. Should not be modified. */

#include "serverobject.h"

/**************************************************************************/
/* Declaration of mapped variables                                        */
/**************************************************************************/
INTEGER32 up_roll = 0x0;		/* Mapped at index 0x2004, subindex 0x00 */
INTEGER32 up_pitch = 0x0;		/* Mapped at index 0x2008, subindex 0x00 */
INTEGER32 up_yaw = 0x0;		/* Mapped at index 0x200B, subindex 0x00 */
INTEGER32 down_roll = 0x0;		/* Mapped at index 0x2011, subindex 0x00 */
INTEGER32 down_pitch = 0x0;		/* Mapped at index 0x2015, subindex 0x00 */
INTEGER32 down_yaw = 0x0;		/* Mapped at index 0x2019, subindex 0x00 */

/**************************************************************************/
/* Declaration of value range types                                       */
/**************************************************************************/

#define valueRange_EMC 0x9F /* Type for index 0x1003 subindex 0x00 (only set of value 0 is possible) */
UNS32 serverobject_valueRangeTest (UNS8 typeValue, void * value)
{
  switch (typeValue) {
    case valueRange_EMC:
      if (*(UNS8*)value != (UNS8)0) return OD_VALUE_RANGE_EXCEEDED;
      break;
  }
  return 0;
}

/**************************************************************************/
/* The node id                                                            */
/**************************************************************************/
/* node_id default value.*/
UNS8 serverobject_bDeviceNodeId = 0x01;

/**************************************************************************/
/* Array of message processing information */

const UNS8 serverobject_iam_a_slave = 1;

TIMER_HANDLE serverobject_heartBeatTimers[1] = {TIMER_NONE};

/*
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

                               OBJECT DICTIONARY

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
*/

/* index 0x1000 :   Device Type. */
                    UNS32 serverobject_obj1000 = 0x0;	/* 0 */
                    subindex serverobject_Index1000[] = 
                     {
                       { RO, uint32, sizeof (UNS32), (void*)&serverobject_obj1000, NULL }
                     };

/* index 0x1001 :   Error Register. */
                    UNS8 serverobject_obj1001 = 0x0;	/* 0 */
                    subindex serverobject_Index1001[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&serverobject_obj1001, NULL }
                     };

/* index 0x1003 :   Pre-defined Error Field */
                    UNS8 serverobject_highestSubIndex_obj1003 = 0; /* number of subindex - 1*/
                    UNS32 serverobject_obj1003[] = 
                    {
                      0x0	/* 0 */
                    };
                    subindex serverobject_Index1003[] = 
                     {
                       { RW, valueRange_EMC, sizeof (UNS8), (void*)&serverobject_highestSubIndex_obj1003, NULL },
                       { RO, uint32, sizeof (UNS32), (void*)&serverobject_obj1003[0], NULL }
                     };

/* index 0x1005 :   SYNC COB ID */
                    UNS32 serverobject_obj1005 = 0x0;   /* 0 */

/* index 0x1006 :   Communication / Cycle Period */
                    UNS32 serverobject_obj1006 = 0x0;   /* 0 */

/* index 0x100C :   Guard Time */ 
                    UNS16 serverobject_obj100C = 0x0;   /* 0 */

/* index 0x100D :   Life Time Factor */ 
                    UNS8 serverobject_obj100D = 0x0;   /* 0 */

/* index 0x1014 :   Emergency COB ID */
                    UNS32 serverobject_obj1014 = 0x80 + 0x00;   /* 128 + NodeID */

/* index 0x1016 :   Consumer Heartbeat Time. */
                    UNS8 serverobject_highestSubIndex_obj1016 = 1; /* number of subindex - 1*/
                    UNS32 serverobject_obj1016[] = 
                    {
                      0x0	/* 0 */
                    };
                    subindex serverobject_Index1016[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&serverobject_highestSubIndex_obj1016, NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1016[0], NULL }
                     };

/* index 0x1017 :   Producer Heartbeat Time */ 
                    UNS16 serverobject_obj1017 = 0x0;   /* 0 */

/* index 0x1018 :   Identity. */
                    UNS8 serverobject_highestSubIndex_obj1018 = 4; /* number of subindex - 1*/
                    UNS32 serverobject_obj1018_Vendor_ID = 0x0;	/* 0 */
                    UNS32 serverobject_obj1018_Product_Code = 0x0;	/* 0 */
                    UNS32 serverobject_obj1018_Revision_Number = 0x0;	/* 0 */
                    UNS32 serverobject_obj1018_Serial_Number = 0x0;	/* 0 */
                    subindex serverobject_Index1018[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&serverobject_highestSubIndex_obj1018, NULL },
                       { RO, uint32, sizeof (UNS32), (void*)&serverobject_obj1018_Vendor_ID, NULL },
                       { RO, uint32, sizeof (UNS32), (void*)&serverobject_obj1018_Product_Code, NULL },
                       { RO, uint32, sizeof (UNS32), (void*)&serverobject_obj1018_Revision_Number, NULL },
                       { RO, uint32, sizeof (UNS32), (void*)&serverobject_obj1018_Serial_Number, NULL }
                     };

/* index 0x1200 :   Server SDO Parameter. */
                    UNS8 serverobject_highestSubIndex_obj1200 = 2; /* number of subindex - 1*/
                    UNS32 serverobject_obj1200_COB_ID_Client_to_Server_Receive_SDO = 0x601;	/* 1536 */
                    UNS32 serverobject_obj1200_COB_ID_Server_to_Client_Transmit_SDO = 0x581;	/* 1408 */
                    subindex serverobject_Index1200[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&serverobject_highestSubIndex_obj1200, NULL },
                       { RO, uint32, sizeof (UNS32), (void*)&serverobject_obj1200_COB_ID_Client_to_Server_Receive_SDO, NULL },
                       { RO, uint32, sizeof (UNS32), (void*)&serverobject_obj1200_COB_ID_Server_to_Client_Transmit_SDO, NULL }
                     };

/* index 0x1400 :   Receive PDO 1 Parameter. */
                    UNS8 serverobject_highestSubIndex_obj1400 = 6; /* number of subindex - 1*/
                    UNS32 serverobject_obj1400_COB_ID_used_by_PDO = 0x200;	/* 512 */
                    UNS8 serverobject_obj1400_Transmission_Type = 0x0;	/* 0 */
                    UNS16 serverobject_obj1400_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 serverobject_obj1400_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 serverobject_obj1400_Event_Timer = 0x0;	/* 0 */
                    UNS8 serverobject_obj1400_SYNC_start_value = 0x0;	/* 0 */
                    subindex serverobject_Index1400[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&serverobject_highestSubIndex_obj1400, NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1400_COB_ID_used_by_PDO, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1400_Transmission_Type, NULL },
                       { RW, uint16, sizeof (UNS16), (void*)&serverobject_obj1400_Inhibit_Time, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1400_Compatibility_Entry, NULL },
                       { RW, uint16, sizeof (UNS16), (void*)&serverobject_obj1400_Event_Timer, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1400_SYNC_start_value, NULL }
                     };

/* index 0x1401 :   Receive PDO 2 Parameter. */
                    UNS8 serverobject_highestSubIndex_obj1401 = 6; /* number of subindex - 1*/
                    UNS32 serverobject_obj1401_COB_ID_used_by_PDO = 0x300;	/* 768 */
                    UNS8 serverobject_obj1401_Transmission_Type = 0x0;	/* 0 */
                    UNS16 serverobject_obj1401_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 serverobject_obj1401_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 serverobject_obj1401_Event_Timer = 0x0;	/* 0 */
                    UNS8 serverobject_obj1401_SYNC_start_value = 0x0;	/* 0 */
                    subindex serverobject_Index1401[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&serverobject_highestSubIndex_obj1401, NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1401_COB_ID_used_by_PDO, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1401_Transmission_Type, NULL },
                       { RW, uint16, sizeof (UNS16), (void*)&serverobject_obj1401_Inhibit_Time, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1401_Compatibility_Entry, NULL },
                       { RW, uint16, sizeof (UNS16), (void*)&serverobject_obj1401_Event_Timer, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1401_SYNC_start_value, NULL }
                     };

/* index 0x1402 :   Receive PDO 3 Parameter. */
                    UNS8 serverobject_highestSubIndex_obj1402 = 6; /* number of subindex - 1*/
                    UNS32 serverobject_obj1402_COB_ID_used_by_PDO = 0x400;	/* 1024 */
                    UNS8 serverobject_obj1402_Transmission_Type = 0x0;	/* 0 */
                    UNS16 serverobject_obj1402_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 serverobject_obj1402_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 serverobject_obj1402_Event_Timer = 0x0;	/* 0 */
                    UNS8 serverobject_obj1402_SYNC_start_value = 0x0;	/* 0 */
                    subindex serverobject_Index1402[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&serverobject_highestSubIndex_obj1402, NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1402_COB_ID_used_by_PDO, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1402_Transmission_Type, NULL },
                       { RW, uint16, sizeof (UNS16), (void*)&serverobject_obj1402_Inhibit_Time, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1402_Compatibility_Entry, NULL },
                       { RW, uint16, sizeof (UNS16), (void*)&serverobject_obj1402_Event_Timer, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1402_SYNC_start_value, NULL }
                     };

/* index 0x1403 :   Receive PDO 4 Parameter. */
                    UNS8 serverobject_highestSubIndex_obj1403 = 6; /* number of subindex - 1*/
                    UNS32 serverobject_obj1403_COB_ID_used_by_PDO = 0x500;	/* 1280 */
                    UNS8 serverobject_obj1403_Transmission_Type = 0x0;	/* 0 */
                    UNS16 serverobject_obj1403_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 serverobject_obj1403_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 serverobject_obj1403_Event_Timer = 0x0;	/* 0 */
                    UNS8 serverobject_obj1403_SYNC_start_value = 0x0;	/* 0 */
                    subindex serverobject_Index1403[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&serverobject_highestSubIndex_obj1403, NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1403_COB_ID_used_by_PDO, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1403_Transmission_Type, NULL },
                       { RW, uint16, sizeof (UNS16), (void*)&serverobject_obj1403_Inhibit_Time, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1403_Compatibility_Entry, NULL },
                       { RW, uint16, sizeof (UNS16), (void*)&serverobject_obj1403_Event_Timer, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1403_SYNC_start_value, NULL }
                     };

/* index 0x1600 :   Receive PDO 1 Mapping. */
                    UNS8 serverobject_highestSubIndex_obj1600 = 8; /* number of subindex - 1*/
                    UNS32 serverobject_obj1600[] = 
                    {
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0	/* 0 */
                    };
                    subindex serverobject_Index1600[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_highestSubIndex_obj1600, NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1600[0], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1600[1], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1600[2], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1600[3], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1600[4], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1600[5], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1600[6], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1600[7], NULL }
                     };

/* index 0x1601 :   Receive PDO 2 Mapping. */
                    UNS8 serverobject_highestSubIndex_obj1601 = 8; /* number of subindex - 1*/
                    UNS32 serverobject_obj1601[] = 
                    {
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0	/* 0 */
                    };
                    subindex serverobject_Index1601[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_highestSubIndex_obj1601, NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1601[0], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1601[1], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1601[2], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1601[3], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1601[4], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1601[5], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1601[6], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1601[7], NULL }
                     };

/* index 0x1602 :   Receive PDO 3 Mapping. */
                    UNS8 serverobject_highestSubIndex_obj1602 = 8; /* number of subindex - 1*/
                    UNS32 serverobject_obj1602[] = 
                    {
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0	/* 0 */
                    };
                    subindex serverobject_Index1602[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_highestSubIndex_obj1602, NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1602[0], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1602[1], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1602[2], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1602[3], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1602[4], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1602[5], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1602[6], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1602[7], NULL }
                     };

/* index 0x1603 :   Receive PDO 4 Mapping. */
                    UNS8 serverobject_highestSubIndex_obj1603 = 8; /* number of subindex - 1*/
                    UNS32 serverobject_obj1603[] = 
                    {
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0	/* 0 */
                    };
                    subindex serverobject_Index1603[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_highestSubIndex_obj1603, NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1603[0], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1603[1], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1603[2], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1603[3], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1603[4], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1603[5], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1603[6], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1603[7], NULL }
                     };

/* index 0x1800 :   Transmit PDO 1 Parameter. */
                    UNS8 serverobject_highestSubIndex_obj1800 = 6; /* number of subindex - 1*/
                    UNS32 serverobject_obj1800_COB_ID_used_by_PDO = 0x180;	/* 384 */
                    UNS8 serverobject_obj1800_Transmission_Type = 0x0;	/* 0 */
                    UNS16 serverobject_obj1800_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 serverobject_obj1800_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 serverobject_obj1800_Event_Timer = 0x0;	/* 0 */
                    UNS8 serverobject_obj1800_SYNC_start_value = 0x0;	/* 0 */
                    subindex serverobject_Index1800[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&serverobject_highestSubIndex_obj1800, NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1800_COB_ID_used_by_PDO, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1800_Transmission_Type, NULL },
                       { RW, uint16, sizeof (UNS16), (void*)&serverobject_obj1800_Inhibit_Time, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1800_Compatibility_Entry, NULL },
                       { RW, uint16, sizeof (UNS16), (void*)&serverobject_obj1800_Event_Timer, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1800_SYNC_start_value, NULL }
                     };

/* index 0x1801 :   Transmit PDO 2 Parameter. */
                    UNS8 serverobject_highestSubIndex_obj1801 = 6; /* number of subindex - 1*/
                    UNS32 serverobject_obj1801_COB_ID_used_by_PDO = 0x280;	/* 640 */
                    UNS8 serverobject_obj1801_Transmission_Type = 0x0;	/* 0 */
                    UNS16 serverobject_obj1801_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 serverobject_obj1801_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 serverobject_obj1801_Event_Timer = 0x0;	/* 0 */
                    UNS8 serverobject_obj1801_SYNC_start_value = 0x0;	/* 0 */
                    subindex serverobject_Index1801[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&serverobject_highestSubIndex_obj1801, NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1801_COB_ID_used_by_PDO, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1801_Transmission_Type, NULL },
                       { RW, uint16, sizeof (UNS16), (void*)&serverobject_obj1801_Inhibit_Time, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1801_Compatibility_Entry, NULL },
                       { RW, uint16, sizeof (UNS16), (void*)&serverobject_obj1801_Event_Timer, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1801_SYNC_start_value, NULL }
                     };

/* index 0x1802 :   Transmit PDO 3 Parameter. */
                    UNS8 serverobject_highestSubIndex_obj1802 = 6; /* number of subindex - 1*/
                    UNS32 serverobject_obj1802_COB_ID_used_by_PDO = 0x380;	/* 896 */
                    UNS8 serverobject_obj1802_Transmission_Type = 0x0;	/* 0 */
                    UNS16 serverobject_obj1802_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 serverobject_obj1802_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 serverobject_obj1802_Event_Timer = 0x0;	/* 0 */
                    UNS8 serverobject_obj1802_SYNC_start_value = 0x0;	/* 0 */
                    subindex serverobject_Index1802[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&serverobject_highestSubIndex_obj1802, NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1802_COB_ID_used_by_PDO, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1802_Transmission_Type, NULL },
                       { RW, uint16, sizeof (UNS16), (void*)&serverobject_obj1802_Inhibit_Time, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1802_Compatibility_Entry, NULL },
                       { RW, uint16, sizeof (UNS16), (void*)&serverobject_obj1802_Event_Timer, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1802_SYNC_start_value, NULL }
                     };

/* index 0x1803 :   Transmit PDO 4 Parameter. */
                    UNS8 serverobject_highestSubIndex_obj1803 = 6; /* number of subindex - 1*/
                    UNS32 serverobject_obj1803_COB_ID_used_by_PDO = 0x480;	/* 1152 */
                    UNS8 serverobject_obj1803_Transmission_Type = 0x0;	/* 0 */
                    UNS16 serverobject_obj1803_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 serverobject_obj1803_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 serverobject_obj1803_Event_Timer = 0x0;	/* 0 */
                    UNS8 serverobject_obj1803_SYNC_start_value = 0x0;	/* 0 */
                    subindex serverobject_Index1803[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&serverobject_highestSubIndex_obj1803, NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1803_COB_ID_used_by_PDO, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1803_Transmission_Type, NULL },
                       { RW, uint16, sizeof (UNS16), (void*)&serverobject_obj1803_Inhibit_Time, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1803_Compatibility_Entry, NULL },
                       { RW, uint16, sizeof (UNS16), (void*)&serverobject_obj1803_Event_Timer, NULL },
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_obj1803_SYNC_start_value, NULL }
                     };

/* index 0x1A00 :   Transmit PDO 1 Mapping. */
                    UNS8 serverobject_highestSubIndex_obj1A00 = 8; /* number of subindex - 1*/
                    UNS32 serverobject_obj1A00[] = 
                    {
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0	/* 0 */
                    };
                    subindex serverobject_Index1A00[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_highestSubIndex_obj1A00, NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A00[0], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A00[1], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A00[2], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A00[3], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A00[4], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A00[5], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A00[6], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A00[7], NULL }
                     };

/* index 0x1A01 :   Transmit PDO 2 Mapping. */
                    UNS8 serverobject_highestSubIndex_obj1A01 = 8; /* number of subindex - 1*/
                    UNS32 serverobject_obj1A01[] = 
                    {
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0	/* 0 */
                    };
                    subindex serverobject_Index1A01[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_highestSubIndex_obj1A01, NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A01[0], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A01[1], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A01[2], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A01[3], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A01[4], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A01[5], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A01[6], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A01[7], NULL }
                     };

/* index 0x1A02 :   Transmit PDO 3 Mapping. */
                    UNS8 serverobject_highestSubIndex_obj1A02 = 8; /* number of subindex - 1*/
                    UNS32 serverobject_obj1A02[] = 
                    {
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0	/* 0 */
                    };
                    subindex serverobject_Index1A02[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_highestSubIndex_obj1A02, NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A02[0], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A02[1], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A02[2], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A02[3], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A02[4], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A02[5], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A02[6], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A02[7], NULL }
                     };

/* index 0x1A03 :   Transmit PDO 4 Mapping. */
                    UNS8 serverobject_highestSubIndex_obj1A03 = 8; /* number of subindex - 1*/
                    UNS32 serverobject_obj1A03[] = 
                    {
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0	/* 0 */
                    };
                    subindex serverobject_Index1A03[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&serverobject_highestSubIndex_obj1A03, NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A03[0], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A03[1], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A03[2], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A03[3], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A03[4], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A03[5], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A03[6], NULL },
                       { RW, uint32, sizeof (UNS32), (void*)&serverobject_obj1A03[7], NULL }
                     };

/* index 0x2004 :   Mapped variable up_roll */
                    subindex serverobject_Index2004[] = 
                     {
                       { RW, int32, sizeof (INTEGER32), (void*)&up_roll, NULL }
                     };

/* index 0x2008 :   Mapped variable up_pitch */
                    subindex serverobject_Index2008[] = 
                     {
                       { RW, int32, sizeof (INTEGER32), (void*)&up_pitch, NULL }
                     };

/* index 0x200B :   Mapped variable up_yaw */
                    subindex serverobject_Index200B[] = 
                     {
                       { RW, int32, sizeof (INTEGER32), (void*)&up_yaw, NULL }
                     };

/* index 0x2011 :   Mapped variable down_roll */
                    subindex serverobject_Index2011[] = 
                     {
                       { RW, int32, sizeof (INTEGER32), (void*)&down_roll, NULL }
                     };

/* index 0x2015 :   Mapped variable down_pitch */
                    subindex serverobject_Index2015[] = 
                     {
                       { RW, int32, sizeof (INTEGER32), (void*)&down_pitch, NULL }
                     };

/* index 0x2019 :   Mapped variable down_yaw */
                    subindex serverobject_Index2019[] = 
                     {
                       { RW, int32, sizeof (INTEGER32), (void*)&down_yaw, NULL }
                     };

/**************************************************************************/
/* Declaration of pointed variables                                       */
/**************************************************************************/

const indextable serverobject_objdict[] = 
{
  { (subindex*)serverobject_Index1000,sizeof(serverobject_Index1000)/sizeof(serverobject_Index1000[0]), 0x1000},
  { (subindex*)serverobject_Index1001,sizeof(serverobject_Index1001)/sizeof(serverobject_Index1001[0]), 0x1001},
  { (subindex*)serverobject_Index1016,sizeof(serverobject_Index1016)/sizeof(serverobject_Index1016[0]), 0x1016},
  { (subindex*)serverobject_Index1018,sizeof(serverobject_Index1018)/sizeof(serverobject_Index1018[0]), 0x1018},
  { (subindex*)serverobject_Index1200,sizeof(serverobject_Index1200)/sizeof(serverobject_Index1200[0]), 0x1200},
  { (subindex*)serverobject_Index1400,sizeof(serverobject_Index1400)/sizeof(serverobject_Index1400[0]), 0x1400},
  { (subindex*)serverobject_Index1401,sizeof(serverobject_Index1401)/sizeof(serverobject_Index1401[0]), 0x1401},
  { (subindex*)serverobject_Index1402,sizeof(serverobject_Index1402)/sizeof(serverobject_Index1402[0]), 0x1402},
  { (subindex*)serverobject_Index1403,sizeof(serverobject_Index1403)/sizeof(serverobject_Index1403[0]), 0x1403},
  { (subindex*)serverobject_Index1600,sizeof(serverobject_Index1600)/sizeof(serverobject_Index1600[0]), 0x1600},
  { (subindex*)serverobject_Index1601,sizeof(serverobject_Index1601)/sizeof(serverobject_Index1601[0]), 0x1601},
  { (subindex*)serverobject_Index1602,sizeof(serverobject_Index1602)/sizeof(serverobject_Index1602[0]), 0x1602},
  { (subindex*)serverobject_Index1603,sizeof(serverobject_Index1603)/sizeof(serverobject_Index1603[0]), 0x1603},
  { (subindex*)serverobject_Index1800,sizeof(serverobject_Index1800)/sizeof(serverobject_Index1800[0]), 0x1800},
  { (subindex*)serverobject_Index1801,sizeof(serverobject_Index1801)/sizeof(serverobject_Index1801[0]), 0x1801},
  { (subindex*)serverobject_Index1802,sizeof(serverobject_Index1802)/sizeof(serverobject_Index1802[0]), 0x1802},
  { (subindex*)serverobject_Index1803,sizeof(serverobject_Index1803)/sizeof(serverobject_Index1803[0]), 0x1803},
  { (subindex*)serverobject_Index1A00,sizeof(serverobject_Index1A00)/sizeof(serverobject_Index1A00[0]), 0x1A00},
  { (subindex*)serverobject_Index1A01,sizeof(serverobject_Index1A01)/sizeof(serverobject_Index1A01[0]), 0x1A01},
  { (subindex*)serverobject_Index1A02,sizeof(serverobject_Index1A02)/sizeof(serverobject_Index1A02[0]), 0x1A02},
  { (subindex*)serverobject_Index1A03,sizeof(serverobject_Index1A03)/sizeof(serverobject_Index1A03[0]), 0x1A03},
  { (subindex*)serverobject_Index2004,sizeof(serverobject_Index2004)/sizeof(serverobject_Index2004[0]), 0x2004},
  { (subindex*)serverobject_Index2008,sizeof(serverobject_Index2008)/sizeof(serverobject_Index2008[0]), 0x2008},
  { (subindex*)serverobject_Index200B,sizeof(serverobject_Index200B)/sizeof(serverobject_Index200B[0]), 0x200B},
  { (subindex*)serverobject_Index2011,sizeof(serverobject_Index2011)/sizeof(serverobject_Index2011[0]), 0x2011},
  { (subindex*)serverobject_Index2015,sizeof(serverobject_Index2015)/sizeof(serverobject_Index2015[0]), 0x2015},
  { (subindex*)serverobject_Index2019,sizeof(serverobject_Index2019)/sizeof(serverobject_Index2019[0]), 0x2019},
};

const indextable * serverobject_scanIndexOD (CO_Data *d, UNS16 wIndex, UNS32 * errorCode)
{
	int i;
	switch(wIndex){
		case 0x1000: i = 0;break;
		case 0x1001: i = 1;break;
		case 0x1016: i = 2;break;
		case 0x1018: i = 3;break;
		case 0x1200: i = 4;break;
		case 0x1400: i = 5;break;
		case 0x1401: i = 6;break;
		case 0x1402: i = 7;break;
		case 0x1403: i = 8;break;
		case 0x1600: i = 9;break;
		case 0x1601: i = 10;break;
		case 0x1602: i = 11;break;
		case 0x1603: i = 12;break;
		case 0x1800: i = 13;break;
		case 0x1801: i = 14;break;
		case 0x1802: i = 15;break;
		case 0x1803: i = 16;break;
		case 0x1A00: i = 17;break;
		case 0x1A01: i = 18;break;
		case 0x1A02: i = 19;break;
		case 0x1A03: i = 20;break;
		case 0x2004: i = 21;break;
		case 0x2008: i = 22;break;
		case 0x200B: i = 23;break;
		case 0x2011: i = 24;break;
		case 0x2015: i = 25;break;
		case 0x2019: i = 26;break;
		default:
			*errorCode = OD_NO_SUCH_OBJECT;
			return NULL;
	}
	*errorCode = OD_SUCCESSFUL;
	return &serverobject_objdict[i];
}

/* 
 * To count at which received SYNC a PDO must be sent.
 * Even if no pdoTransmit are defined, at least one entry is computed
 * for compilations issues.
 */
s_PDO_status serverobject_PDO_status[4] = {s_PDO_status_Initializer,s_PDO_status_Initializer,s_PDO_status_Initializer,s_PDO_status_Initializer};

const quick_index serverobject_firstIndex = {
  4, /* SDO_SVR */
  0, /* SDO_CLT */
  5, /* PDO_RCV */
  9, /* PDO_RCV_MAP */
  13, /* PDO_TRS */
  17 /* PDO_TRS_MAP */
};

const quick_index serverobject_lastIndex = {
  4, /* SDO_SVR */
  0, /* SDO_CLT */
  8, /* PDO_RCV */
  12, /* PDO_RCV_MAP */
  16, /* PDO_TRS */
  20 /* PDO_TRS_MAP */
};

const UNS16 serverobject_ObjdictSize = sizeof(serverobject_objdict)/sizeof(serverobject_objdict[0]); 

CO_Data serverobject_Data = CANOPEN_NODE_DATA_INITIALIZER(serverobject);

