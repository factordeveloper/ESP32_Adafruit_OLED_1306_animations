#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Número de estrellas
#define NUM_STARS 25
int starsX[NUM_STARS];
int starsY[NUM_STARS];

// Variables para la nave espacial 🚀
int spaceshipX = 10;
int spaceshipDirection = 2; // Velocidad de movimiento

// Variables para el planeta 🪐
int planetX = 90;
int planetY = 20;
bool rotatePlanet = true;

// Disparos 🔫
#define MAX_BULLETS 3
struct Bullet {
    int x;
    int y;
    bool active;
};
Bullet bullets[MAX_BULLETS]; // Arreglo de balas
unsigned long lastShotTime = 0;
const int fireRate = 2000; // Disparo cada 2 segundos

void setup() {
    Serial.begin(115200);

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
        Serial.println(F("Error al iniciar pantalla OLED"));
        for (;;);
    }

    display.clearDisplay();

    // Inicializar estrellas en posiciones aleatorias
    for (int i = 0; i < NUM_STARS; i++) {
        starsX[i] = random(0, SCREEN_WIDTH);
        starsY[i] = random(0, SCREEN_HEIGHT / 2);  // Solo en la parte superior
    }

    // Inicializar balas
    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].active = false;
    }
}

// Dibujar estrellas parpadeantes
void drawStars() {
    for (int i = 0; i < NUM_STARS; i++) {
        display.drawPixel(starsX[i], starsY[i], SSD1306_WHITE);
        if (random(0, 10) > 7) { // Aleatorio para parpadeo
            starsX[i] = random(0, SCREEN_WIDTH);
            starsY[i] = random(0, SCREEN_HEIGHT / 2);
        }
    }
}

// Dibujar el planeta con un efecto de rotación 🪐
void drawPlanet() {
    display.fillCircle(planetX, planetY, 8, SSD1306_WHITE);  // Planeta
    if (rotatePlanet) {
        display.drawPixel(planetX - 3, planetY - 2, SSD1306_BLACK); // Sombra simulada
    } else {
        display.drawPixel(planetX + 3, planetY + 2, SSD1306_BLACK);
    }
    rotatePlanet = !rotatePlanet; // Alternar rotación
}

// Dibujar la nave espacial 🚀
void drawSpaceship() {
    display.fillTriangle(spaceshipX, 50, spaceshipX + 10, 55, spaceshipX - 10, 55, SSD1306_WHITE); // Cuerpo
    display.fillRect(spaceshipX - 2, 55, 4, 5, SSD1306_WHITE); // Motor

    // Animación de propulsión
    if (random(0, 2) == 1) {
        display.drawPixel(spaceshipX, 60, SSD1306_WHITE);
    }
}

// Mover la nave de lado a lado más rápido
void updateSpaceship() {
    spaceshipX += spaceshipDirection;
    if (spaceshipX > SCREEN_WIDTH - 10 || spaceshipX < 10) {
        spaceshipDirection = -spaceshipDirection; // Cambiar dirección
    }
}

// Disparar balas cada 2 segundos 🔫
void fireBullet() {
    unsigned long currentTime = millis();
    if (currentTime - lastShotTime >= fireRate) {
        lastShotTime = currentTime;

        // Buscar una bala inactiva y activarla
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (!bullets[i].active) {
                bullets[i].x = spaceshipX;
                bullets[i].y = 50; // Justo encima de la nave
                bullets[i].active = true;
                break;
            }
        }
    }
}

// Dibujar y mover balas
void updateBullets() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            display.drawPixel(bullets[i].x, bullets[i].y, SSD1306_WHITE);
            bullets[i].y -= 2; // Movimiento hacia arriba

            // Desactivar si sale de la pantalla
            if (bullets[i].y < 0) {
                bullets[i].active = false;
            }
        }
    }
}

void loop() {
    display.clearDisplay();

    drawStars();       // Estrellas parpadeantes ✨
    drawPlanet();      // Planeta con rotación 🪐
    drawSpaceship();   // Nave espacial 🚀
    updateSpaceship(); // Movimiento de la nave
    fireBullet();      // Disparar balas cada 2 segundos 🔫
    updateBullets();   // Animación de los disparos 🚀🔫

    display.display();
    delay(50);  // Animación más fluida
}
