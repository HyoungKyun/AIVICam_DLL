#pragma once

#ifndef _AICAM_LIB_H_
#define _AICAM_LIB_H_
#include "pch.h"
#include "AIVICam_Err.h"
#include <string.h>

#ifndef AIVI_NULL
#define AIVI_NULL    0
#endif

#define MAX_CAM_NUM                     4
#define INFO_MAX_BUFFER_SIZE            64

#ifdef AIVICAM_EXPORTS
#define AIVICAM_LIB_API __declspec(dllexport)
#else
#define AIVICAM_LIB_API __declspec(dllimport)
#endif

typedef struct _AIVI_USB3_DEVICE_INFO_
{
    unsigned char       CrtlInEndPoint;
    unsigned char       CrtlOutEndPoint;
    unsigned char       StreamEndPoint;
    unsigned char       EventEndPoint;
    unsigned short      idVendor;
    unsigned short      idProduct;
    unsigned int        nDeviceNumber;
    unsigned char       chDeviceGUID[INFO_MAX_BUFFER_SIZE];
    unsigned char       chVendorName[INFO_MAX_BUFFER_SIZE];
    unsigned char       chModelName[INFO_MAX_BUFFER_SIZE];
    unsigned char       chFamilyName[INFO_MAX_BUFFER_SIZE];
    unsigned char       chDeviceVersion[INFO_MAX_BUFFER_SIZE];
    unsigned char       chManufacturerName[INFO_MAX_BUFFER_SIZE];
    unsigned char       chSerialNumber[INFO_MAX_BUFFER_SIZE];
    unsigned char       chUserDefinedName[INFO_MAX_BUFFER_SIZE];
    unsigned int        nbcdUSB;
    unsigned int        nDeviceAddress;

    unsigned int        nReserved[2];
}AIVI_USB3_DEVICE_INFO;

typedef struct _AIVI_DEVICE_INFO_
{
    unsigned short          nMajorVer;                         
    unsigned short          nMinorVer;                         
    unsigned int            nMacAddrHigh;                      
    unsigned int            nMacAddrLow;                       
    unsigned int            nTLayerType;                       
    unsigned int            nReserved[4];                 
  
    AIVI_USB3_DEVICE_INFO stUsb3VInfo;          
}AIVI_DEVICE_INFO;


typedef struct _AIVI_DEVICE_INFO_LIST_
{
    unsigned int        nDeviceNum;                                
    AIVI_DEVICE_INFO    DeviceInfo[MAX_CAM_NUM];
}AIVI_DEVICE_INFO_LIST;


class AIVICAM_LIB_API AIVICam_Lib
{
public:
    AIVICam_Lib();
    ~AIVICam_Lib();

    int GetCameraList(AIVI_DEVICE_INFO_LIST* pDeviceList);
    int CameraInitialize(int Index);

private:
    void*       m_hAIVICamHandle;
    int			m_nValidCamNum;
};

extern "C" {
    AIVICAM_LIB_API AIVICam_Lib* CreateCamera();
    AIVICAM_LIB_API void DestroyCamera(AIVICam_Lib* camera);    
}


#endif//_AICAM_LIB_H_