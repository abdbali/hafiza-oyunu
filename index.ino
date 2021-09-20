#include <Tone.h>
Tone speakerpin;
int starttune[] = {NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_C4, 
NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_G4};
int duration2[] = {100, 200, 100, 200, 100, 400, 100, 100, 100, 100, 200, 100, 500};
int note[] = {NOTE_C4, NOTE_C4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_C5};
int duration[] = {100, 100, 100, 300, 100, 300};
int button[] = {2, 3, 4, 5}; //4 buton pinleri
int ledpin[] = {8, 9, 10, 11}; // LED pinleri
int turn = 0; // dönüş sayacı
int buttonstate = 0; // buton durumu değişkeni
int randomArray[100]; //rstgele yanacak led dizisi 
int inputArray[100]; //kullanıcının yaktığı led dizisi
void setup() 
{
 Serial.begin(9600);
 speakerpin.begin(12); // buzzer 12.pine tanımlandı
 for(int x=0; x<4; x++) // LED pinleri çıkış olarak ayarlandı
 {
 pinMode(ledpin[x], OUTPUT);
 }
 
 for(int x=0; x<4; x++) 
 {
 pinMode(button[x], INPUT); // buton pinleri giriş olarak ayarlandı
 digitalWrite(button[x], HIGH); // pullup dirençleri için butonlar HIGH yapıldı
 }
 randomSeed(analogRead(0)); //rastgele dizisinde daha fazla rastgele sayı üretmesi için
 for (int thisNote = 0; thisNote < 13; thisNote ++) {
 // buzzer bir sonraki melodiyi çalsın
 speakerpin.play(starttune[thisNote]);
 // notayı saklar(tutar):
 if (thisNote==0 || thisNote==2 || thisNote==4 || thisNote== 6)
 {
// Bu oyunda ledler 
// rastgele yanar, 
// kullanıcı aynı sırada 
// butona basmalıdır. Doğru 
// sırayı bilmişse oyun 
// melodi çalar ve bir üst 
// seviyeye geçer. Yanlış
// yaptığında melodi çalar 
// ve oyun baştan başlar.
 digitalWrite(ledpin[0], HIGH);
 }
 if (thisNote==1 || thisNote==3 || thisNote==5 || thisNote== 7 || thisNote==9 || 
thisNote==11)
 {
 digitalWrite(ledpin[1], HIGH);
 }
 if (thisNote==8 || thisNote==12)
 {
 digitalWrite(ledpin[2], HIGH);
 } 
 if (thisNote==10)
 { 
 digitalWrite(ledpin[3], HIGH);
 }
 delay(duration2[thisNote]);
 // stop for the next note:
 speakerpin.stop();
 digitalWrite(ledpin[0], LOW);
 digitalWrite(ledpin[1], LOW);
 digitalWrite(ledpin[2], LOW);
 digitalWrite(ledpin[3], LOW);
 delay(25);
 }
 delay(1000);
}
void loop() 
{ 
 for (int y=0; y<=99; y++)
 {
 //rastgele dizisini yenilemek için
 digitalWrite(ledpin[0], HIGH);
 digitalWrite(ledpin[1], HIGH);
 digitalWrite(ledpin[2], HIGH);
 digitalWrite(ledpin[3], HIGH);
 
 for (int thisNote = 0; thisNote < 6; thisNote ++) {
 //bir sonraki notayı çal:
 speakerpin.play(note[thisNote]);
 // notayı sakla:
 delay(duration[thisNote]);
 // buzzer ı sustur:
 speakerpin.stop();
 delay(25);
 }
 
 digitalWrite(ledpin[0], LOW);
 digitalWrite(ledpin[1], LOW);
 digitalWrite(ledpin[2], LOW);
 digitalWrite(ledpin[3], LOW);
 delay(1000);
 
 for (int y=turn; y <= turn; y++)
 { //dönüş değişkeni için sabitler
 Serial.println(""); 
 Serial.print("Turn: ");
 Serial.print(y);//kullanıcıya hangi tuşlara basması gerektiğini söyler
 Serial.println("");
 randomArray[y] = random(1, 5); //rastgele dizisine 1-4 arası rastgele sayı atar
 for (int x=0; x <= turn; x++)
 {
 Serial.print(randomArray[x]);
 
 for(int y=0; y<4; y++)
 {
 
 if (randomArray[x] == 1 && ledpin[y] == 8) 
 { 
 digitalWrite(ledpin[y], HIGH);
 speakerpin.play(NOTE_G3, 100);
 delay(400);
 digitalWrite(ledpin[y], LOW);
 delay(100);
 }
 if (randomArray[x] == 2 && ledpin[y] == 9) 
 {
 digitalWrite(ledpin[y], HIGH);
 speakerpin.play(NOTE_A3, 100);
 delay(400);
 digitalWrite(ledpin[y], LOW);
 delay(100);
 }
 
 if (randomArray[x] == 3 && ledpin[y] == 10) 
 {
 digitalWrite(ledpin[y], HIGH);
 speakerpin.play(NOTE_B3, 100);
 delay(400);
 digitalWrite(ledpin[y], LOW);
 delay(100);
 }
 if (randomArray[x] == 4 && ledpin[y] == 11) 
 {
 digitalWrite(ledpin[y], HIGH);
 speakerpin.play(NOTE_C4, 100);
 delay(400);
 digitalWrite(ledpin[y], LOW);
 delay(100);
 }
 }
 }
 }
 input();
 }
}
void input() { //kullanıcıya yeni dizi girmek için izin verir
 for (int x=0; x <= turn;)
 { //x'i dönüş sayısı ile sınırlandırır
 for(int y=0; y<4; y++)
 {
 
 buttonstate = digitalRead(button[y]);
 
 if (buttonstate == HIGH && button[y] == 2)
 { //butona basılıp basılmadığını kontrol eder
 digitalWrite(ledpin[0], HIGH);
 speakerpin.play(NOTE_G3, 100);
 delay(200);
 digitalWrite(ledpin[0], LOW);
 inputArray[x] = 1;
 delay(250);
 Serial.print(" ");
 Serial.print(1);
 if (inputArray[x] != randomArray[x]) { //kullanıcının girdiği dizi(buton sırası) ile rastgele yanan dizi eşit değilse
 fail(); //fail() metodunu çağır
 } 
 x++; //diziler aynıysa x'i artırır (seviyeyi artırır)
 }
 if (buttonstate == HIGH && button[y] == 3)
 {
 digitalWrite(ledpin[1], HIGH);
 speakerpin.play(NOTE_A3, 100);
 delay(200);
 digitalWrite(ledpin[1], LOW);
 inputArray[x] = 2;
 delay(250);
 Serial.print(" ");
 Serial.print(2);
 if (inputArray[x] != randomArray[x]) {
 fail();
 }
 x++;
 }
 if (buttonstate == HIGH && button[y] == 4)
 {
 digitalWrite(ledpin[2], HIGH);
 speakerpin.play(NOTE_B3, 100);
 delay(200);
 digitalWrite(ledpin[2], LOW);
 inputArray[x] = 3;
 delay(250);
 Serial.print(" ");
 Serial.print(3);
 if (inputArray[x] != randomArray[x]) {
 fail();
 }
 x++;
 }
 if (buttonstate == HIGH && button[y] == 5)
 {
 digitalWrite(ledpin[3], HIGH);
 speakerpin.play(NOTE_C4, 100);
 delay(200);
 digitalWrite(ledpin[3], LOW);
 inputArray[x] = 4;
 delay(250);
 Serial.print(" ");
 Serial.print(4);
 if (inputArray[x] != randomArray[x]) 
 {
 fail();
 }
 x++;
 }
 }
 }
 delay(500);
 turn++; //dönüş sayısını artıt
}
void fail() { //kullanıcı yanlış giriş yaptığında çalışacak metot (kodlar)
 for (int y=0; y<=2; y++)
 { //ledler hatayı bildirmek için yanar
 
 digitalWrite(ledpin[0], HIGH);
 digitalWrite(ledpin[1], HIGH);
 digitalWrite(ledpin[2], HIGH);
 digitalWrite(ledpin[3], HIGH);
 speakerpin.play(NOTE_G3, 300);
 delay(200);
 digitalWrite(ledpin[0], LOW);
 digitalWrite(ledpin[1], LOW);
 digitalWrite(ledpin[2], LOW);
 digitalWrite(ledpin[3], LOW);
 speakerpin.play(NOTE_C3, 300); //hata melodisini çal
 delay(200);
 }
 delay(500);
 turn = -1; //oyunu başa döndürür
}