=================================================
Chủ đề: LED đa chế độ – chuyển mode bằng ngắt
=================================================
Yêu cầu

Có 2 LED đơn

Có 3 chế độ hoạt động:
=================================================
Mode	LED1	LED2
=================================================
0	Tắt	Tắt
1	Nháy 1s	Tắt
2	Nháy 0.5s	Nháy 1s
=================================================
Nhấn INT0 → chuyển mode (0 → 1 → 2 → 0)
Nhấn INT1 → chọn led

UART in ra:
=================================================
MODE1 = x
MODE2 = x
=================================================

LED 7 đoạn hiển thị mode hiện tại

Kỹ thuật bắt buộc

Timer interrupt

State machine

Không delay blocking