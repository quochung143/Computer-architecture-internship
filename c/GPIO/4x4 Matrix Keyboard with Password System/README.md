MÔ TẢ:
Xây dựng hệ thống bảo mật sử dụng bàn phím ma trận 4x4. Người dùng phải nhập đúng mật khẩu 6 chữ số để mở khóa. Hệ thống có cơ chế chống brute-force.
YÊU CẦU CHI TIẾT:
Phần cứng:

P0: Bàn phím ma trận 4x4 (P0.0-P0.3: hàng, P0.4-P0.7: cột)

  1  2  3  A
  4  5  6  B
  7  8  9  C
  *  0  #  D

P1.0: LED xanh (mật khẩu đúng)
P1.1: LED đỏ (mật khẩu sai)
P1.2: LED vàng (đang nhập)
P2.0: Buzzer cảnh báo
P2.1-P2.3: LED 7 đoạn hiển thị số lần sai

Chức năng:

Mật khẩu mặc định: 123456
Nhập mật khẩu:

Nhấn phím → LED vàng nhấp nháy
Hiển thị dấu * cho mỗi ký tự đã nhập
Nhấn # để xác nhận
Nhấn * để xóa ký tự cuối


Xác thực:

Đúng: LED xanh sáng 3s, buzzer kêu 2 tiếng ngắn
Sai: LED đỏ sáng 1s, buzzer kêu 1 tiếng dài, tăng số lần sai


Khóa hệ thống:

Sau 3 lần nhập sai → Khóa 30 giây
LED đỏ nhấp nháy, buzzer kêu liên tục
Đếm ngược thời gian khóa


Chức năng nâng cao:

Nhấn A+1234: Đổi mật khẩu mới
Nhấn B+123456: Reset về mặc định
Nhấn C: Xem số lần nhập sai



Kỹ thuật yêu cầu:

Quét bàn phím theo hàng
Debounce 20ms
Lưu mật khẩu trong RAM
Timeout 30s nếu không nhập gì

OUTPUT MẪU:
=== HỆ THỐNG BẢO MẬT ===
Nhập mật khẩu (6 chữ số):

[Người dùng nhấn: 1-2-3-4-5-6-#]
Màn hình: * * * * * *
LED vàng: Nhấp nháy

→ Kết quả: MẬT KHẨU ĐÚNG ✓
   LED xanh: Sáng 3s
   Buzzer: Beep-Beep
   Trạng thái: MỞ KHÓA

---

[Người dùng nhấn: 1-1-1-1-1-1-#]
Màn hình: * * * * * *
→ Kết quả: SAI! Còn 2 lần thử
   LED đỏ: Sáng 1s
   Buzzer: Beeeeep
   Số lần sai: 1

[Nhấn sai lần 2: 9-9-9-9-9-9-#]
→ Kết quả: SAI! Còn 1 lần thử
   Số lần sai: 2

[Nhấn sai lần 3: 0-0-0-0-0-0-#]
→ Kết quả: HỆ THỐNG BỊ KHÓA!
   LED đỏ: Nhấp nháy nhanh
   Buzzer: Kêu liên tục
   Thời gian khóa: 30s
   
   Đếm ngược: 30...29...28...

[Sau 30s]
→ Hệ thống mở khóa
   Số lần sai: Reset về 0