#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
String Delimiter = ",";

void setup() {
  if (! i2CAddrTest(0x27)) {
    lcd = LiquidCrystal_I2C(0x3F, 16, 2);
  }

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    int index = command.indexOf(Delimiter);
    float cpu = command.substring(0, index).toFloat();
    String memory = command.substring(index + 1, command.length());
    lcd.setCursor(0, 0);
    lcd.print("CPU%:");
    lcd.print(cpu);
    lcd.setCursor(0, 1);
    lcd.print("Mem%:");
    lcd.print(memory);
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
