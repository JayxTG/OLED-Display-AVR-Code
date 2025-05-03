/*
 * OLED Display Driver for AVR Microcontrollers
 * Author: Jayamadu Gammune
 * Description: This code provides functions to interface with an SSD1306 OLED display using I2C communication.
 * License: Fair Use License. This code is provided for educational and personal use. Users are free to modify, distribute, and use the code, provided it is not used for commercial purposes or in violation of any copyright laws. This code is provided "as is," without warranty of any kind. The author is not responsible for any damages, issues, or consequences arising from the use or misuse of this code.
 * Date: May 3, 2025
 */

// Define clock frequency and OLED I2C address
#define F_CPU 16000000UL
#define OLED_ADDRESS 0x3C
#define SCL_PIN    PC5   // Pin for SCL (Clock)
#define SDA_PIN    PC4   // Pin for SDA (Data)

// Display dimensions
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

// Commands for the SSD1306 OLED
#define OLED_COMMAND 0x00
#define OLED_DATA 0x40

// 5x7 font data for digits 0-9
const uint8_t font5x7[][5] = {
    // 0-9
    {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0
    {0x00, 0x42, 0x7F, 0x40, 0x00}, // 1
    {0x42, 0x61, 0x51, 0x49, 0x46}, // 2
    {0x21, 0x41, 0x45, 0x4B, 0x31}, // 3
    {0x18, 0x14, 0x12, 0x7F, 0x10}, // 4
    {0x27, 0x45, 0x45, 0x45, 0x39}, // 5
    {0x3C, 0x4A, 0x49, 0x49, 0x30}, // 6
    {0x01, 0x71, 0x09, 0x05, 0x03}, // 7
    {0x36, 0x49, 0x49, 0x49, 0x36}, // 8
    {0x06, 0x49, 0x49, 0x29, 0x1E}, // 9
    // A-Z
    {0x7E, 0x11, 0x11, 0x11, 0x7E}, // A
    {0x7F, 0x49, 0x49, 0x49, 0x36}, // B
    {0x3E, 0x41, 0x41, 0x41, 0x22}, // C
    {0x7F, 0x41, 0x41, 0x22, 0x1C}, // D
    {0x7F, 0x49, 0x49, 0x49, 0x41}, // E
    {0x7F, 0x09, 0x09, 0x09, 0x01}, // F
    {0x3E, 0x41, 0x49, 0x49, 0x7A}, // G
    {0x7F, 0x08, 0x08, 0x08, 0x7F}, // H
    {0x41, 0x7F, 0x41}, // I
    {0x30, 0x40, 0x41, 0x3F, 0x01}, // J
    {0x7F, 0x08, 0x14, 0x22, 0x41}, // K
    {0x7F, 0x40, 0x40, 0x40}, // L
    {0x7F, 0x20, 0x10, 0x20, 0x7F}, // M
    {0x7F, 0x30, 0x0E, 0x01, 0x7F}, // N
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, // O
    {0x7F, 0x09, 0x09, 0x09, 0x06}, // P
    {0x3E, 0x41, 0x51, 0x21, 0x5E}, // Q
    {0x7F, 0x09, 0x19, 0x29, 0x46}, // R
    {0x26, 0x49, 0x49, 0x49, 0x32}, // S
    {0x01, 0x01, 0x7F, 0x01, 0x01}, // T
    {0x3F, 0x40, 0x40, 0x40, 0x3F}, // U
    {0x1F, 0x20, 0x40, 0x20, 0x1F}, // V
    {0x3F, 0x40, 0x30, 0x40, 0x3F}, // W
    {0x63, 0x14, 0x08, 0x14, 0x63}, // X
    {0x07, 0x08, 0x70, 0x08, 0x07}, // Y
    {0x61, 0x51, 0x49, 0x45, 0x43}, // Z
    // a-z
    {0x00, 0x20, 0x54, 0x54, 0x78}, // a
    {0x7F, 0x48, 0x44, 0x44, 0x38}, // b
    {0x38, 0x44, 0x44, 0x44, 0x20}, // c
    {0x38, 0x44, 0x44, 0x48, 0x7F}, // d
    {0x38, 0x54, 0x54, 0x54, 0x18}, // e
    {0x08, 0x7E, 0x09, 0x01, 0x02}, // f
    {0x08, 0x14, 0x54, 0x54, 0x3C}, // g
    {0x7F, 0x08, 0x04, 0x04, 0x78}, // h
    {0x00, 0x44, 0x7D, 0x40, 0x00}, // i
    {0x20, 0x40, 0x44, 0x3D, 0x00}, // j
    {0x7F, 0x10, 0x28, 0x44, 0x00}, // k
    {0x00, 0x41, 0x7F, 0x40, 0x00}, // l
    {0x7C, 0x04, 0x18, 0x04, 0x78}, // m
    {0x7C, 0x08, 0x04, 0x04, 0x78}, // n
    {0x38, 0x44, 0x44, 0x44, 0x38}, // o
    {0xFC, 0x14, 0x14, 0x14, 0x08}, // p
    {0x08, 0x14, 0x14, 0x18, 0xFC}, // q
    {0x7C, 0x08, 0x04, 0x04, 0x08}, // r
    {0x48, 0x54, 0x54, 0x54, 0x20}, // s
    {0x04, 0x3F, 0x44, 0x40, 0x20}, // t
    {0x3C, 0x40, 0x40, 0x20, 0x7C}, // u
    {0x1C, 0x20, 0x40, 0x20, 0x1C}, // v
    {0x3C, 0x40, 0x30, 0x40, 0x3C}, // w
    {0x44, 0x28, 0x10, 0x28, 0x44}, // x
    {0x0C, 0x10, 0x60, 0x10, 0x0C}, // y
    {0x44, 0x4A, 0x49, 0x49, 0x31}, // z
};


void i2c_init(void) {
    // Set SCL and SDA as output pins (only if you are manually controlling the pins)
    DDRC |= (1 << SCL_PIN) | (1 << SDA_PIN);  
    TWSR = 0x00;  // Set prescaler to 1
    TWBR = 0x0C;  // Set SCL frequency to 400kHz
    TWCR = (1 << TWEN);  // Enable TWI (I2C)
}

void i2c_start(void) {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

void i2c_stop(void) {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    while (TWCR & (1 << TWSTO));
}

void i2c_write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

void oled_command(uint8_t cmd) {
    i2c_start();
    i2c_write(OLED_ADDRESS << 1); // Write address
    i2c_write(OLED_COMMAND);
    i2c_write(cmd);
    i2c_stop();
}

void oled_data(uint8_t data) {
    i2c_start();
    i2c_write(OLED_ADDRESS << 1); // Write address
    i2c_write(OLED_DATA);
    i2c_write(data);
    i2c_stop();
}

void oled_init(void) {
    _delay_ms(100);  // Wait for OLED to power up
    oled_command(0xAE); // Display off
    oled_command(0xD5); // Set display clock divide ratio/oscillator frequency
    oled_command(0x80); // Set divide ratio
    oled_command(0xA8); // Set multiplex ratio(1 to 64)
    oled_command(0x3F); // 1/64 duty
    oled_command(0xD3); // Set display offset
    oled_command(0x00); // No offset
    oled_command(0x40); // Set display start line
    oled_command(0x8D); // Set charge pump
    oled_command(0x14); // Enable charge pump
    oled_command(0x20); // Set memory addressing mode
    oled_command(0x00); // Horizontal addressing mode
    oled_command(0xA1); // Set segment re-map
    oled_command(0xC8); // Set COM output scan direction
    oled_command(0xDA); // Set COM pins hardware configuration
    oled_command(0x12);
    oled_command(0x81); // Set contrast control
    oled_command(0xCF);
    oled_command(0xD9); // Set pre-charge period
    oled_command(0xF1);
    oled_command(0xDB); // Set VCOMH deselect level
    oled_command(0x40);
    oled_command(0xA4); // Disable entire display on
    oled_command(0xA6); // Set normal display
    oled_command(0xAF); // Display on
}

void oled_clear(void) {
    for (uint8_t i = 0; i < 8; i++) {
        oled_command(0xB0 + i); // Set page address
        oled_command(0x00); // Set lower column address
        oled_command(0x10); // Set higher column address
        for (uint8_t j = 0; j < 128; j++) {
            oled_data(0x00);
        }
    }
}

void oled_set_cursor(uint8_t x, uint8_t y) {
    oled_command(0xB0 + y); // Set page address
    oled_command(0x00 + (x & 0x0F)); // Set lower column address
    oled_command(0x10 + ((x >> 4) & 0x0F)); // Set higher column address
}

void oled_write_char(char c) {
    if (c >= '0' && c <= '9') {
        // Handle digits
        for (uint8_t i = 0; i < 5; i++) {
            oled_data(font5x7[c - '0'][i]);
        }
    } else if (c >= 'A' && c <= 'Z') {
        // Handle uppercase letters
        for (uint8_t i = 0; i < 5; i++) {
            oled_data(font5x7[c - 'A' + 10][i]);
        }
    } else if (c >= 'a' && c <= 'z') {
        // Handle lowercase letters
        for (uint8_t i = 0; i < 5; i++) {
            oled_data(font5x7[c - 'a' + 36][i]);
        }
    } else {
        // Handle unknown characters
        for (uint8_t i = 0; i < 6; i++) {
            oled_data(0x00); // Space for unknown characters
        }
    }
    oled_data(0x00); // Space between characters
}

void oled_write_string(const char* str) {
    while (*str) {
        oled_write_char(*str++);
    }
}



int main(void) {
    i2c_init();
    oled_init();
    
    //Add your Program foir oled here
    oled_clear();
    oled_set_cursor(0, 0); // Position the cursor at the top left
    oled_write_string("Hello World 2");

    while (1) {
        // Main loop, do nothing here
    }

    return 0;
}