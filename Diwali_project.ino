// Code made by Gaurav@Electrovilla.

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


const unsigned int num_of_relays = 5;  // max no. of relay(as required)
unsigned int* relay_Out;


// turn all relay ON
void All_Relay_OFF() {
  for (int i = 0; i < num_of_relays; i++) {
    digitalWrite(relay_Out[i], 0);
  }
}

//turn all relay off
void All_Relay_ON() {
  for (int i = 0; i < num_of_relays; i++) {
    digitalWrite(relay_Out[i], 1);
  }
}

void setup() {

  relay_Out = new unsigned int[num_of_relays];
  // Initialize relay_out array with specific relay values
  // total 9 relays are connected in the circuit but you can change them here:- (I'm using 5 of them)
  relay_Out[0] = relay1;
  relay_Out[1] = relay2;
  relay_Out[2] = relay3;
  relay_Out[3] = relay4;
  relay_Out[4] = relay5;
  // relay_Out[5] = relay6; // Uncomment and add more relays if needed
  // relay_Out[6] = relay7;
  // relay_Out[7] = relay8;
  // relay_Out[8] = relay9;

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
  All_Relay_ON();
  delay(5000);
  All_Relay_OFF();
  delay(2000);
}

const unsigned int period = 100;  // change speed of the pattern in ms (min 90 for proper relay switching)

// Pattern1 - Right To Left Fill Then Left To Right
int Count_Pattern1 = 0;
void Pattern1() {
  delay(250);
  for (int i = 0; i < num_of_relays; i++) {
    digitalWrite(relay_Out[i], 1);
    delay(period);
  }
  delay(250);
  for (int i = num_of_relays; i > 0; i--) {
    digitalWrite(relay_Out[i - 1], 0);
    delay(period);
  }
  if (Count_Pattern1 >= 4) {
    for (int i = 0; i < num_of_relays; i++) {
      delay(250);
      Rev_Pattern1();
    }
  }
  ++Count_Pattern1;
}
void Rev_Pattern1() {
  for (int i = num_of_relays; i > 0; i--) {
    digitalWrite(relay_Out[i - 1], 1);
    delay(period);
  }
  delay(250);
  for (int i = 0; i < num_of_relays; i++) {
    digitalWrite(relay_Out[i], 0);
    delay(period);
  }
  Count_Pattern1 = 0;
}

//Pattern2 - Move Right to Left & then Reverse
int Count_Pattern2 = 0;
void Pattern2() {
  delay(250);
  for (int i = 0; i < num_of_relays; i++) {
    digitalWrite(relay_Out[i], 1);
    delay(period);
    digitalWrite(relay_Out[i], 0);
  }
  if (Count_Pattern2 >= 4) {
    for (int i = 0; i < num_of_relays; i++) {
      delay(250);
      Rev_Pattern2();
    }
  }
  ++Count_Pattern2;
}
void Rev_Pattern2() {
  for (int i = num_of_relays; i > 0; i--) {
    digitalWrite(relay_Out[i - 1], 1);
    delay(period);
    digitalWrite(relay_Out[i - 1], 0);
  }
  Count_Pattern2 = 0;
}

//Pattern3 - Create wave pattern from center and reverse!
unsigned int wave_period = 150;
void Pattern3() {
  delay(200);
  digitalWrite(relay_Out[2], 1);
  for (int i = 2, j = 2; i < num_of_relays && j >= 0; i++, j--) {
    if (i == 2 && j == 2) {
      continue;
    } else {
      digitalWrite(relay_Out[i], 1);
      digitalWrite(relay_Out[j], 1);
      delay(wave_period);
      if (i == 4 && j == 0) {
        delay(200);
        Rev_Pattern3();
      }
    }
  }
}

void Rev_Pattern3() {
  digitalWrite(relay_Out[2], 1);
  for (int i = 2, j = 2; i < num_of_relays && j >= 0; i++, j--) {
    if (i == 2 && j == 2) {
      continue;
    } else {
      digitalWrite(relay_Out[i], 0);
      digitalWrite(relay_Out[j], 0);
      delay(wave_period);
    }
  }
}

//Flash
void Flash() {
  delay(250);
  const int min_period = 90;  // should not be less then 90!
  const int max_period = 360;
  for (int i = max_period; i >= min_period; i -= 10) {
    int flash_period = i;
    All_Relay_ON();
    delay(flash_period);
    All_Relay_OFF();
    delay(flash_period);
  }
  delay(250);
}

void loop() {
  //all patterns running in loop:-
  for (int i = 0; i < num_of_relays; i++) { Pattern1(); }
  for (int i = 0; i < num_of_relays; i++) { Pattern2(); }
  for (int i = 0; i < num_of_relays; i++) { Pattern3(); }
  for (int i = 0; i < 1; i++) { Flash(); }
  delay(250);
}
