#include "DFRobot_SEN0233_AirQualityMonitor.h"


uint8_t DFRobot_SEN0233_AirQualityMonitor::DFRobot_SEN0233_getPMS(){  
return ((_sRecv.pm25A_H<<8)+_sRecv.pm25A_L);
}

uint8_t DFRobot_SEN0233_AirQualityMonitor::DFRobot_SEN0233_getFMHDS(){  
return ((_sRecv.fmhd_H<<8)+_sRecv.fmhd_L);
}

uint8_t DFRobot_SEN0233_AirQualityMonitor::DFRobot_SEN0233_getTPS(){  
return (((_sRecv.tp_H<<8)+_sRecv.tp_L)/10);
}

uint8_t DFRobot_SEN0233_AirQualityMonitor::DFRobot_SEN0233_getHDS(){  
return (((_sRecv.hd_H<<8)+_sRecv.hd_L)/10);
}

int8_t DFRobot_SEN0233_AirQualityMonitor::DFRobot_SEN0233_readData()
{
  uint8_t   i = 0;
  uint8_t   CR1 = 0;
  uint8_t   CR2 = 0;
  uint8_t   *pRecv = (uint8_t*) &_sRecv;

    while(_pSerial->available()) {
      if(_pSerial->read() == DFGT_RECV_HEAD1) {
        if(_pSerial->read() == DFGT_RECV_HEAD2) {
            for(i = 0; i < sizeof(_sRecv); i ++){
              pRecv[i] = _pSerial->read();
              CR2+=pRecv[i];
            }
            CR1=(_sRecv.cr1<<8)+_sRecv.cr2;
            
            if(CR1!=CR2){
                for(i = 0; i < sizeof(_sRecv); i ++){
                  pRecv[i] = 0;
                }
              return CHECK_ERR;
            }
            return DF_OK;  
          }
        }
    }
    return READ_ERR;


}



