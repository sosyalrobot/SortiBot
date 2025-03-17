#include <Servo.h>
#include "esp_camera.h"  // For ESP32-CAM module if used

// Servo motor objects
Servo baseServo;    // Base rotation
Servo armServo;     // Arm movement
Servo gripperServo; // Gripper control

// Pin definitions
#define BASE_PIN 9
#define ARM_PIN 10
#define GRIPPER_PIN 11
#define COLOR_SENSOR_PIN A0

// Color thresholds
#define RED_THRESHOLD 200
#define BLUE_THRESHOLD 150
#define GREEN_THRESHOLD 180

// Servo positions
#define HOME_POS 90
#define RED_BIN 45
#define BLUE_BIN 135
#define GREEN_BIN 0
#define PICKUP_HEIGHT 30
#define RELEASE_HEIGHT 60

class SortiBot {
private:
  int redValue, greenValue, blueValue;
  
  void readColorSensor() {
    // Simplified color reading - replace with actual sensor code
    redValue = analogRead(COLOR_SENSOR_PIN);
    greenValue = analogRead(COLOR_SENSOR_PIN + 1);
    blueValue = analogRead(COLOR_SENSOR_PIN + 2);
  }

public:
  void initialize() {
    baseServo.attach(BASE_PIN);
    armServo.attach(ARM_PIN);
    gripperServo.attach(GRIPPER_PIN);
    
    // Initial position
    baseServo.write(HOME_POS);
    armServo.write(HOME_POS);
    gripperServo.write(0);  // Gripper open
  }

  bool pickObject() {
    armServo.write(PICKUP_HEIGHT);  // Lower arm
    delay(500);
    gripperServo.write(90);         // Close gripper
    delay(300);
    armServo.write(HOME_POS);       // Raise arm
    delay(500);
    return true;  // Add error checking in real implementation
  }

  String identifyColor() {
    readColorSensor();
    
    if (redValue > RED_THRESHOLD && redValue > greenValue && redValue > blueValue) {
      return "RED";
    }
    else if (blueValue > BLUE_THRESHOLD && blueValue > redValue && blueValue > greenValue) {
      return "BLUE";
    }
    else if (greenValue > GREEN_THRESHOLD && greenValue > redValue && greenValue > blueValue) {
      return "GREEN";
    }
    return "UNKNOWN";
  }

  void sortObject(String color) {
    // Move to appropriate sorting position
    if (color == "RED") {
      baseServo.write(RED_BIN);
    }
    else if (color == "BLUE") {
      baseServo.write(BLUE_BIN);
    }
    else if (color == "GREEN") {
      baseServo.write(GREEN_BIN);
    }
    else {
      baseServo.write(HOME_POS);  // Unknown objects stay at home
      return;
    }
    
    delay(700);  // Allow time for movement
    releaseObject();
  }

  void releaseObject() {
    armServo.write(RELEASE_HEIGHT);
    delay(300);
    gripperServo.write(0);     // Open gripper
    delay(300);
    armServo.write(HOME_POS);  // Return to neutral height
    baseServo.write(HOME_POS); // Return to home position
  }

  void calibrate() {
    // Add calibration routine
    baseServo.write(HOME_POS);
    delay(1000);
    armServo.write(PICKUP_HEIGHT);
    delay(1000);
    armServo.write(HOME_POS);
  }
};

SortiBot robot;

void setup() {
  Serial.begin(115200);
  robot.initialize();
  robot.calibrate();
  Serial.println("SortiBot ready for sorting");
}

void loop() {
  // Main sorting operation
  if (robot.pickObject()) {
    String color = robot.identifyColor();
    Serial.print("Sorting object color: ");
    Serial.println(color);
    robot.sortObject(color);
    delay(1000);  // Wait before next sort
  }
  else {
    Serial.println("Failed to pick object");
    delay(2000);  // Wait before retry
  }
}