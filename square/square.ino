#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Configuración de la pantalla OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Configuración del cuadrado
int x = 10;          // Posición inicial en X
int y = 10;          // Posición inicial en Y
int size = 10;       // Tamaño del cuadrado
int speedX = 2;      // Velocidad en X
int speedY = 2;      // Velocidad en Y

void setup() {
    Serial.begin(115200);
    
    // Inicializar pantalla OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
        Serial.println(F("Error al iniciar pantalla OLED"));
        for (;;);
    }

    display.clearDisplay();
}

void loop() {
    display.clearDisplay(); // Borra la pantalla en cada frame
    
    // Dibujar el cuadrado
    display.fillRect(x, y, size, size, SSD1306_WHITE);
    
    // Mostrar en pantalla
    display.display();

    // Actualizar posición
    x += speedX;
    y += speedY;

    // Rebote en los bordes horizontales
    if (x <= 0 || x + size >= SCREEN_WIDTH) {
        speedX = -speedX; // Invertir dirección en X
    }

    // Rebote en los bordes verticales
    if (y <= 0 || y + size >= SCREEN_HEIGHT) {
        speedY = -speedY; // Invertir dirección en Y
    }

    delay(20); // Controla la velocidad del movimiento
}
