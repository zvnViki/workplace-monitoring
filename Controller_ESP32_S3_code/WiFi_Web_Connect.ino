/* ================= SETTINGS UI ================= */
void build(sets::Builder& b) {
    {
        sets::Group g(b, "WiFi");
        b.Input(kk::wifi_ssid, "SSID");
        b.Pass(kk::wifi_pass, "Password");
        if (b.Button(kk::apply, "Save & Restart")) {
            db.update();  // сохраняем БД не дожидаясь таймаута
            ESP.restart();
        }
    }
}
