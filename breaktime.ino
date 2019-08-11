#include <Adafruit_CircuitPlayground.h>

void setup() {
  CircuitPlayground.begin();
}

const unsigned long SEC = 1000;
const unsigned long MIN = 60 * SEC;
const unsigned long N_PIXELS = 10;
const unsigned long BRIGHTNESS = 128;
const unsigned long ALARM_FREQUENCY = 500;

void countdown(unsigned long ms) {
    // init
    unsigned long red = random(BRIGHTNESS - 10) + 10;
    unsigned long green = random(BRIGHTNESS - 10) + 10;
    unsigned long blue = random(BRIGHTNESS - 10) + 10;
    CircuitPlayground.clearPixels();
    unsigned long start_time = millis();
    unsigned long current_time = start_time;
    unsigned long elapsed_time = current_time - start_time;

    // progress
    while(start_time + ms > current_time) {
      unsigned long fully_elapsed = (elapsed_time * N_PIXELS) / ms;
      for(int i = 0; i < fully_elapsed; i++) {
        CircuitPlayground.setPixelColor(i, red, green, blue);
      }

      unsigned long reminder_elapsed = ((elapsed_time * N_PIXELS) % ms);
      CircuitPlayground.setPixelColor(
        fully_elapsed,
        red * reminder_elapsed / ms,
        green * reminder_elapsed / ms,
        blue * reminder_elapsed / ms
      );
      
      delay(10);
      current_time = millis();
      elapsed_time = current_time - start_time;
    }

    // alarm
    unsigned long signal = 0;
    const unsigned long CHECK_FREQUENCY = 10;
    while(true) {
      if(CircuitPlayground.leftButton()) {
        break;
      }

      for(int i = 0; i < N_PIXELS; i++) {
        if(signal / (ALARM_FREQUENCY / CHECK_FREQUENCY) % 2) {
            CircuitPlayground.setPixelColor(i, red, green, blue);
        } else {
            CircuitPlayground.setPixelColor(i, 0, 0, 0);
        }
      }

      delay(CHECK_FREQUENCY);
      signal++;
    }
}

void loop() {
  countdown(45 * MIN);
  countdown(5 * MIN);
}
