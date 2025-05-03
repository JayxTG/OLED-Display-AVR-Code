# OLED Display Driver for AVR Microcontrollers 🎮🖥️

## Author: Jayamadu Gammune 👨‍💻

### Description 📜
This code provides functions to interface with an SSD1306 OLED display using I2C communication on AVR microcontrollers. The driver supports basic operations like initialization, clearing the screen, setting the cursor, and displaying characters and digits. This code is designed for educational and personal use.

### License ⚖️
- **License**: Fair Use License.
- This code is provided for educational and personal use.
- Users are free to modify, distribute, and use the code, provided it is not used for commercial purposes or in violation of any copyright laws.
- This code is provided "as is," without warranty of any kind.
- The author is not responsible for any damages, issues, or consequences arising from the use or misuse of this code.

### Date 📅
May 3, 2025

---

### Features 💡
- **I2C Communication**: The code uses I2C to interface with the OLED display.
- **Character Display**: Supports displaying characters (including digits and letters).
- **OLED Initialization**: Initializes the OLED display with the correct configuration.
- **Screen Clear**: Clears the OLED screen with the `oled_clear()` function.
- **Cursor Control**: Set the cursor position for displaying characters.

---

### How to Use 🚀

1. **Include the Driver**:
   To use this OLED driver in your project, include the necessary functions and libraries as provided in the code.

2. **Setup I2C**:
   - Configure the I2C by initializing the clock frequency, SDA, and SCL pins.
   - Use the `i2c_init()` function to set up the I2C communication at 400kHz.

3. **Initialize OLED**:
   - Use the `oled_init()` function to initialize the OLED display and configure necessary settings.

4. **Display Data**:
   - You can write characters or digits using `oled_write_char()` function.
   - Set the cursor to the desired location with `oled_set_cursor()`.

---

### Code Snippets 🧑‍💻

```c
// Define clock frequency and OLED I2C address
#define F_CPU 16000000UL           // Clock frequency: 16 MHz
#define OLED_ADDRESS 0x3C          // I2C address for OLED
#define SCL_PIN    PC5             // Pin for SCL (Clock)
#define SDA_PIN    PC4             // Pin for SDA (Data)

// Display dimensions
#define DISPLAY_WIDTH 128          // OLED Width (128 pixels)
#define DISPLAY_HEIGHT 64          // OLED Height (64 pixels)

// OLED Commands
#define OLED_COMMAND 0x00          // Command Mode
#define OLED_DATA 0x40             // Data Mode

// 5x7 Font Data (0-9 and A-Z)
const uint8_t font5x7[][5] = {
    // Characters (0-9)
    {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0
    {0x00, 0x42, 0x7F, 0x40, 0x00}, // 1
    {0x42, 0x61, 0x51, 0x49, 0x46}, // 2
    {0x21, 0x41, 0x45, 0x4B, 0x31}, // 3
    {0x18, 0x14, 0x12, 0x7F, 0x10}, // 4
    // ... (remaining characters)
};

// I2C Functions 📡
void i2c_init(void) { 
    // Initialize I2C communication 
    DDRC |= (1 << SCL_PIN) | (1 << SDA_PIN);  
    TWSR = 0x00;  // Set prescaler to 1
    TWBR = 0x0C;  // Set SCL frequency to 400kHz
    TWCR = (1 << TWEN);  // Enable TWI (I2C)
}

void i2c_start(void) {
    // Start I2C transmission
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

void i2c_stop(void) {
    // Stop I2C transmission
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    while (TWCR & (1 << TWSTO));
}

void i2c_write(uint8_t data) {
    // Write data over I2C
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

// OLED Functions 🖥️
void oled_command(uint8_t cmd) {
    i2c_start();
    i2c_write(OLED_ADDRESS << 1);  // Write address
    i2c_write(OLED_COMMAND);       // Command mode
    i2c_write(cmd);                // Send command
    i2c_stop();
}

void oled_data(uint8_t data) {
    i2c_start();
    i2c_write(OLED_ADDRESS << 1);  // Write address
    i2c_write(OLED_DATA);          // Data mode
    i2c_write(data);               // Send data
    i2c_stop();
}

void oled_init(void) {
    // Initialize OLED Display
    _delay_ms(100);  // Wait for OLED to power up
    oled_command(0xAE);  // Display off
    oled_command(0xD5);  // Set display clock divide ratio/oscillator frequency
    oled_command(0x80);  // Set divide ratio
    // ... (Remaining initialization commands)
}

void oled_clear(void) {
    // Clear the OLED Display
    for (uint8_t i = 0; i < 8; i++) {
        oled_command(0xB0 + i);  // Set page address
        oled_command(0x00);      // Set lower column address
        oled_command(0x10);      // Set higher column address
        for (uint8_t j = 0; j < 128; j++) {
            oled_data(0x00);    // Clear pixel
        }
    }
}
```
---

### Pin Configuration 📌
- **SDA (Data)**: Pin `PC4`
- **SCL (Clock)**: Pin `PC5`
- **I2C Address**: `0x3C` (Default)

---

### Troubleshooting 🔧

- **No Display**: Ensure the I2C address is correct and that the wiring for SDA and SCL is properly set.
- **Flickering Display**: Check the power supply to the OLED display. Try adding a capacitor for stable voltage.
- **Wrong Characters**: Double-check your wiring and ensure proper initialization of the display. Verify that the I2C communication is set correctly.

---

### Contributions 🤝
Feel free to fork this project and contribute! If you have any improvements or bug fixes, please submit a pull request. If you encounter issues, open an issue ticket, and I'll try to address them as soon as possible.

---

### Credits 🎉
- This project was created by **Jayamadu Gammune**. All rights reserved.
- Special thanks to the authors of the SSD1306 OLED display libraries and documentation.
- Thanks to the AVR community for providing valuable resources and tutorials on microcontroller interfacing.

---

### References 📚
1. **AVR Microcontroller Documentation**: Official documentation for AVR microcontrollers, which provides detailed information on peripherals like I2C.
2. **SSD1306 Datasheet**: Detailed datasheet of the SSD1306 OLED display, which describes the initialization sequence and commands.
3. **Arduino I2C Library**: The I2C library for Arduino, useful for understanding the I2C protocol.
