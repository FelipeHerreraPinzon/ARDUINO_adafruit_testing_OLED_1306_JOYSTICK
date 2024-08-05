#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Configuración de pines del OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C  // Asegúrate de usar la dirección correcta (0x3C o 0x3D)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Configuración del joystick
const int joyYPin = A1;  // Pin analógico del joystick para el eje Y

int textPosition = 0;  // Posición actual del texto
const int textHeight = 8;  // Altura de una línea de texto
const int screenLines = SCREEN_HEIGHT / textHeight;  // Número de líneas visibles en la pantalla

// Texto largo para mostrar
const char* longText[] = {
  "Línea 1: Texto largo para pruebas.",
  "Línea 2: Desplázate con el joystick.",
  "Línea 3: Ajusta el umbral si es necesario.",
  "Línea 4: Verifica la conexión del joystick.",
  "Línea 5: El texto debería moverse arriba y abajo.",
  "Línea 6: Ajusta el tiempo de retraso si es muy rápido.",
  "Línea 7: Prueba el texto en una pantalla real si es posible."
};
const int totalLines = sizeof(longText) / sizeof(longText[0]);

void setup() {
  Serial.begin(115200);
  
  // Inicializar el display OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Detener el programa si la inicialización falla
  }
  
  display.clearDisplay(); // Limpiar pantalla
  display.setTextSize(1); // Tamaño del texto
  display.setTextColor(SSD1306_WHITE); // Color del texto
  display.setCursor(0, 0); // Posición inicial del cursor
  
  // Mostrar un mensaje inicial
  display.println(F("Hola, OLED!"));
  display.display(); // Actualizar el contenido en la pantalla
}

void loop() {
  // Leer valor del joystick
  int joyYValue = analogRead(joyYPin);
  int threshold = 500; // Umbral para detección de movimiento
  
  // Mover el texto basado en la posición del joystick
  if (joyYValue < 1024 - threshold && textPosition < totalLines - screenLines) {
    textPosition++;
    delay(200); // Retraso para evitar movimientos demasiado rápidos
  }
  if (joyYValue > threshold && textPosition > 0) {
    textPosition--;
    delay(200); // Retraso para evitar movimientos demasiado rápidos
  }

  // Limpiar pantalla y mostrar texto
  display.clearDisplay();

  for (int i = 0; i < screenLines; i++) {
    if (textPosition + i < totalLines) {
      display.setCursor(0, i * textHeight);
      display.print(longText[textPosition + i]);
    }
  }

  display.display();
}
