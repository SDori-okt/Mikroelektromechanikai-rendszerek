# Dokumentáció
## Felhasznált szenzorok és bekötésük

### Hőmérséklet és páratartalom mérése

A DHT-22 (alternatív néven: AM2302) pára- és hőmérsékletszenzor ideális ökoház, humán-környezet, melegház/speciális környezet monitorozásra, így az általam tervezett okosotthon számára is ideális válaszásnak tűnt.

Funkciók:
- 1 másodperc válaszidő
- max. 100 méter vezetékhossz
- működési feszültségtartomány: 3.3-5.5V
- mérési pontosság: 0.1°C, 0.1RH%
- csatlakoztatása külső alkatrészt nem igényel

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

