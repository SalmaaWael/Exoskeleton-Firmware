#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include <stdint.h>
#include <stdbool.h>

// Exoskeleton Data Structure (BLE Payload)
// Using (packed) is essential to ensure the data size matches exactly when received by the mobile application
typedef struct __attribute__((packed)) {
    uint8_t start_byte;        // Start byte to verify packet integrity (e.g., 0xAA)
    
    // Sensors Data
    float left_knee_angle;     // Left knee angle (IMU)
    float right_knee_angle;    // Right knee angle (IMU)
    uint16_t left_fsr_value;   // Left foot pressure force (FSR)
    uint16_t right_fsr_value;  // Right foot pressure force (FSR)
    
    // Motors Status
    bool is_left_motor_active; // Left motor status
    bool is_right_motor_active;// Right motor status
    
    // System Status
    uint8_t battery_level;     // Battery percentage (0-100)
    uint8_t system_error_code; // Error code (0 means no error)
    
    uint8_t end_byte;          // End byte (e.g., 0x55)
} ExoskeletonData_t;

// Create an instance of the struct to be updated within the tasks
ExoskeletonData_t exo_data = {
    .start_byte = 0xAA,
    .end_byte = 0x55,
    .battery_level = 100
};

#include "freertos/task.h"

// 1. Task to read sensors
void vTaskReadSensors(void *pvParameters) {
    while(1) {
        vTaskDelay(50 / portTICK_PERIOD_MS); 
    }
}

// 2. Task to control motors (Movement decisions)
void vTaskMotorControl(void *pvParameters) {
    while(1) {
        vTaskDelay(20 / portTICK_PERIOD_MS); 
    }
}

// 3. Bluetooth Task (Sending data to the mobile app)
void vTaskBLE_Comms(void *pvParameters) {
    while(1) {
        vTaskDelay(2000 / portTICK_PERIOD_MS); 
    }
}

void app_main(void) {
    printf("Exoskeleton System Initializing...\n");
    xTaskCreate(vTaskMotorControl, "MotorTask", 4096, NULL, 5, NULL);
    xTaskCreate(vTaskReadSensors, "SensorsTask", 4096, NULL, 4, NULL);
    xTaskCreate(vTaskBLE_Comms, "BLETask", 4096, NULL, 3, NULL);
}
