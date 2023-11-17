// By ElectroVilla YT :- www.youtube.com/@ElectroVilla
// Code made by Gaurav.

//starting of code.....

//defining all digital pins with the name for the relays as integer
const int relay1 = 2;  //D2
const int relay2 = 3;  //D3
const int relay3 = 4;  //D4
const int relay4 = 5;  //D5
const int relay5 = 6;  //D6
// const int relay6 = 7; //D7
// const int relay7 = 8;  //D8         //uncomment these pins if required..........
// const int relay8 = 9;  //D9
// const int relay9 = 10; //D10


int num_of_relays = 5;  // max no. of relay in the above array (as required)

int relay_out[]{
  // total 9 relays are declared in the circuit but you can change them here:- (I'm using 5 of them)
  relay1,
  relay2,
  relay3,
  relay4,
  relay5,
  // relay6,
  // relay7,           // Uncomment these if required
  // relay8,
  // relay9,
};

// turn all relay ON
void all_relay_OFF() {
  for (int i = 0; i < num_of_relays; i++) {
    digitalWrite(relay_out[i], 0);
  }
}

//turn all relay off
void all_relay_ON() {
  for (int i = 0; i < num_of_relays; i++) {
    digitalWrite(relay_out[i], 1);
  }
}

void setup() {
  //defining all digital pins defined above as ouput
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  // pinMode(relay6, OUTPUT);
  // pinMode(relay7, OUTPUT);   //Un-comment as required........
  // pinMode(relay8, OUTPUT);
  // pinMode(relay9, OUTPUT);

  // turn ON all relay for 5 sec at boot then turn off for 2 sec before excecuting the loop.
  all_relay_ON();
  delay(5000);
  all_relay_OFF();
  delay(2000);
}

//Flash
void flash() {
  int flash_period = 500;
  all_relay_ON();
  delay(flash_period);
  all_relay_OFF();
  delay(flash_period);
}

const int period = 150;  // change speed of the pattern in ms (min 80 for proper relay switching)

//Pattern 1 Right To Left Fill Then Left To Right
void pattern1() {
  for (int i = 0; i < num_of_relays; i++) {
    digitalWrite(relay_out[i], 1);
    delay(period);
  }
  delay(250);
  for (int i = num_of_relays; i > 0; i--) {
    digitalWrite(relay_out[i - 1], 0);
    delay(period);
  }
}
void rev_pattern1() {
  delay(250);
  for (int i = num_of_relays; i > 0; i--) {
    digitalWrite(relay_out[i - 1], 1);
    delay(period);
  }
  delay(250);
  for (int i = 0; i < num_of_relays; i++) {
    digitalWrite(relay_out[i], 0);
    delay(period);
  }
}

//Move Right to Left & then Reverse
void pattern2() {
  delay(250);
  for (int i = 0; i < num_of_relays; i++) {
    digitalWrite(relay_out[i], 1);
    delay(period);
    digitalWrite(relay_out[i], 0);
  }
}
void rev_pattern2() {
  delay(250);
  for (int i = num_of_relays; i > 0; i--) {
    digitalWrite(relay_out[i - 1], 1);
    delay(period);
    digitalWrite(relay_out[i - 1], 0);
  }
}

void loop() {
  //all patterns running in loop
  for (int i = 0; i < num_of_relays; i++) { flash(); }
  for (int i = 0; i < num_of_relays; i++) { pattern1(); }
  for (int i = 0; i < num_of_relays; i++) { rev_pattern1(); }
  for (int i = 0; i < num_of_relays; i++) { pattern2(); }
  for (int i = 0; i < num_of_relays; i++) { rev_pattern2(); }
  delay(250);
}
