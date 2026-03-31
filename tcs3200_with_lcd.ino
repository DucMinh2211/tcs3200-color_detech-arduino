#include <LiquidCrystal_I2C.h> // Thêm thư viện I2C
#include <vector>

// TCS3200 pins wiring to Arduino
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Khai báo màn hình LCD 16x2: (Địa chỉ I2C, Cột, Hàng)
// Địa chỉ I2C thường là 0x27 hoặc 0x3F.
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

// Stores the red. green and blue colors
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

// Các giá trị Min/Max hiệu chuẩn của bạn:
const int R_MIN = 117;
const int R_MAX = 578;
const int G_MIN = 120;
const int G_MAX = 530;
const int B_MIN = 40;
const int B_MAX = 160;


void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  // Begins serial communication
  Serial.begin(9600); // begin at port 9600
  
  // Khởi tạo LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("RED GRE BLU Color");
}

void loop() {
  // --- Đo và Xử lý giá trị màu ---
  
  // RED
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  redFrequency = pulseIn(sensorOut, LOW);
  redColor = map(redFrequency, R_MIN, R_MAX, 255,0);
  redColor = constrain(redColor, 0, 255); // Giới hạn giá trị

  // GREEN
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);
  greenColor = map(greenFrequency, G_MIN, G_MAX, 255, 0);
  greenColor = constrain(greenColor, 0, 255); // Giới hạn giá trị

  // BLUE
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);
  blueColor = map(blueFrequency, B_MIN, B_MAX, 255, 0);
  blueColor = constrain(blueColor, 0, 255); // Giới hạn giá trị

  
  // --- SERIAL MONITOR OUTPUT  ---
  Serial.print(blueColor);    // Giá trị BLUR
  Serial.print("\t");        // Dùng Tab để phân tách
  Serial.print(redColor);  // Giá trị RED
  Serial.print("\t");
  Serial.println(greenColor); // Giá trị GREEN và xuống dòng
  
  // --- HIỂN THỊ LÊN LCD ---
  lcd.setCursor(0, 1); // Về đầu hàng 1
  
  // In giá trị R (cột 0)
  lcd.print(redColor);
  lcd.print("  ");
  
  // In giá trị G (cột 4)
  lcd.setCursor(4, 1);
  lcd.print(greenColor);
  lcd.print("  ");
  
  // In giá trị B (cột 8)
  lcd.setCursor(8, 1);
  lcd.print(blueColor);
  lcd.print("  ");
  
  // In Tên Màu (Hàng 1, Cột 13)
  lcd.setCursor(12, 1); 
  
  if (redColor < 25 && greenColor < 25 && blueColor < 25) {
    lcd.print("BLACK");
  } else if(blueColor >= 225 && redColor >= 225 && greenColor >= 225) {
    lcd.print("WHITE");
    // Serial.println("- WHITE detected");
  } else if (greenColor >= 225 && redColor >= 225 && blueColor <= 100) {
    lcd.print("YELLOW");
    // Serial.println("- YELLOW detected");
  } else if(redColor > greenColor && redColor > blueColor){
    lcd.print("RED    "); // Dùng 4 ký tự để xóa phần còn lại
    // Serial.println(" - RED detected!");
  } else if(greenColor > redColor && greenColor > blueColor){
    lcd.print("GREEN"); 
    // Serial.println(" - GREEN detected!");
  } else if(blueColor > redColor && blueColor > greenColor){
    lcd.print("BLUE");
    // Serial.println(" - BLUE detected!");
  } else {
    lcd.print("----    "); // Màu trung tính/khác
    // Serial.println(" - OTHER detected!");
  }
  
  delay(1000); // LCD output delay
}