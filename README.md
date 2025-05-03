# Autonomous-light-finder-follower-robot
autonomous robot that finds the brightest light source and follows it, also performs a celebration routine once it has arrived at a proximity to the light source in a room.

# 🌞 Autonomous Light Finder-Follower Robot (Arduino)

An autonomous robotic vehicle designed to find and follow the brightest source of light using Arduino and a variety of environmental sensors. The system includes live display, speed/mileage tracking, obstacle avoidance, and temperature/humidity monitoring, making it a robust showcase of multi-sensor fusion and control.

## 🚀 Features
- 🔦 **Light Detection:** Uses dual LDRs to detect and steer toward the brightest light source.
- 📟 **OLED Display:** Shows brightness, temperature, humidity, speed, and mileage in real-time.
- 💡 **LED Indicators:** Visually represent light intensity detected by each LDR.
- 🎛 **Speed Control:** Potentiometer allows dynamic motor speed calibration.
- 📏 **Obstacle Avoidance:** Ultrasonic sensor halts robot when objects are too close.
- 🌡 **Environmental Monitoring:** DHT22 sensor for temperature and humidity.
- 📏 **Mileage Tracking:** Speed sensors calculate total distance traveled.
- 🔔 **Feedback Alert:** Buzzer indicates state changes (e.g., light found, stop triggered).
- 🟢 **Button Activation:** Start/stop robot operation with a physical push button.

## 🧰 Hardware Components
- Arduino Uno
- 2x LDR sensors
- OLED Display (SSD1306 recommended)
- 2x LEDs
- HC-SR04 Ultrasonic Sensor
- DHT22 Temperature/Humidity Sensor
- Rotary Potentiometer
- 2x Speed Sensors (IR encoder type)
- Buzzer
- Push Button
- L298N Motor Driver
- Chassis + DC Motors + Wheels
- Battery Pack

## 📂 Project Structure
light-finder-robot/
├── src/
│ ├── light_tracking.ino # Main logic to read LDR and adjust motor direction
│ ├── oled_display.ino # OLED display logic (brightness, temp, humidity, speed)
│ ├── ultrasonic.ino # Obstacle detection logic
│ ├── motor_control.ino # Potentiometer + PWM speed control
│ ├── speed_sensor.ino # Mileage calculation using speed sensors
│ ├── dht22_sensor.ino # Temperature and humidity reading
│ ├── buzzer_feedback.ino # Event alerts
│ └── main.ino # Master integration file combining all modules
├── images/
│ ├── robot_photo.jpg
│ └── oled_sample_display.jpg
├── docs/
│ └── wiring_diagram.pdf
└── README.md


## 🛠 How to Use

1. Wire all components according to the wiring diagram.
2. Flash `main.ino` or modularly upload parts into functions inside a central sketch.
3. Adjust `thresholds` for LDRs and distance limits in code as per your environment.
4. Upload to Arduino Uno via Arduino IDE or PlatformIO.
5. Power the robot, press the button, and watch it autonomously search for light and follow!

## 📸 Demo

![WhatsApp Image 2024-07-22 at 13 51 05_f85ca4a2](https://github.com/user-attachments/assets/e71955af-35c7-4e87-a49d-4867635bf348)


## 🔮 Possible Improvements
- Use PID control for smoother directional control
- Add Bluetooth or WiFi telemetry
- Solar charging to align with the robot’s light-seeking nature

## 👨‍💻 Author
- Oluwaniyi Victor Momoh – [@Niyi-Momoh](https://github.com/Niyi-Momoh)



