
#include "M3DPrintVue.h"
#include "gcode/parser.h"
#include "MarlinCore.h"
#include "module/printcounter.h" // for print jobs
#include "module/motion.h"
#include "module/temperature.h"

#define debug_pv
#if defined(debug_pv)
#define PV_Debug(x) Serial.print(x)
#define PV_Debugln(x) Serial.println(x)
#else
#define PV_Debug(x)
#define PV_Debugln(x)
#endif

//#include <ArduinoBLE.h>

#define comSerial Serial1
#define print_job_timer_status_totalPrints print_job_timer.getStats().totalPrints
#define temp thermalManager.temp_hotend->celsius
// M1101 start a new time lapse
bool M1101()
{
    
  PV_Debug("M1101 @ ");
  PV_Debugln(print_job_timer_status_totalPrints);
  //if(comSerial.connected())
    comSerial.println(String("begin ") + String(print_job_timer_status_totalPrints));
  return true;
}
// M1102 trigger a time-lapse photo
bool M1102()
{
  PV_Debug("M1102 @ ");
  PV_Debugln(current_position.z);
  //if(comSerial.connected())
    comSerial.println(String("inc ") + String(current_position.z)); 
  return true;
}
// M1103 End a time lapse
bool M1103()
{
  PV_Debugln("M1103");
  //if(comSerial.connected())
    comSerial.println(String("end "));
  return true;
}


float lastX = -100;
float lastY = -100;
float lastZ = -100;
float lastE = -100;
float lastT = -100;

void M3DPrintVueSetup()
{
  PV_Debugln("M3DPrintVueSetup()");
  //comSerial.begin("M3D Enabler PV");
  //comSerial.register_callback(Bt_Status);

  comSerial.begin(115200, SERIAL_8N1, -1, 13);
}
void M3DPrintVueLoop()
{  
  if (lastX != current_position.x)
  {
    lastX = current_position.x;
    //if(comSerial.connected())
      comSerial.println(String("x ") + String(current_position.x));
    PV_Debug("x change = ");
    PV_Debugln(lastX);
  }
  if (lastY != current_position.y)
  {
    lastY = current_position.y;
    //if(comSerial.connected())
      comSerial.println(String("y ") + String(current_position.y));
    PV_Debug("y change = ");
    PV_Debugln(lastY);
  }
  if (lastZ != current_position.z)
  {
    lastZ = current_position.z;
    //if(comSerial.connected())
      comSerial.println(String("z ") + String(current_position.z));
    PV_Debug("z change = ");
    PV_Debugln(lastZ);
  }
  if (lastE != current_position.e)
  {
    lastE = current_position.e;
    //if(comSerial.connected())
      comSerial.println(String("e ") + String(current_position.e));
    PV_Debug("e change = ");
    PV_Debugln(lastE);
  }
  if (lastT != temp)
  {
    lastT = temp;
    //if(comSerial.connected())
      comSerial.println(String("x ") + String(temp));
    PV_Debug("temp change = ");
    PV_Debugln(lastT);
  }
}

// String BLEName;

// // create service and characteristics:
// BLEService m3dPrintVueTelemetryService("8e088cd2-8100-11ee-b9d1-0242ac120002");
// BLEFloatCharacteristic positionXCharactristic("8e088cd2-7101-11ee-b9d1-0242ac120002", BLERead);
// BLEFloatCharacteristic positionYCharactristic("8e088cd2-7102-11ee-b9d1-0242ac120002", BLERead);
// BLEFloatCharacteristic positionZCharactristic("8e088cd2-7103-11ee-b9d1-0242ac120002", BLERead | BLENotify);
// BLEFloatCharacteristic positionECharactristic("8e088cd2-7104-11ee-b9d1-0242ac120002", BLERead);
// BLEFloatCharacteristic temperatureCharactristic("8e088cd2-7105-11ee-b9d1-0242ac120002", BLERead);
// BLEIntCharacteristic printingStatusCharactristic("8e088cd2-7106-11ee-b9d1-0242ac120002", BLERead | BLENotify);

// //BLEFloatCharacteristic servoBSpeedCharactristic("8e088cd2-6106-11ee-b9d1-0242ac120002", BLEWrite);
// //BLEStringCharacteristic expressionCharactristic("8e088cd2-6107-11ee-b9d1-0242ac120002", BLEWrite, 128);


// #if ENABLED(M3DPrintVueSupport)

// // M1101 start a new time lapse
// bool M1101(){
//     PV_Debugln("M1101");
//     printingStatusCharactristic.setValue(print_job_timer.getStats().totalPrints);
//     return true;
// }
// // M1102 trigger a time-lapse photo
// bool M1102(){
//     PV_Debugln("M1102");
//     return true;
// }
// // M1103 End a time lapse
// bool M1103(){
//     PV_Debugln("M1103");
//     printingStatusCharactristic.setValue(false);
//     return true;
// }

// void connectHandler(BLEDevice central)
// {
//     // central connected event handler
//     PV_Debug("PrintVue BLE Connected: ");
//     PV_Debugln(central.address());
// }

// void disconnectHandler(BLEDevice central)
// {
//     // central disconnected event handler
//     PV_Debug("PrintVue BLE Disconncted");
//     PV_Debugln(central.address());
// }

// void M3DPrintVueSetup(){
//     BLE.begin();
//     BLEName = "M3D Enabler";
//     BLE.setLocalName(BLEName.c_str());
    
//     BLE.setAdvertisedService(m3dPrintVueTelemetryService);
//     m3dPrintVueTelemetryService.addCharacteristic(positionXCharactristic);
//     m3dPrintVueTelemetryService.addCharacteristic(positionYCharactristic);
//     m3dPrintVueTelemetryService.addCharacteristic(positionZCharactristic);
//     m3dPrintVueTelemetryService.addCharacteristic(positionECharactristic);
//     m3dPrintVueTelemetryService.addCharacteristic(temperatureCharactristic);

//     BLE.setEventHandler(BLEConnected, connectHandler);
//     BLE.setEventHandler(BLEDisconnected, disconnectHandler);
// }
// float lastX = -100;
// float lastY = -100;
// float lastZ = -100;
// float lastE = -100;
// float lastT = -100;

// void M3DPrintVueLoop(){
//     if (lastX!=  current_position.x){
//         lastX = current_position.x;
//         positionXCharactristic.setValue(current_position.x);
//     }
//     if (lastY!=  current_position.y){
//         lastY = current_position.y;
//         positionYCharactristic.setValue(current_position.y);
//     }
//     if (lastZ!=  current_position.z){
//         lastZ = current_position.z;
//         positionZCharactristic.setValue(current_position.z);
//     }
//     if (lastE!=  current_position.e){
//         lastE = current_position.e;
//         positionECharactristic.setValue(current_position.e);
//     }
//     if (lastT!= thermalManager.degHotend(0)){
//         lastT = thermalManager.degHotend(0);
//         temperatureCharactristic.setValue(thermalManager.degHotend(0));
//     }
// }
// #endif