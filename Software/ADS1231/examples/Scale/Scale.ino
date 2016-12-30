#include <ADS1231.h>

ADS1231 ads1231(2, 3, 4, 5);

double divisor = 0;
double offset = 0;
long val;

void setup()
{
    // Initialize led
    pinMode(13, OUTPUT);
    // Initialize serial
    Serial.begin(9600);

    // Initialize ADS1231
    ads1231.begin(false, true);

    // Start calibration process (Using 0 and 500g weight)
    calibrate(0, 500);
}

void loop()
{
    ads1231.read(val);
    Serial.print(val / divisor + offset);
    Serial.println("g");
    delay(200);
}

void calibrate(double weight1, double weight2)
{
    Serial.println("Initiating calibration, make sure the scale is empty...");
    long rawValue1 = 0, rawValue2 = 0;

    // Put on first weight
    // Wait 3 seconds to let the user clear the scale
    Serial.println("Stabilizing scale...");
    delay(3000);

    ads1231.read(val);
    rawValue1 = val;

    Serial.println("First step of calibration complete, please put on the "
                   "second weight...");

    // Put on second weight
    while (rawValue1 + 8000 > val) {
        // Wait for new weight
        ads1231.read(val);
        delay(10);
    }

    Serial.println("Stabilizing scale...");
    // Wait 3 seconds to let the scale stablize
    delay(3000);

    Serial.println("Initiating final step of the calibration process...");

    ads1231.read(val);
    rawValue2 = val;

    // Calculate and set the divisor
    divisor = (rawValue1 - rawValue2) / (weight1 - weight2);
    offset = weight1 - (rawValue1 * (weight1 - weight2)) / (rawValue1 - rawValue2);

    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(200);
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);

    Serial.println("Calibration complete...");
}
