
#include "M3DPrintVue.h"
#include "gcode/parser.h"
#include "MarlinCore.h"
#include "module/printcounter.h" // for print jobs
#include "module/motion.h"
#include "module/temperature.h"

#include <ArduinoBLE.h>


String BLEName;

// create service and characteristics:
BLEService m3dPrintVueTelemetryService("8e088cd2-8100-11ee-b9d1-0242ac120002");
BLEFloatCharacteristic positionXCharactristic("8e088cd2-7101-11ee-b9d1-0242ac120002", BLERead);
BLEFloatCharacteristic positionYCharactristic("8e088cd2-7102-11ee-b9d1-0242ac120002", BLERead);
BLEFloatCharacteristic positionZCharactristic("8e088cd2-7103-11ee-b9d1-0242ac120002", BLERead | BLENotify);
BLEFloatCharacteristic positionECharactristic("8e088cd2-7104-11ee-b9d1-0242ac120002", BLERead);
BLEFloatCharacteristic temperatureCharactristic("8e088cd2-7105-11ee-b9d1-0242ac120002", BLERead);
BLEIntCharacteristic printingStatusCharactristic("8e088cd2-7106-11ee-b9d1-0242ac120002", BLERead | BLENotify);

//BLEFloatCharacteristic servoBSpeedCharactristic("8e088cd2-6106-11ee-b9d1-0242ac120002", BLEWrite);
//BLEStringCharacteristic expressionCharactristic("8e088cd2-6107-11ee-b9d1-0242ac120002", BLEWrite, 128);


#if ENABLED(M3DPrintVueSupport)

// M1101 start a new time lapse
bool M1101(){
    Serial.println("M1101");
    printingStatusCharactristic.setValue(print_job_timer.getStats().totalPrints);
}
// M1102 trigger a time-lapse photo
bool M1102(){
    Serial.println("M1102");
}
// M1103 End a time lapse
bool M1103(){
    Serial.println("M1103");
    printingStatusCharactristic.setValue(false);
}

void connectHandler(BLEDevice central)
{
    // central connected event handler
    Serial.print("PrintVue BLE Connected: ");
    Serial.println(central.address());
}

void disconnectHandler(BLEDevice central)
{
    // central disconnected event handler
    Serial.print("PrintVue BLE Disconncted");
    Serial.println(central.address());
}

void M3DPrintVueSetup(){
    BLE.begin();
    BLEName = "M3D Enabler";
    BLE.setLocalName(BLEName.c_str());
    
    BLE.setAdvertisedService(m3dPrintVueTelemetryService);
    m3dPrintVueTelemetryService.addCharacteristic(positionXCharactristic);
    m3dPrintVueTelemetryService.addCharacteristic(positionYCharactristic);
    m3dPrintVueTelemetryService.addCharacteristic(positionZCharactristic);
    m3dPrintVueTelemetryService.addCharacteristic(positionECharactristic);
    m3dPrintVueTelemetryService.addCharacteristic(temperatureCharactristic);

    BLE.setEventHandler(BLEConnected, connectHandler);
    BLE.setEventHandler(BLEDisconnected, disconnectHandler);
}
float lastX = -100;
float lastY = -100;
float lastZ = -100;
float lastE = -100;
float lastT = -100;

void M3DPrintVueLoop(){
    if (lastX!=  current_position.x){
        lastX = current_position.x;
        positionXCharactristic.setValue(current_position.x);
    }
    if (lastY!=  current_position.y){
        lastY = current_position.y;
        positionYCharactristic.setValue(current_position.y);
    }
    if (lastZ!=  current_position.z){
        lastZ = current_position.z;
        positionZCharactristic.setValue(current_position.z);
    }
    if (lastE!=  current_position.e){
        lastE = current_position.e;
        positionECharactristic.setValue(current_position.e);
    }
    if (lastT!= thermalManager.degHotend(0)){
        lastT = thermalManager.degHotend(0);
        temperatureCharactristic.setValue(thermalManager.degHotend(0));
    }
}
#endif