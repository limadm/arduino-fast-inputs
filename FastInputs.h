/*
 * Fast Debounced Inputs for Arduino
 * MIT license © 2017 Daniel M. Lima
 */

template<int N>
class FastInputs {
  long t;
  byte pin[21];
  byte debuf[N];
  byte sampl[N];
  bool state[N];
public:
  FastInputs(byte inputs[N]):
    pin(),
    debuf(),
    sampl(),
    state()
  {
    for (byte i=0; i<sizeof(pin); i++) pin[i] = 255;
    for (byte i=0; i<N; i++) pin[inputs[i]] = i;
  }
  ~FastInputs() {}
  // update input buffers
  void operator()(void) {
    for (byte i=0; i<sizeof(pin); i++) {
      byte p = pin[i];
      if (p != 255) {
        debuf[p] = (debuf[p]/2) + (digitalRead(p) ? 0 : 128);
        state[p] = debuf[p]>254 ? 1 : debuf[p]==1 ? 0 : state[p];
        sampl[p] = sampl[p]<<1 | state[p];
      }
    }
  }
  // returns true if button is down
  // (i.e. when input is pulled DOWN)
  bool operator[](byte p) const {
    return state[pin[p]];
  }
  // returns true if button has changed with given edge
  // defaults to falling edge (button has just been pressed)
  bool operator()(byte p, bool edge=true) const {
    return sampl[pin[p]] == (edge ? 0xF0 : 0x0F);
  }
};
