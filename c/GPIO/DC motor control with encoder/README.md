MÔ TẢ:
Điều khiển tốc độ và hướng quay của động cơ DC sử dụng encoder quang học để đo vị trí chính xác. Hệ thống có khả năng điều khiển vị trí theo góc quay.
YÊU CẦU CHI TIẾT:
Phần cứng:

P1.0, P1.1: Điều khiển H-Bridge (Motor driver L298N)

P1.0=1, P1.1=0: Quay thuận
P1.0=0, P1.1=1: Quay ngược
P1.0=0, P1.1=0: Dừng


P1.2: PWM tốc độ (từ Timer 0)
P3.2 (INT0): Encoder Channel A
P3.3 (INT1): Encoder Channel B
P2.0-P2.3: 4 nút điều khiển (Thuận, Ngược, Tăng tốc, Giảm tốc)
P0: LED hiển thị trạng thái

Thông số encoder:

600 xung/vòng (Quadrature: 2400 xung/vòng)
Đọc cả cạnh lên của Channel A và B

Chức năng:

Điều khiển tốc độ:

5 mức tốc độ: 20%, 40%, 60%, 80%, 100%
PWM tần số 1kHz
Nút tăng/giảm để chọn mức


Điều khiển hướng:

Nút Thuận: Quay theo chiều kim đồng hồ
Nút Ngược: Quay ngược chiều kim đồng hồ
Chuyển hướng phải có dừng 200ms


Đo vị trí:

Đếm xung từ encoder
Tính góc quay (độ)
Tính vòng quay (số vòng)


Chế độ tự động (điều khiển vị trí):

Nhập góc mục tiêu (0-360°)
Động cơ tự động quay đến vị trí
Dừng chính xác ±2°
PID control để mượt mà


Hiển thị:

LED hiển thị: Hướng, Tốc độ, Vị trí hiện tại



Kỹ thuật yêu cầu:

Sử dụng INT0, INT1 để đọc encoder
PWM từ Timer 0
Timer 1 cho PID controller (10ms)
Xử lý quadrature encoding

OUTPUT MẪU:
=== ĐỘNG CƠ DC VỚI ENCODER ===

[Chế độ thủ công]
Trạng thái ban đầu:
- Hướng: DỪNG
- Tốc độ: 0%
- Vị trí: 0° (0 vòng)
- Encoder: 0 xung

[Nhấn nút Thuận + Tăng tốc lên 60%]
Trạng thái:
- Hướng: THUẬN ⟳
- Tốc độ: 60% (PWM duty = 153/255)
- Vị trí: 45.5° (0.126 vòng)
- Encoder: 302 xung
- Tốc độ quay: ~120 RPM

[Sau 2 giây]
- Vị trí: 315° (0.875 vòng)
- Encoder: 2100 xung

[Nhấn nút Ngược]
→ Động cơ dừng 200ms
→ Chuyển hướng
- Hướng: NGƯỢC ⟲
- Tốc độ: 60%
- Vị trí: Đếm ngược từ 315°

---

[Chế độ tự động - Điều khiển vị trí]
Mục tiêu: Quay đến 180°
Vị trí hiện tại: 45°

Bắt đầu di chuyển:
t=0ms   : Vị trí = 45°  | Sai số = 135° | Tốc độ = 100%
t=200ms : Vị trí = 89°  | Sai số = 91°  | Tốc độ = 90%
t=400ms : Vị trí = 132° | Sai số = 48°  | Tốc độ = 70%
t=600ms : Vị trí = 165° | Sai số = 15°  | Tốc độ = 40%
t=750ms : Vị trí = 178° | Sai số = 2°   | Tốc độ = 20%
t=820ms : Vị trí = 180° | Sai số = 0°   | DỪNG ✓

Kết quả: ĐẠT VỊ TRÍ MỤC TIÊU
Thời gian: 820ms
Độ chính xác: ±0.5°

---

[Giám sát liên tục]
Thời gian | Hướng  | Tốc độ | Vị trí | RPM | Xung
----------|--------|--------|--------|-----|-------
0.0s      | THUẬN  | 80%    | 0°     | 0   | 0
0.5s      | THUẬN  | 80%    | 67°    | 135 | 448
1.0s      | THUẬN  | 80%    | 134°   | 134 | 897
1.5s      | THUẬN  | 80%    | 201°   | 134 | 1346
2.0s      | THUẬN  | 80%    | 268°   | 134 | 1794
Sơ đồ encoder:
Channel A: ‾|_|‾|_|‾|_|‾
Channel B: _|‾|_|‾|_|‾|_

Quay thuận: A dẫn trước B
Quay ngược: B dẫn trước A