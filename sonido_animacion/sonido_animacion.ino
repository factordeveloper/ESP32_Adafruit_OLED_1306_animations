#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Configuración de la onda de sonido
#define NUM_BARS 32   // Número de barras de la onda (más barras para un efecto más fluido)
int wave[NUM_BARS];   // Alturas de las ondas

void setup() {
    Serial.begin(115200);

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
        Serial.println(F("Error al iniciar pantalla OLED"));
        for (;;);
    }

    display.clearDisplay();

    // Inicializar las alturas de las ondas con valores aleatorios
    for (int i = 0; i < NUM_BARS; i++) {
        wave[i] = random(10, 30);
    }
}

void drawWave() {
    int barWidth = SCREEN_WIDTH / NUM_BARS; // Ancho de cada barra de onda

    for (int i = 0; i < NUM_BARS - 1; i++) {
        int x1 = i * barWidth;
        int x2 = (i + 1) * barWidth;
        int y1 = SCREEN_HEIGHT / 2 - wave[i] / 2;
        int y2 = SCREEN_HEIGHT / 2 - wave[i + 1] / 2;

        // Dibujar la línea de onda conectada para suavizar el efecto
        display.drawLine(x1, y1, x2, y2, SSD1306_WHITE);
    }

    // Desplazar la onda hacia la izquierda para un efecto de osciloscopio
    for (int i = 0; i < NUM_BARS - 1; i++) {
        wave[i] = wave[i + 1];
    }

    // Generar una nueva altura en el último punto
    wave[NUM_BARS - 1] = random(10, 30);
}

void loop() {
    display.clearDisplay();
    
    drawWave();  // Dibujar la onda de sonido animada con desplazamiento

    display.display();
    delay(50);  // Menor delay para una animación más fluida
}
