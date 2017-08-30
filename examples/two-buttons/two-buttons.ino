#include <FastInputs.h>

enum MyPins {
	Button_A = 5,
	Button_B = 6,
	Led = 13,
};

FastInputs<Button_A,Button_B> inputs;

void setup() {
	// no resistors needed because internal pullups are awesome
	pinMode(Button_A, INPUT_PULLUP);
	pinMode(Button_B, INPUT_PULLUP);
}

bool led_state = LOW;

void loop() {
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
