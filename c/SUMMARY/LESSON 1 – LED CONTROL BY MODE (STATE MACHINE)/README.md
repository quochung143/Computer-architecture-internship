/=================================================

Topic: LED CONTROL BY MODE

//=================================================

Requirements

There are 2 single LEDs

There are 3 operating modes:

//=================================================

Mode	LED1	LED2

//=================================================

0	Off	Off

1	On for 1s	Off

2	On 0.5s	Off 0.5s

//=================================================

Press INT0 → change mode (0 → 1 → 2 → 0)

Press INT1 → select LED


UART output:

//=================================================

MODE1 = x

MODE2 = x

//=================================================

Input format MX (select-mode)

Example: 10 : LED 1 mode 0

//=================================================

10
ok


13
ERROR: Format MX, M=0-1, X=0-1-2

//=================================================


7-segment LED displays the current mode
