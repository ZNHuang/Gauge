#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  if (! i2CAddrTest(0x27)) {
    lcd = LiquidCrystal_I2C(0x3F, 16, 2);
  }

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  //lcd.print("Hello world!");
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 0);
  if (Serial.available()) {
    auto command = Serial.readStringUntil('\n');
    command.trim();
    lcd.print("CPU%:");
    lcd.print(command);
  }
  lcd.setCursor(0, 1);
  //lcd.print("Counter:");
  //lcd.print(millis() / 1000);
}

bool i2CAddrTest(uint8_t addr) {
  Wire.begin();
  Wire.beginTransmission(addr);

  if (Wire.endTransmission() == 0) {
    return true;
  }

  return false;
}
