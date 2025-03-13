#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Número de estrellas parpadeantes
#define NUM_STARS 8

// Estructura para las estrellas
struct Star {
    int x;
    int y;
    bool visible;
};

// Arreglo de estrellas
Star stars[NUM_STARS];

// Estado de animación del agua en el río
bool waveState = false;

void setup() {
    Serial.begin(115200);

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
        Serial.println(F("Error al iniciar pantalla OLED"));
        for (;;);
    }

    display.clearDisplay();

    // Inicializar estrellas en posiciones aleatorias
    for (int i = 0; i < NUM_STARS; i++) {
        stars[i].x = random(5, SCREEN_WIDTH - 5);
        stars[i].y = random(5, 20);  // Solo en la parte superior del cielo
        stars[i].visible = random(0, 2);  // Algunas visibles al inicio
    }
}

// Dibujar el paisaje del bosque nocturno
void drawNightForest() {
    // Dibujar la luna grande con reflejo en el río
    display.fillCircle(100, 15, 10, SSD1306_WHITE);  // Luna
    display.drawCircle(100, 15, 12, SSD1306_WHITE);  // Halo
    
    // Dibujar árboles minimalistas
    display.drawLine(20, 40, 20, 55, SSD1306_WHITE);
    display.drawTriangle(10, 40, 20, 25, 30, 40, SSD1306_WHITE);
    
    display.drawLine(60, 42, 60, 55, SSD1306_WHITE);
    display.drawTriangle(50, 42, 60, 28, 70, 42, SSD1306_WHITE);
    
    display.drawLine(110, 45, 110, 58, SSD1306_WHITE);
    display.drawTriangle(100, 45, 110, 30, 120, 45, SSD1306_WHITE);

    // Dibujar el río con reflejo de la luna
    display.drawLine(0, 55, 128, 55, SSD1306_WHITE); // Línea de agua
    if (waveState) {
        display.drawPixel(50, 56, SSD1306_WHITE);
        display.drawPixel(70, 57, SSD1306_WHITE);
        display.drawPixel(90, 56, SSD1306_WHITE);
    } else {
        display.drawPixel(55, 57, SSD1306_WHITE);
        display.drawPixel(75, 56, SSD1306_WHITE);
        display.drawPixel(95, 57, SSD1306_WHITE);
    }
}

// Dibujar estrellas que parpadean
void drawStars() {
    for (int i = 0; i < NUM_STARS; i++) {
        if (stars[i].visible) {
            display.drawPixel(stars[i].x, stars[i].y, SSD1306_WHITE);
        }

        // Alternar visibilidad cada ciclo
        if (random(0, 10) > 7) {
            stars[i].visible = !stars[i].visible;
        }
    }
}

void loop() {
    display.clearDisplay();

    drawNightForest();  // Dibujar el bosque con el río
    drawStars();        // Dibujar estrellas parpadeantes

    display.display();

    waveState = !waveState; // Cambiar estado de las ondas en el agua
    delay(500);  // Animación fluida
}

