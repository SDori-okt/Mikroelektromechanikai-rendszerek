# Dokumentáció
## Felhasznált szenzorok és bekötésük

### Hőmérséklet és páratartalom mérése

A DHT-22 (alternatív néven: AM2302) pára- és hőmérsékletszenzor ideális ökoház, humán-környezet, melegház/speciális környezet monitorozásra, így az általam tervezett okosotthon számára is ideális válaszásnak tűnt.

Funkciók:
- 1 másodperc válaszidő
- Max. 100 méter vezetékhossz
- Működési feszültségtartomány: 3.3-5.5V
- Mérési pontosság: 0.1°C, 0.1RH%
- Csatlakoztatása külső alkatrészt nem igényel

Csatlakoztatás az alábbi ábra alapján:

![DHT22](/img/dht22-wiring.png)

### Oled kijelző

Az mért adatok megjelenítésére Oled kijelzőt használtam. Az első adatsorban a mért hőmérséklet, a második adatsorban a mért páratartalom található. Előbbi Celsius fokban, utóbbi százalékban mérve.

Funkciók:
- Felbontás: 128x64
- Teljesítmény: 0.06W
- Tápfeszültség tartomány: DC 3V-5V
- Hőmérséklet: -30 °C és 70 °C
- Méret: 29,28mm x 27,1 mm

Csatlakoztatás az alábbi ábra alapján:

![oled](/img/oled.jpg)

### Ajtónyitás érzékelő

A Reed YB-32NC egy felületre szerelhető reed relés nyitásérzékelő, ideális beléptető rendszerek ajtóállapot visszajelzésére, ezáltal az általam tervezett okosotthon ajtajához is megfelelt. Az eszköz NC módban működik, vagyis bezárt ajtó esetén ad rövidzárat.

Funkciók:
- Mód: NC (mágneses)
- Érzékenység: 15mm
- Méret : 34 × 7,62 × 13,5 mm
- Terhelhetőség: 0.5A / 30 V DC

Bekötés az alábbi ábra alapján:

![ajtonyitas](/img/arduino-door-sensor-wiring-diagram.jpg)

### Mozgásérzékelő

Jó minőségű érzékelő modul, önálló érzékelőként, összhangban az Arduino™ platformmal vagy más rendszerekkel együtt is használható. Az általam választott célhoz pontosan megfelelőnek tűnt. A PIR mozgásérzékelő modulnak 3 darab pinje (GND, OUT, VCC) és két potmétere van, amelyből az egyik az távolság beállítására szolgál, a másik pedig a késleltetés beállítására.

Funkciók:
- Állítható távolság
- Állítható késleltetés 0.3 - 300 mp
- Blokkolási idő: 0.2 másodperc
- Működési feszültség: DC 5V-20V
- Statikus energiafogyasztás: 65 mA
- Szintkimenet: Magas: 3.3 V, Alacsony: 0 V
- Indukciós tartomány: 120°-nál kisebb, kevesebb mint 7 méter magasságú kúp

Bekötés az alábbi ábra alapján:

![mozgaserzekelo](/src/motion.jfif)

