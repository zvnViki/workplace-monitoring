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
  delay(2000);
  airSensor.setMeasurementInterval(30);  // Интервал измерений. Не ставить реже 2 секунд
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
  while (!Serial)
    ;
  InitialiseDisplay();
  //start_image_E_inc();
  //----------------------------

  // Настройки WiFi------------
  WiFi.mode(WIFI_AP_STA);

  sett.begin();
  sett.onBuild(build);

  // базу данных запускаем до подключения к точке
#ifdef ESP32
  LittleFS.begin(true);
#else
  LittleFS.begin();
#endif
  db.begin();
  db.init(kk::wifi_ssid, "");
  db.init(kk::wifi_pass, "");

  // ======= AP =======
  WiFi.softAP("AP ESP","23456789");
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

  // ======= STA =======
  // если логин задан - подключаемся
  if (db[kk::wifi_ssid].length()) {
    WiFi.begin(db[kk::wifi_ssid], db[kk::wifi_pass]);
    Serial.print("Connect STA");
    int tries = 20;
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print('.');
      if (!--tries) break;
    }
    Serial.println();
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  }

  //----------------------------
}
