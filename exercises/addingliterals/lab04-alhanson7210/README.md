# lab04-alhanson7210
lab04-alhanson7210 created by GitHub Classroom

Due
Monday Sept 14th at 11:59 PM to Github

The Github Classroom assignment URL will be published in your section's Piazza

Requirements
Add the ability to take a binary literals as well as decimal integer literals. To do this:

Your scanner should identify "0b" and scan binary digits

Your scanner should encounter "0b101" and store "101" in the scan_token name.

Your parser should convert "101" to decimal 5, and store that as a uint32_t in the intval of the parse_node_st. 

Note: In previous labs, there is a call to the C library function atoi() to convert a character string of decimal digits to an integer. You should replace this with your own base conversion code.

For binary output (-b 2) your eval code should output 32 bits

Add the ability to write the results out in binary (base 2). The examples below illustrate the desired input and output. Your eval code should use the parse_node's operator to evaluate the intvals after your parser has done the base conversion.
$ ./lab04 -e "17 - (0b1000 * (0b01 + 1))" -b 2
0b00000000000000000000000000000001

$./lab04 -e "0b1011101011010001 - 0b10101" -b 2
0b00000000000000001011101010111100

Add unary NOT (~) to your scanning, parsing, and eval code.
$ ./lab04 -e "~(0 - 1)" -b 2
0b00000000000000000000000000000000

$ ./lab04 -e "~0b11111111 + 1" -b 2
0b11111111111111111111111100000001

Add a two-operand operator for Logical Shift Left (<< with an uint32_t) to your scanning, parsing and eval code.
$ ./lab04 -e "(~0b11111111 + 1) << 8" -b 2
0b11111111111111110000000100000000

$ ./lab04 -e "2 * (1 + (8 << 1))" -b 2
0b00000000000000000000000000100010
