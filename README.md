# 🌈 TCS3200 Color Recognition System (Arduino-based)

Dự án này triển khai một hệ thống nhận diện và phân loại màu sắc thời gian thực sử dụng cảm biến **TCS3200** và hiển thị kết quả lên màn hình **LCD 16x2 (I2C)**.

## 🚀 Tính năng nổi bật
- **RGB Processing:** Chuyển đổi tần số thô từ cảm biến sang không gian màu RGB (0-255).
- **Auto-Scaling:** Cấu hình tỉ lệ tần số đầu ra 20% (S0-HIGH, S1-LOW) để tối ưu hóa độ chính xác cho vi điều khiển 8-bit.
- **Smart Classification:** Thuật toán phân loại logic giúp nhận diện chính xác các màu cơ bản: Đỏ, Xanh lá, Xanh dương, Trắng, Đen và Vàng.
- **I2C Integration:** Tối ưu hóa số lượng chân kết nối bằng giao thức I2C cho màn hình hiển thị.

## 🛠️ Linh kiện sử dụng
- **MCU:** Arduino Uno/Nano.
- **Sensor:** TCS3200 (Color Sensor).
- **Display:** LCD 16x2 với Module I2C (PCFs8574).

## 📌 Sơ đồ kết nối (Pinout)
| TCS3200 | Arduino | Chức năng |
| :--- | :--- | :--- |
| S0, S1 | D4, D5 | Thiết lập dải tần số (Scaling) |
| S2, S3 | D6, D7 | Lựa chọn bộ lọc màu (Filter) |
| Out | D8 | Đọc tần số đầu ra |
| SDA, SCL | A4, A5 | Giao tiếp I2C cho LCD |

## ⚙️ Thuật toán xử lý
Hệ thống hoạt động dựa trên việc quét tuần tự các bộ lọc màu thông qua chân điều khiển **S2 & S3**, sau đó sử dụng hàm `pulseIn()` để đo độ dài xung. Dữ liệu thô được chuẩn hóa (Map) dựa trên các giá trị hiệu chuẩn (Calibration) để đạt được độ chính xác cao nhất trong môi trường ánh sáng cố định.

```cpp
// Ví dụ logic chọn bộ lọc màu Đỏ trong code
digitalWrite(S2, LOW);
digitalWrite(S3, LOW);
redFrequency = pulseIn(sensorOut, LOW);
redColor = map(redFrequency, R_MIN, R_MAX, 255, 0);
```
