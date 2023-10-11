#pragma once
#ifndef _AIVICAM_DEF_H_
#define _AIVICAM_DEF_H_

#include <cstdint>

#define MAX_CAM_NUM                     4
#define INFO_MAX_BUFFER_SIZE            64

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

typedef struct _AIVI_CHUNK_DATA_CONTENT_
{
    unsigned char*      pChunkData;                                 
    unsigned int        nChunkID;                                   
    unsigned int        nChunkLen;                                  

    unsigned int        nReserved[8];                               

}AIVI_CHUNK_DATA_CONTENT;

typedef struct _AIVI_FRAME_OUT_INFO_
{
    unsigned short          nWidth;                                 
    unsigned short          nHeight;                                
    enum MvGvspPixelType    enPixelType;                            

    unsigned int            nFrameNum;                              
    unsigned int            nDevTimeStampHigh;                      
    unsigned int            nDevTimeStampLow;                       
    unsigned int            nReserved0;                             
    int64_t                 nHostTimeStamp;                         

    unsigned int            nFrameLen;                              
       
    unsigned int            nSecondCount;                           
    unsigned int            nCycleCount;                            
    unsigned int            nCycleOffset;                           

    float                   fGain;                                  
    float                   fExposureTime;                          
    unsigned int            nAverageBrightness;                     

    unsigned int            nRed;                                   
    unsigned int            nGreen;                                 
    unsigned int            nBlue;                                  

    unsigned int            nFrameCounter;                          
    unsigned int            nTriggerIndex;                          

    unsigned int            nInput;                                 
    unsigned int            nOutput;                                

    unsigned short          nOffsetX;                               
    unsigned short          nOffsetY;                               
    unsigned short          nChunkWidth;                            
    unsigned short          nChunkHeight;                           

    unsigned int            nLostPacket;                            

    unsigned int            nUnparsedChunkNum;                      
    union
    {
        AIVI_CHUNK_DATA_CONTENT* pUnparsedChunkContent;             
        int64_t                 nAligning;                          
    }UnparsedChunkList;

    unsigned int            nReserved[36];                          

}AIVI_FRAME_OUT_INFO;


typedef struct _AIVI_FRAME_OUT_
{
    unsigned char*          pBufAddr;                              
    AIVI_FRAME_OUT_INFO     stFrameInfo;                           

    unsigned int            nRes[16];                              

}AIVI_FRAME_OUT;

#endif
