
//% color="#AA278D" iconWidth=50 iconHeight=40
namespace DFRobot_SEN0233_AirQualityMonitor {

    //% board="arduino"
    //% block="Air Quality Monitor Initliallize Pin [SSER] Rx[SSTXD] Tx[SSRXD]" blockType="command"
    //% SSER.shadow="dropdown" SSER.options="SSER"
    //% SSRXD.shadow="dropdown" SSRXD.options="SSRXD"
    //% SSTXD.shadow="dropdown" SSTXD.options="SSTXD"

    export function beginSoftSerial(parameter: any, block: any) {
        let sser=parameter.SSER.code;
        let rx = parameter.SSRXD.code;
        let tx = parameter.SSTXD.code;

            Generator.addInclude("includeAQM","#include <DFRobot_SEN0233_AirQualityMonitor.h>");
            Generator.addInclude("includesoftSerial","#include <SoftwareSerial.h>");
                
            Generator.addObject("softSerialObject","SoftwareSerial",`${sser}(${rx}, ${tx});`);
            Generator.addObject("AQMObject"+sser,"DFRobot_SEN0233_AirQualityMonitor",`AQM_SEN0233(&${sser});`);
  
            Generator.addSetup("AQMSerialSetup"+sser,`${sser}.begin(9600);`);
          

    }

    //% block="Air Quality Monitor Initliallize Pin [SER] Rx[TXD] Tx[RXD]" blockType="command"
    //% SER.shadow="dropdown" SER.options="SER"
    //% RXD.shadow="dropdown" RXD.options="RXD"
    //% TXD.shadow="dropdown" TXD.options="TXD"

    export function beginSerial(parameter: any, block: any) {  
        let ser=parameter.SER.code;
        let rx = parameter.RXD.code;
        let tx = parameter.TXD.code;

            Generator.addInclude("includeAQM","#include <DFRobot_SEN0233_AirQualityMonitor.h>");
            Generator.addObject("AQMObject"+ser,"DFRobot_SEN0233_AirQualityMonitor",`AQM_SEN0233(&${ser});`);

            if(Generator.board==="arduino"){
                Generator.addSetup("AQMSerialSetup",`${ser}.begin(9600);`);
            }else if(Generator.board==="esp32"){
                Generator.addSetup("AQMSerialSetup",`${ser}.begin(9600,${rx},${tx});`);
            }
           

            

    }

    
    //% block="Air Quality Monitor Read data once" blockType="command"
    export function readSensor(){
        Generator.addCode("AQM_SEN0233.DFRobot_SEN0233_readData();");
    }

    //% block="Air Quality Monitor read [DAT] value" blockType="reporter"
    //% DAT.shadow="dropdown" DAT.options="DAT"
    export function readDate(parameter: any){
        let dat=parameter.DAT.code;
        switch(dat){
            case "PM2.5":
            Generator.addCode("AQM_SEN0233.DFRobot_SEN0233_getPMS()");
            break;
            case "Formaldehyde":
            Generator.addCode("AQM_SEN0233.DFRobot_SEN0233_getFMHDS()");
            break;
            case "Temperature":
            Generator.addCode("AQM_SEN0233.DFRobot_SEN0233_getTPS()");
            break;
            case "Humidity":
            Generator.addCode("AQM_SEN0233.DFRobot_SEN0233_getHDS()");
            break;

        }
        
    }


}
