#pragma once
#ifndef _AIVICAM_ERR_H_
#define _AIVICAM_ERR_H_

#define AIVI_OK						0x00000000

#define AIVI_ERR_HANDLE					0x80000000
#define AIVI_ERR_SUPPORT                0x80000001  
#define AIVI_ERR_BUFOVER                0x80000002  
#define AIVI_ERR_CALLORDER			0x80000003
#define AIVI_ERR_PARAMETER			0x80000004
#define AIVI_ERR_RESOURCE               0x80000006  
#define AIVI_ERR_NODATA                 0x80000007  
#define AIVI_ERR_PRECONDITION           0x80000008  
#define AIVI_ERR_VERSION                0x80000009  
#define AIVI_ERR_NOENOUGH_BUF           0x8000000A  
#define AIVI_ERR_ABNORMAL_IMAGE         0x8000000B  
#define AIVI_ERR_LOAD_LIBRARY           0x8000000C  
#define AIVI_ERR_NOOUTBUF               0x8000000D  
#define AIVI_ERR_ENCRYPT                0x8000000E  
#define AIVI_ERR_CLOSE					0x8000000F
#define AIVI_ERR_GRABSTART				0x80000010
#define AIVI_ERR_GRABSTOP				0x8000000F
#define AIVI_ERR_NODEVICE				0x80000011
#define AIVI_ERR_INITIALFAIL			0x80000012
#define AIVI_ERR_UNKNOW                 0x800000FF

#define AIVI_ERR_GC_GENERIC             0x80000100  
#define AIVI_ERR_GC_ARGUMENT            0x80000101  
#define AIVI_ERR_GC_RANGE               0x80000102  
#define AIVI_ERR_GC_PROPERTY            0x80000103  
#define AIVI_ERR_GC_RUNTIME             0x80000104  
#define AIVI_ERR_GC_LOGICAL             0x80000105  
#define AIVI_ERR_GC_ACCESS              0x80000106  
#define AIVI_ERR_GC_TIMEOUT             0x80000107  
#define AIVI_ERR_GC_DYNAMICCAST         0x80000108  
#define AIVI_ERR_GC_UNKNOW              0x800001FF  

#define AIVI_ERR_NOT_IMPLEMENTED        0x80000200  
#define AIVI_ERR_INVALID_ADDRESS        0x80000201  
#define AIVI_ERR_WRITE_PROTECT          0x80000202  
#define AIVI_ERR_ACCESS_DENIED          0x80000203  
#define AIVI_ERR_BUSY                   0x80000204  
#define AIVI_ERR_PACKET                 0x80000205  
#define AIVI_ERR_NETER                  0x80000206  
#define AIVI_ERR_IP_CONFLICT            0x80000221  

#define AIVI_ERR_USB_READ               0x80000300  
#define AIVI_ERR_USB_WRITE              0x80000301  
#define AIVI_ERR_USB_DEVICE             0x80000302  
#define AIVI_ERR_USB_GENICAM            0x80000303  
#define AIVI_ERR_USB_BANDWIDTH          0x80000304  
#define AIVI_ERR_USB_DRIVER             0x80000305  
#define AIVI_ERR_USB_UNKNOW             0x800003FF  

#define AIVI_ERR_UPG_FILE_MISMATCH      0x80000400  
#define AIVI_ERR_UPG_LANGUSGE_MISMATCH  0x80000401  
#define AIVI_ERR_UPG_CONFLICT           0x80000402  
#define AIVI_ERR_UPG_INNER_ERR          0x80000403  
#define AIVI_ERR_UPG_UNKNOW             0x800004FF  

#endif