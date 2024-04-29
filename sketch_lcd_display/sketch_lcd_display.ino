#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
String Delimiter = ",";
/*
byte zero[8] = {0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b10000};
byte one[8] = {0b10000,0b10000,0b10000,0b10000,0b10000,0b10000,0b10000,0b10000};
byte two[8] = {0b11000,0b11000,0b11000,0b11000,0b11000,0b11000,0b11000,0b11000};
byte three[8] = {0b11100,0b11100,0b11100,0b11100,0b11100,0b11100,0b11100,0b11100};
byte four[8] = {0b11110,0b11110,0b11110,0b11110,0b11110,0b11110,0b11110,0b11110};
byte five[8] = {0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111};
*/
//byte ten[8] = {0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b00000};
byte eleven[8] = {0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b11111};
byte twelve[8] = {0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b11111,0b11111};
byte thirteen[8] = {0b00000,0b00000,0b00000,0b00000,0b00000,0b11111,0b11111,0b11111};
byte fourteen[8] = {0b00000,0b00000,0b00000,0b00000,0b11111,0b11111,0b11111,0b11111};

byte fifteen[8] = {0b00000,0b00000,0b00000,0b11111,0b11111,0b11111,0b11111,0b11111};
byte sixteen[8] = {0b00000,0b00000,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111};
byte seventeen[8] = {0b00000,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111};
byte eighteen[8] = {0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111};


void setup() {
  if (! i2CAddrTest(0x27)) {
    lcd = LiquidCrystal_I2C(0x3F, 16, 2);
  }

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  /*
  lcd.createChar(0, zero);
  lcd.createChar(1, one);
  lcd.createChar(2, two);
  lcd.createChar(3, three);
  lcd.createChar(4, four);
  lcd.createChar(5, five);
  */
  //lcd.createChar(0, ten);
  lcd.createChar(1, eleven);
  lcd.createChar(2, twelve);
  lcd.createChar(3, thirteen);
  lcd.createChar(4, fourteen);
  lcd.createChar(5, fifteen);
  lcd.createChar(6, sixteen);
  lcd.createChar(7, seventeen);
  lcd.createChar(8, eighteen);
}

void loop() {
  if (Serial.available()) {
    //alternating();
    displayCores();
  }
}

void displayCores() {
  String command = Serial.readStringUntil('\n');
  command.trim();
  float usage[] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
  String percentage;
  int index = 0;
  for (int i = 0; i < command.length(); i++) {
    if (command[i] == ',') {
      if (percentage != "") {
        usage[index] = percentage.toFloat();
        lcd.setCursor(index, 0);
        //lcd.print(10 + 8 * int(usage[index] / 100));
        lcd.print(int(usage[index] * 8 / 100));
        lcd.setCursor(index, 1);
        displayPercentage(int(usage[index] * 8 / 100));
      }
      percentage = "";
      index++;
    } else {
      percentage = percentage + command[i];
    }
  }
}

void displayPercentage(int p) {
  if (p == 0) {
    lcd.print(" ");
  }
  lcd.write(p);
}

void alternating() {
    displayCPU();
    delay(1000);
    displayRAM();
    delay(1000);
}

void displayCPU() {
    String command = Serial.readStringUntil('\n');
    command.trim();
    int index = command.indexOf(Delimiter);
    float cpu = command.substring(0, index).toFloat();
    float memory = command.substring(index + 1, command.length()).toFloat();
    
    lcd.setCursor(0, 0);
    lcd.print("CPU%:");
    lcd.print(cpu);
    //lcd.setCursor(0, 0);
    //lcd.print("Mem%:");
    //lcd.print(memory);

    displayBar(1, cpu);
    //displayBar(1, memory);
}

void displayRAM() {
    String command = Serial.readStringUntil('\n');
    command.trim();
    int index = command.indexOf(Delimiter);
    float cpu = command.substring(0, index).toFloat();
    float memory = command.substring(index + 1, command.length()).toFloat();
    
    //lcd.setCursor(0, 0);
    //lcd.print("CPU%:");
    //lcd.print(cpu);
    lcd.setCursor(0, 0);
    lcd.print("Mem%:");
    lcd.print(memory);

    //displayBar(1, cpu);
    displayBar(1, memory);
}

void displayBar(int row, float value) {
  int bar_count = 80 * (value / 100); //80 = 16 * 5
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, row);
    if (bar_count > 5) {
      lcd.write(5);
      bar_count -= 5;
    } else if (bar_count > 0) {
      lcd.write(bar_count);
      bar_count = 0;
    } else {
      lcd.write(0);
    }
  }
}

bool i2CAddrTest(uint8_t addr) {
  Wire.begin();
  Wire.beginTransmission(addr);

  if (Wire.endTransmission() == 0) {
    return true;
  }

  return false;
}
