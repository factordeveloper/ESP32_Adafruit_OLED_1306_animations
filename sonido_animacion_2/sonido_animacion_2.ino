#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Configuración de la onda de sonido
#define NUM_POINTS 64  // Mayor cantidad de puntos para suavizar la onda
float wave[NUM_POINTS];  // Valores de la onda

void setup() {
    Serial.begin(115200);

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
        Serial.println(F("Error al iniciar pantalla OLED"));
        for (;;);
    }

    display.clearDisplay();

    // Inicializar la onda con una señal senoidal suave
    for (int i = 0; i < NUM_POINTS; i++) {
        wave[i] = 15 * sin(i * 2 * PI / NUM_POINTS); // Onda senoidal base
    }
}

void drawWave() {
    int centerY = SCREEN_HEIGHT / 2; // Centro de la pantalla

    for (int i = 0; i < NUM_POINTS - 1; i++) {
        int x1 = i * (SCREEN_WIDTH / NUM_POINTS);
        int x2 = (i + 1) * (SCREEN_WIDTH / NUM_POINTS);
        int y1 = centerY + wave[i];
        int y2 = centerY + wave[i + 1];

        // Dibujar la línea de la onda conectando los puntos
        display.drawLine(x1, y1, x2, y2, SSD1306_WHITE);
    }

    // Desplazar la onda hacia la izquierda
    for (int i = 0; i < NUM_POINTS - 1; i++) {
        wave[i] = wave[i + 1];
    }

    // Generar una nueva muestra en el último punto con variaciones suaves
    wave[NUM_POINTS - 1] = 15 * sin(millis() / 200.0) + random(-2, 3);
}

void loop() {
    display.clearDisplay();
    
    drawWave();  // Dibujar la onda de sonido animada con interpolación suave

    display.display();
    delay(30);  // Menor delay para una animación ultra fluida
}
