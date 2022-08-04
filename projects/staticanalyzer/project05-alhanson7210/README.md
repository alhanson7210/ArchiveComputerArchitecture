# project05-alhanson7210
project05-alhanson7210 created by GitHub Classroom

## Student
_Developer_
- Name: Alex Hanson
- Section: 03
- Due: 11/9/2020
- Completed: 11/8/2020

## Stactic Analyzer 
```
* Static Analyzer sets DIP SWITCH to high, PN to zero, & the clock with real-time start
- analyses IW and counts the number and type of instructions within a program
- runs orginal top level circuit from project spec

* Test Analyzer is used for checking output(count) with an external clock sent into S_A
  (same circuit as the Static Analyzer but no embedded DIP SWITCH and Clock)
  and external DIP SWITCH so it can be used to test programs without changing inputs
  in the statict analyzer (original/class top level circuit)  
```
## Components
```
- Comparators:
  * Various lower base comparators
  
- Latches:
  * D 
  * SR
  
- Registers:
  * D flip flop clr 
  
- Decoder
  * 32 bit IW decoder
  
- Counters:
  * Various lower base counters

- Adders:
  * Various lower base Adders

- Instruction Memory
  * 2 Loaded Roms
    • quadratic_s.hex
    • reverse_s.hex
  * 8 bit addresses from 16 bit counter -> 32 IW
```
## Expected Output
_Program One_
```
INST: 17(0x11)
DP: 7
MEM: 5
BRANCH: 4
MUL: 0
BX: 1
```
_Program Zero_
```
INST: 6
DP: 2
MEM: 0
BRANCH: 0
MUL: 3
BX: 1
```
## Given Files:
_inclass: hex_
```
- quadratic_s.hex
- reverse_s.hex
```
_inclass: base components_
```
- sr-latch.dig
- d-latch-clr.dig
- d-flip-flop-clr.dig
```
_inclass: References_
- [Top-Level-Circuit and Project-Spec](http://cs315.cs.usfca.edu/projects/project05)
