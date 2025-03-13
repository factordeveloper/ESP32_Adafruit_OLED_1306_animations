#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Configuración del espectro
#define NUM_BARS 16  // Número de barras en el espectro
int spectrum[NUM_BARS];  // Altura de cada barra

void setup() {
    Serial.begin(115200);

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
        Serial.println(F("Error al iniciar pantalla OLED"));
        for (;;);
    }

    display.clearDisplay();

    // Inicializar las barras del espectro con valores aleatorios
    for (int i = 0; i < NUM_BARS; i++) {
        spectrum[i] = random(5, 40);
    }
}

void drawSpectrum() {
    int barWidth = SCREEN_WIDTH / NUM_BARS;  // Ancho de cada barra

    for (int i = 0; i < NUM_BARS; i++) {
        int x = i * barWidth;
        int height = spectrum[i];

        // Dibujar la barra rellena
        display.fillRect(x, SCREEN_HEIGHT - height, barWidth - 2, height, SSD1306_WHITE);

        // Variar la altura suavemente para simular cambios de frecuencia
        spectrum[i] = random(10, 50);
    }
}

void loop() {
    display.clearDisplay();
    
    drawSpectrum();  // Dibujar el espectro animado

    display.display();
    delay(50);  // Velocidad de actualización rápida
}
