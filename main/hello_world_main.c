#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include <stdint.h>
#include <stdbool.h>

// هيكل بيانات الـ Exoskeleton (BLE Payload)
// استخدام (packed) ضروري جداً لضمان تطابق حجم البيانات عند استلامها في الموبايل أبلكيشن
typedef struct __attribute__((packed)) {
    uint8_t start_byte;        // بايت البداية للتأكد من سلامة الحزمة (مثلاً 0xAA)
    
    // بيانات الحساسات (Sensors)
    float left_knee_angle;     // زاوية الركبة اليسرى (IMU)
    float right_knee_angle;    // زاوية الركبة اليمنى (IMU)
    uint16_t left_fsr_value;   // قوة الضغط على القدم اليسرى (FSR)
    uint16_t right_fsr_value;  // قوة الضغط على القدم اليمنى (FSR)
    
    // حالة المواتير (Motors)
    bool is_left_motor_active; // حالة الموتور الأيسر
    bool is_right_motor_active;// حالة الموتور الأيمن
    
    // حالة النظام (System Status)
    uint8_t battery_level;     // نسبة البطارية (0-100)
    uint8_t system_error_code; // كود الأخطاء (0 يعني لا يوجد خطأ)
    
    uint8_t end_byte;          // بايت النهاية (مثلاً 0x55)
} ExoskeletonData_t;

// إنشاء نسخة من الهيكل عشان نحدثها جوه المهام
ExoskeletonData_t exo_data = {
    .start_byte = 0xAA,
    .end_byte = 0x55,
    .battery_level = 100
};

#include "freertos/task.h"

// 1. مهمة قراءة الحساسات
void vTaskReadSensors(void *pvParameters) {
    while(1) {
        vTaskDelay(50 / portTICK_PERIOD_MS); 
    }
}

// 2. مهمة التحكم في المواتير (قرارات الحركة)
void vTaskMotorControl(void *pvParameters) {
    while(1) {
        vTaskDelay(20 / portTICK_PERIOD_MS); 
    }
}

// 3. مهمة البلوتوث (إرسال البيانات للموبايل)
void vTaskBLE_Comms(void *pvParameters) {
    while(1) {
        vTaskDelay(200 / portTICK_PERIOD_MS); 
    }
}

void app_main(void) {
    printf("Exoskeleton System Initializing...\n");
    xTaskCreate(vTaskMotorControl, "MotorTask", 4096, NULL, 5, NULL);
    xTaskCreate(vTaskReadSensors, "SensorsTask", 4096, NULL, 4, NULL);
    xTaskCreate(vTaskBLE_Comms, "BLETask", 4096, NULL, 3, NULL);
}