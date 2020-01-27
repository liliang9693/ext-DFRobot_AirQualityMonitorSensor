#ifndef DFROBOT_SEN0233_AIRQUALITYMONITOR
#define DFROBOT_SEN0233_AIRQUALITYMONITOR

#include "Arduino.h"
#include "Stream.h"

#define DF_OK   0
#define READ_ERR  -1
#define CHECK_ERR  -2

#define DFGT_RECV_HEAD1   0x42
#define DFGT_RECV_HEAD2   0x4d


typedef struct {
  uint8_t   lenth_H;
  uint8_t   lenth_L;
  uint8_t   pm1_H;//CF=1,标准颗粒物下的浓度
  uint8_t   pm1_L;
  uint8_t   pm25_H;
  uint8_t   pm25_L;
  uint8_t   pm10_H;
  uint8_t   pm10_L;
  uint8_t   pm1A_H;//大气环境下的浓度
  uint8_t   pm1A_L;
  uint8_t   pm25A_H;
  uint8_t   pm25A_L;
  uint8_t   pm10A_H;
  uint8_t   pm10A_L;
  uint8_t   um03_H;
  uint8_t   um03_L;
  uint8_t   um05_H;
  uint8_t   um05_L;
  uint8_t   um1_H;
  uint8_t   um1_L;
  uint8_t   um25_H;
  uint8_t   um25_L;
  uint8_t   um50_H;
  uint8_t   um50_L;
  uint8_t   um10_H;
  uint8_t   um10_L;
  uint8_t   fmhd_H;
  uint8_t   fmhd_L;
  uint8_t   tp_H;
  uint8_t   tp_L;
  uint8_t   hd_H;
  uint8_t   hd_L;
  uint8_t   null_H;
  uint8_t   null_L;
  uint8_t   version;
  uint8_t   err;
  uint8_t   cr1;
  uint8_t   cr2;

} AQM_SEN0233_data_t;

class DFRobot_SEN0233_AirQualityMonitor
{
public:
  DFRobot_SEN0233_AirQualityMonitor(Stream  *pSerial) { _pSerial = pSerial; }

  int8_t    DFRobot_SEN0233_readData();
  uint8_t    DFRobot_SEN0233_getPMS();
  uint8_t    DFRobot_SEN0233_getFMHDS();
  uint8_t    DFRobot_SEN0233_getTPS();
  uint8_t    DFRobot_SEN0233_getHDS();
  
private:
  AQM_SEN0233_data_t      _sRecv;
  Stream   *_pSerial;
};

#endif
