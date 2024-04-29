# A standalone microcontroller based computer resource usage gauge

```
  ________    _____   ____ ___  ___________________
 /  _____/   /  _  \ |    |   \/  _____/\_   _____/
/   \  ___  /  /_\  \|    |   /   \  ___ |    __)_ 
\    \_\  \/    |    \    |  /\    \_\  \|        \
 \______  /\____|__  /______/  \______  /_______  /
        \/         \/                 \/        \/ 
```
This is a usage guage build using arduino UNO (or similar product) + "I2C LCD1602" LCD screen.

## How to use

### Hardware requirement:
  1. arduino UNO or similar
  2. I2C LCD1602
  3. A computer running linux operating system
  4. A USB cable
     
### Software requiremnt:
  1. [Arduino IDE](https://www.arduino.cc/en/software)

### Usage
  0. Connect the arduino UNO board with the computer using a LCD, connect the LCD with arduino board.
     | Arduino UNO    | I2C LCD     |
     | ------- | ---------- |
     |GND      | GND         |
     |POWER 5V | VCC         |
     |A4       | SDA         |
     |A5       | SCL         |
  2. Download this repository. Open the sketch folder from Arduino_IDE.
  3. open a terminal, cd to the root directory of this repo, run the following command
     ```bash hold_open.sh```
  4. open another terminal, cd to the root directory of this repo, run the following command:
     ```bash send.sh```

  After those steps, you should be able to see the cpu usage on the LCD display both as a percentage in the top row and also a bar in the lower row.

