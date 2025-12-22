MÔ TẢ:
Thiết kế hệ thống đèn giao thông điều khiển 2 ngã tư giao nhau. Mỗi ngã tư có 3 đèn LED (Đỏ, Vàng, Xanh) và hoạt động luân phiên. Hệ thống có chế độ khẩn cấp khi có xe ưu tiên.
YÊU CẦU CHI TIẾT:
Phần cứng:

P1.0, P1.1, P1.2: Đèn Đỏ, Vàng, Xanh cho Ngã tư A
P1.3, P1.4, P1.5: Đèn Đỏ, Vàng, Xanh cho Ngã tư B
P3.2 (INT0): Nút khẩn cấp (xe ưu tiên)
P3.3 (INT1): Nút reset hệ thống

Chức năng:

Chế độ bình thường:

Ngã tư A: Xanh 20s → Vàng 3s → Đỏ 20s
Ngã tư B: Đỏ 20s → Xanh 20s → Vàng 3s
Lặp lại liên tục


Chế độ khẩn cấp (khi nhấn INT0):

Tất cả đèn chuyển sang đỏ ngay lập tức
Nhấp nháy đèn đỏ với tần số 2Hz trong 5 giây
Sau đó quay lại chu kỳ bình thường


Chức năng reset (INT1):

Khởi động lại từ đầu chu kỳ



Kỹ thuật yêu cầu:

Sử dụng Timer 0 tạo độ trễ 1 giây
Debounce cho nút nhấn (20ms)
Sử dụng ngắt ngoài để xử lý khẩn cấp

OUTPUT MẪU:
Thời điểm | Ngã tư A        | Ngã tư B        | Ghi chú
----------|-----------------|-----------------|------------------
0s        | XANH            | ĐỎ              | Bắt đầu chu kỳ
20s       | VÀNG            | ĐỎ              | A chuyển vàng
23s       | ĐỎ              | XANH            | B bắt đầu đi
43s       | ĐỎ              | VÀNG            | B chuyển vàng
46s       | XANH            | ĐỎ              | Lặp lại chu kỳ

[Khi nhấn nút khẩn cấp tại giây 30]
30s       | ĐỎ nhấp nháy    | ĐỎ nhấp nháy    | Chế độ khẩn cấp
35s       | XANH            | ĐỎ              | Tiếp tục từ đầu
LED hiển thị:
Ngã tư A: ● ○ ○  (Đỏ sáng, Vàng tắt, Xanh tắt)
Ngã tư B: ○ ○ ●  (Đỏ tắt, Vàng tắt, Xanh sáng)