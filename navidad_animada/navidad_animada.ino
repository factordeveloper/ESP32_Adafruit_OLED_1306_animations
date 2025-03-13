#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Configuración de la onda de sonido
#define NUM_BARS 16  // Número de barras de la onda
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
        wave[i] = random(10, 40);
    }
}

void drawWave() {
    int barWidth = SCREEN_WIDTH / NUM_BARS; // Ancho de cada barra de onda

    for (int i = 0; i < NUM_BARS; i++) {
        int x = i * barWidth;
        int height = wave[i];

        // Dibujar la barra de la onda
        display.drawLine(x, SCREEN_HEIGHT / 2 - height / 2, x, SCREEN_HEIGHT / 2 + height / 2, SSD1306_WHITE);
        
        // Variar la altura de la onda para la animación
        wave[i] = random(10, 40);
    }
}

void loop() {
    display.clearDisplay();
    
    drawWave();  // Dibujar la onda de sonido animada

    display.display();
    delay(100);  // Control de la velocidad de la animación
}
