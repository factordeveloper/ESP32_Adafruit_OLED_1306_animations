#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Configuración de la pantalla OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Número de gotas de lluvia (menos para un efecto más limpio)
#define NUM_DROPS 10

// Estructura para las gotas de lluvia
struct RainDrop {
    int x;
    int y;
    int speed;
};

// Arreglo de gotas de lluvia
RainDrop rain[NUM_DROPS];

void setup() {
    Serial.begin(115200);

    // Inicializar pantalla OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
        Serial.println(F("Error al iniciar pantalla OLED"));
        for (;;);
    }

    display.clearDisplay();

    // Inicializar gotas en posiciones aleatorias
    for (int i = 0; i < NUM_DROPS; i++) {
        rain[i].x = random(0, SCREEN_WIDTH);
        rain[i].y = random(0, SCREEN_HEIGHT);
        rain[i].speed = random(2, 5); // Velocidades diferentes para cada gota
    }
}

void drawMinimalLandscape() {
    // Dibujar la luna llena con un efecto de halo
    display.fillCircle(100, 10, 10, SSD1306_WHITE); // Luna sólida
    display.drawCircle(100, 10, 12, SSD1306_WHITE); // Halo

    // Dibujar montañas minimalistas con líneas finas
    display.drawLine(0, 50, 40, 25, SSD1306_WHITE);
    display.drawLine(40, 25, 80, 50, SSD1306_WHITE);
    display.drawLine(50, 50, 100, 30, SSD1306_WHITE);
    display.drawLine(100, 30, 128, 50, SSD1306_WHITE);
}

void drawRain() {
    // Dibujar gotas de lluvia
    for (int i = 0; i < NUM_DROPS; i++) {
        display.drawPixel(rain[i].x, rain[i].y, SSD1306_WHITE);
        rain[i].y += rain[i].speed; // Caída con diferentes velocidades

        // Si la gota llega al final de la pantalla, reaparece en la parte superior
        if (rain[i].y >= SCREEN_HEIGHT) {
            rain[i].y = 0;
            rain[i].x = random(0, SCREEN_WIDTH);
            rain[i].speed = random(2, 5); // Asignar nueva velocidad
        }
    }
}

void loop() {
    display.clearDisplay();

    drawMinimalLandscape();  // Dibujar el paisaje minimalista
    drawRain();              // Dibujar la lluvia animada

    display.display();
    delay(50); // Control de la velocidad de la animación
}
