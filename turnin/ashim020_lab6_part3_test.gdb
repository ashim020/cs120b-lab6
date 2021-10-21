# Test file for "cs120b_lab6"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

test "Start => PORTB: 0x07"
expectPORTB 7
checkResult

test "Start, Press A0 Once => PORTB: 0x08"
setPINA 0xFE
continue 1
setPINA 0xFF

expectPORTB 8
checkResult

test "Start, Hold A0 for 2 Ticks => PORTB: 0x09"
setPINA 0xFE
continue 2
setPINA 0xFF

expectPORTB 9
checkResult

test "Start, Hold A0 for 10 Ticks => PORTB: 0x09"
setPINA 0xFE
continue 10
setPINA 0xFF

expectPORTB 9
checkResult

test "Start, Press A1 Once => PORTB: 0x06"
setPINA 0xFD
continue 1
setPINA 0xFF

expectPORTB 6
checkResult

test "Start, Press A1 4 Times => PORTB: 0x03"
setPINA 0xFD
continue 1
setPINA 0xFF
continue 1
setPINA 0xFD
continue 1
setPINA 0xFF
continue 1
setPINA 0xFD
continue 1
setPINA 0xFF
continue 1
setPINA 0xFD
continue 1
setPINA 0xFF

expectPORTB 3
checkResult

test "Start, Hold A1 for 2 Ticks => PORTB: 0x05"
setPINA 0xFD
continue 2
setPINA 0xFF

expectPORTB 5
checkResult

test "Start, Hold A1 for 10 Ticks => PORTB: 0x00"
setPINA 0xFE
continue 10
setPINA 0xFF

expectPORTB 0
checkResult

test "Start, A1A0 => PORTB: 0x00"
setPINA 0xFC
continue 1
setPINA 0xFF

expectPORTB 0
checkResult 

test "Start, Hold A0 for 2 Ticks, A1A0 => PORTB: 0x00"
setPINA 0xFE
continue 2
setPINA 0xFF
continue 1
setPINA 0xFC
continue 1
setPINA 0xFF

expectPORTB 0
checkResult

test "Start, Press A1 3 Times, A1A0 => PORTB: 0x00"
setPINA 0xFD
continue 1
setPINA 0xFF
continue 1
setPINA 0xFD
continue 1
setPINA 0xFF
continue 1
setPINA 0xFD
continue 1
setPINA 0xFF
continue 1
setPINA 0xFC
continue 1
setPINA 0xFF
continue 1

expectPORTB 3
checkResult

test "Start, Hold A1 for 10 Ticks, A1A0 => PORTB: 0x00"
setPINA 0xFE
continue 10
setPINA 0xFF
continue 1
setPINA 0xFC
continue 1
setPINA 0xFF
continue 1

expectPORTB 0
checkResult


# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
