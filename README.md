Fast Debounced Inputs for Arduino
---------------------------------

This library debounces inputs with a digital RC filter with hysteresis
and no time delays, effectively emulating a Schimitt-Trigger gate,
perfect for detection of fast changing sensors in noisy environments.

Example usage:


```arduino
#include <FastInputs.h>

enum MyPins {
	Button_A = 5,
	Button_B = 6,
	Led = 13,
};

const byte my_buttons = { Button_A, Button_B };
FastInputs<sizeof(my_inputs)> inputs = my_buttons;

setup() {
	// no resistors needed because internal pullups are awesome
	pinMode(Button_A, INPUT_PULLUP);
	pinMode(Button_B, INPUT_PULLUP);
}

bool led_state = LOW;

loop() {
	// call inputs() to update input buffers
	inputs();

	// square brackets return true if button is pressed, and stays true while the button is down
	if (inputs[Button_A]) {
		// invert led state while the button is down
		digitalWrite(Led, !led_state);
	}

	// parentheses return true just once at the edge, so you need to click again to generate another event
	if (inputs(Button_B)) {
		// invert led state each time the button is clicked
		led_state = !led_state;
		digitalWrite(Led_B, led_state);
	}
}

```

Have fun!

---

MIT license © 2017 Daniel M. Lima