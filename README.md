# Program's name

The program monitors real time greenhouse gas data and compares current data with historial greenhouse gas data. The purpose of the program is that user can note the impact of gases on climate change.

MAIN branch does not have any functionality yet. 

## Usage

MVC-branch:
Running the code opens the UI window where you can start the program. Set time range, compare and average buttons open new windows, but user can’t do anything on them. From the combo box user can choose statfi, smear or compare. Compare doesn’t work yet. When user selects statfi or smear, she can also choose different gases and stations. After that user can press Show data button and graph shows up. At this point the graph’s data is always the same and it is defined in model.cpp. From quit button user can close the program.

STATFI-branch:
Running the code opens the empty UI window and prints data fetched from STATFI as a debug message. The test parameters are defined in main.cpp.

SMEAR-branch:
Running the code opens the empty UI window and prints data fetched from SMEAR as a debug message. The test parameters are defined in main.cpp.




