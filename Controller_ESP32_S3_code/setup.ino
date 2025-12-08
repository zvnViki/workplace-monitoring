void setup() {
  Serial.begin(115200);
  // Общая I2C шина проекта
  Wire.begin(SDA_PIN, SCL_PIN);  // SDA=8, SCL=9

  // Проверка SCD-30 на работоспособность
  if (airSensor.begin() == false) {
    while (1) {
      Serial.println("SCD30 не обнаружен. Проверьте подключение!");
      delay(5000);
    }
  }

  airSensor.setMeasurementInterval(2);  // Интервал измерений. Не ставить реже 2 секунд
   delay(2000);
  //---------------------------------------

  // Проверка BME280 на работоспособность
  if (!bme.begin(0x76, &Wire)) {
    while (1) {
      Serial.println("BME280 не обнаружен. Проверьте подключение!");
      delay(5000);
    }
  }
  //---------------------------------------
  
  // Проверка TSL2591 на работоспособность
  if (!tsl.begin()) {
    while (1) {
      Serial.println("TSL2591 не обнаружен. Проверьте подключение!");
      delay(5000);
    }
  }
  //---------------------------------------

  // Проверка DS3231 на работоспособность
  if (!rtc.begin()) {
    while (1) {
      Serial.println("DS3231 не обнаружен. Проверьте подключение!");
      delay(5000);
    }
  }
  // Один раз установи время:
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // Формат: DateTime(год, месяц, день, час, минута, секунда)
  //rtc.adjust(DateTime(2025, 12, 5, 14, 30, 0)); // 5 декабря 2025, 14:30:00
  //---------------------------------------

//Инициализация E-inc дисплея
 while (!Serial);
InitialiseDisplay();
//start_image_E_inc();
}