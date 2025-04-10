#define DHTTYPE DHT11
#define trigPin 6
#define echoPin 7
#define greenLED 10
#define redLED 11
#define servoPin 9

DHT dht(DHTPIN, DHTTYPE);
Servo doorServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  doorServo.attach(servoPin);
  dht.begin();
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smart Door Ready");
  delay(2000);
  lcd.clear();
  closeDoor();
}

void loop() {
  float distance = getDistance();
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  lcd.setCursor(0, 0);
  lcd.print("Temp: "); lcd.print(temperature); lcd.print("C ");
  lcd.setCursor(0, 1);
  lcd.print("Hum: "); lcd.print(humidity); lcd.print("% ");

  if (distance < 20) {
    openDoor();
    lcd.setCursor(10, 1);
    lcd.print("Open");
  } else {
    closeDoor();
    lcd.setCursor(10, 1);
    lcd.print("Closed");
  }

  delay(1000);
}

float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
  return distance;
}

void openDoor() {
  doorServo.write(90);
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);
}

void closeDoor() {
  doorServo.write(0);
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, HIGH);
}
