#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Número de copos de nieve
#define NUM_SNOWFLAKES 25

// Estructura para los copos de nieve
struct Snowflake {
    int x;
    int y;
    int speed;
};

// Arreglo de copos de nieve
Snowflake snow[NUM_SNOWFLAKES];

void setup() {
    Serial.begin(115200);

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
        Serial.println(F("Error al iniciar pantalla OLED"));
        for (;;);
    }

    display.clearDisplay();

    // Inicializar los copos de nieve en posiciones aleatorias
    for (int i = 0; i < NUM_SNOWFLAKES; i++) {
        snow[i].x = random(0, SCREEN_WIDTH);
        snow[i].y = random(0, SCREEN_HEIGHT);
        snow[i].speed = random(1, 3); // Velocidad de caída
    }
}

// Dibujar el fondo con montañas nevadas y el muñeco de nieve
void drawWinterLandscape() {
    // Dibujar montañas nevadas
    display.drawLine(0, 50, 40, 20, SSD1306_WHITE);
    display.drawLine(40, 20, 80, 50, SSD1306_WHITE);
    display.drawLine(50, 50, 100, 30, SSD1306_WHITE);
    display.drawLine(100, 30, 128, 50, SSD1306_WHITE);

    // Nieve en las montañas
    display.drawLine(40, 20, 35, 30, SSD1306_WHITE);
    display.drawLine(35, 30, 45, 30, SSD1306_WHITE);
    display.drawLine(90, 30, 85, 35, SSD1306_WHITE);
    display.drawLine(85, 35, 95, 35, SSD1306_WHITE);

    // Dibujar el muñeco de nieve ☃️
    display.fillCircle(105, 48, 7, SSD1306_WHITE); // Cuerpo inferior
    display.fillCircle(105, 38, 5, SSD1306_WHITE); // Cuerpo medio
    display.fillCircle(105, 30, 3, SSD1306_WHITE); // Cabeza
    display.drawPixel(104, 29, SSD1306_BLACK);  // Ojo izquierdo
    display.drawPixel(106, 29, SSD1306_BLACK);  // Ojo derecho
    display.drawPixel(105, 31, SSD1306_BLACK);  // Botón central
    display.drawLine(100, 38, 90, 35, SSD1306_WHITE);  // Brazo izquierdo
    display.drawLine(110, 38, 120, 35, SSD1306_WHITE); // Brazo derecho
    display.drawRect(102, 24, 6, 3, SSD1306_WHITE); // Sombrero
}

// Dibujar la nieve animada
void drawSnowfall() {
    for (int i = 0; i < NUM_SNOWFLAKES; i++) {
        display.drawPixel(snow[i].x, snow[i].y, SSD1306_WHITE);
        snow[i].y += snow[i].speed; // Mover hacia abajo

        // Si el copo de nieve llega al fondo, reaparece arriba
        if (snow[i].y >= SCREEN_HEIGHT) {
            snow[i].y = 0;
            snow[i].x = random(0, SCREEN_WIDTH);
            snow[i].speed = random(1, 3);
        }
    }
}

void loop() {
    display.clearDisplay();

    drawWinterLandscape(); // Dibujar el paisaje nevado
    drawSnowfall();        // Dibujar nieve animada

    display.display();
    delay(50); // Control de la velocidad de la animación
}
