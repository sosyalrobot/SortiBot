# SortiBot - Robotic Arm for Object Sorting

**SortiBot** is an open-source robotic arm project designed for sorting objects by color using a camera or color sensor, servo motors, and an Arduino microcontroller. Developed by [sosyalrobot](https://github.com/sosyalrobot), this project is ideal for applications like recycling automation, warehouse organization, or educational robotics.

## Features

- **Color-Based Sorting**: Identifies and sorts objects into designated bins based on color (red, blue, green).
- **Modular Design**: Built with an object-oriented approach for easy customization.
- **Servo Control**: Uses three servo motors for base rotation, arm movement, and gripper action.
- **Open Source**: Fully documented code and hardware requirements for community contributions.

## Hardware Requirements

- **Microcontroller**: Arduino Uno or ESP32
- **Servo Motors**: 3x (for base, arm, and gripper)
- **Color Sensor**: TCS34725 or similar (or ESP32-CAM for vision-based sorting)
- **Power Supply**: 5V-6V (depending on servo specs)
- **Structure**: 3D-printed or custom-built robotic arm
- **Sorting Bins**: Containers for sorted objects

## Software Requirements

- **Arduino IDE**: For programming and uploading the code
- **Libraries**:
  - `Servo.h` (included with Arduino IDE)
  - `esp_camera.h` (if using ESP32-CAM)
- **Optional**: Python with OpenCV/TensorFlow Lite for advanced vision processing

## Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/sosyalrobot/SortiBot.git
   cd SortiBot
   ```

2. **Assemble Hardware**:
   - Connect servo motors to pins 9 (base), 10 (arm), and 11 (gripper).
   - Attach the color sensor to analog pins (A0-A2) or configure I2C if using a specific sensor.
   - Build the physical arm structure (refer to `docs/hardware-guide.md` for suggested designs).

3. **Upload Code**:
   - Open `SortiBot.ino` in Arduino IDE.
   - Install required libraries via the Library Manager.
   - Upload the code to your microcontroller.

## Usage

1. Power on the SortiBot.
2. Place objects in the pickup area.
3. The arm will:
   - Pick up the object
   - Identify its color
   - Sort it to the appropriate bin (red: 45°, blue: 135°, green: 0°)
   - Return to home position

Example output in Serial Monitor:
```
SortiBot ready for sorting
Sorting object color: RED
Sorting object color: BLUE
```

## Configuration

- **Color Thresholds**: Adjust `RED_THRESHOLD`, `BLUE_THRESHOLD`, and `GREEN_THRESHOLD` in the code to match your sensor readings.
- **Servo Positions**: Modify `HOME_POS`, `RED_BIN`, etc., based on your physical setup.
- **Timing**: Tune delay values for smoother operation.

## Contributing

Contributions are welcome! Please:
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/YourFeature`)
3. Commit your changes (`git commit -m "Add YourFeature"`)
4. Push to the branch (`git push origin feature/YourFeature`)
5. Open a Pull Request

See [CONTRIBUTING.md](CONTRIBUTING.md) for more details.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Built by [sosyalrobot](https://github.com/sosyalrobot)
- Inspired by robotics and automation communities
- Thanks to the Arduino and open-source hardware communities

## Contact

For questions or suggestions, open an issue or reach out via GitHub: [sosyalrobot](https://github.com/sosyalrobot).
