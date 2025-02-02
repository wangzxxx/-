#include <LiquidCrystal.h>  // 引入LCD库

// LCD连接引脚
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// 假设考试时间戳是固定的，举例使用一个未来的时间戳
unsigned long examTimestamp = 1749254400;  // 目标时间戳（考试时间）

unsigned long currentTimestamp = 0;  // 当前时间戳

void setup() {
  // 初始化串口通信和LCD
  Serial.begin(9600);
  lcd.begin(16, 2);  // LCD的列数为16，行数为2
  lcd.clear();
  lcd.print("Load time...");
}

void loop() {
  if (Serial.available() > 0) {  // 确保串口有数据可读
    currentTimestamp = Serial.parseInt();  // 读取时间戳
    long remainingTime = examTimestamp - currentTimestamp;  // 剩余时间（秒）

    // 如果剩余时间为负，说明已经超时
    if (remainingTime < 0) {
      lcd.clear();
      lcd.print("Exam Started!");
      return;  // 如果考试已开始，跳出循环
    }

    // 计算天、小时、分钟和秒
    int days = remainingTime / 86400;  // 1天 = 86400秒
    int hours = (remainingTime % 86400) / 3600;  // 1小时 = 3600秒
    int minutes = (remainingTime % 3600) / 60;   // 1分钟 = 60秒
    int seconds = remainingTime % 60;   // 剩余的秒数

    // 在LCD上显示剩余时间
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Remaining:");
    lcd.setCursor(0, 1);
    lcd.print(days);
    lcd.print("d ");
    lcd.print(hours);
    lcd.print("h ");
    lcd.print(minutes);
    lcd.print("m ");
    lcd.print(seconds);
    lcd.print("s");

    Serial.print("Remaining Time: ");
    Serial.print(days);
    Serial.print("d ");
    Serial.print(hours);
    Serial.print("h ");
    Serial.print(minutes);
    Serial.print("m ");
    Serial.print(seconds);
    Serial.println("s");

    delay(1000);  // 延时1秒刷新显示
  }
}
