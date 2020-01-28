#include "DFRobot_SEN0233_AirQualityMonitor.h"


float DFRobot_SEN0233_AirQualityMonitor::DFRobot_SEN0233_getPMS(){  
  uint16_t val=((((uint16_t)_sRecv.pm25A_H)<<8)+_sRecv.pm25A_L);
  return ((float)val);
}

float DFRobot_SEN0233_AirQualityMonitor::DFRobot_SEN0233_getFMHDS(){ 
  uint16_t val= ((((uint16_t)_sRecv.fmhd_H)<<8)+_sRecv.fmhd_L);
  return (((float)val)/1000.0);
}

float DFRobot_SEN0233_AirQualityMonitor::DFRobot_SEN0233_getTPS(){  
  uint16_t val=(((uint16_t)_sRecv.tp_H<<8)+_sRecv.tp_L);
  return (((float)val)/10.0);
}

float DFRobot_SEN0233_AirQualityMonitor::DFRobot_SEN0233_getHDS(){  
  uint16_t val=((((uint16_t)_sRecv.hd_H)<<8)+_sRecv.hd_L);
  return (((float)val)/10.0);
}

uint8_t DFRobot_SEN0233_AirQualityMonitor::DFRobot_SEN0233_readData()
{
  uint8_t   i = 0;
  uint16_t   CR1 = 0;
  uint16_t   CR2 = 0;
  uint8_t   *pRecv = (uint8_t*) &_sRecv;

    while(_pSerial->available()) {
      if(_pSerial->read() == DFGT_RECV_HEAD1) {
        delay(5);
        if(_pSerial->read() == DFGT_RECV_HEAD2) {
            for(i = 0; i < sizeof(_sRecv); i ++){
              pRecv[i] = _pSerial->read();
              Serial.print(pRecv[i], HEX);
              if(i<(sizeof(_sRecv)-2)) CR2+=pRecv[i];
              delay(2);
            }
            Serial.println(" ");
            Serial.println(_sRecv.cr1, HEX);
            Serial.println(_sRecv.cr2, HEX);
            CR2=CR2+0x42+0x4d;
            CR1=(((uint16_t)_sRecv.cr1)<<8)+_sRecv.cr2;
            Serial.println(CR1, HEX);
            Serial.println(CR2, HEX);
            if(CR1!=CR2){
                for(i = 0; i < sizeof(_sRecv); i ++){
                  pRecv[i] = 0;
                }
                delay(5);
                Serial.println("CHECK_ERR");delay(5);
              return CHECK_ERR;
            }
            Serial.println("DF_OK");
            return DF_OK;  
          }
        }
    }
    Serial.println("READ_ERR");
    return READ_ERR;


}



