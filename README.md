# Datapresenter

The program monitors real time and historial greenhouse gas data from SMEAR and STATFI. The purpose of the program is that user can note the impact of gases on climate change.

## Running code

Project must be open in Qt Creator for running it. Pressing Run-button in Qt Creator starts the program. 


## Usage

Main-branch:
Running the code opens the UI window. When user selects statfi or smear, she can also choose different gases, stations and time ranges. After that user can press Show button and graph shows up. Program checks users input and notifies user of invalid inputs. If user selects both databases, application shows graphs for all selected gases. In that case user can compare different graphs from different databases. Statistics buttons opens new window where user can view min, max and average values from SMEAR. From quit button user can close the program.

Code must be run in datapresenter folder to get use of the colours. 
If getting data from a larger range software can be run in fullscreen to see more dates on the x-axis.
When using SMEAR data there must be at least one day difference between start and end dates. This is because the day starts at 00.00.
SMEAR data has limit of seven (7) days for accessing data to make charts more readable for user.
Preferences can be used after charts are diplayed. Saving a preference saves the last displayed configurations. Pressing preferences button will check the boxes used int the last save and user can show them again.

Interface:
IMPORTANT for developers:
To synchronize model with an interface model needs to call it twice. Once with fetchData() to setup the data in an interface and second time with getData() to actually return the data. This will fill the gap in time between asking for the data and receiving it from a website. The implemented interface should notify model when data can be pulled from the interface.

STATFI-branch:
Running the code opens the empty UI window and prints data fetched from STATFI as a debug message.

SMEAR-branch:
Running the code opens the empty UI window and prints data fetched from SMEAR as a debug message.


## Technologies

This project is created by using c++ and Qt Creator.

## Future features

We hope that there is more stations and gases in the future. New databases are also easy to add since databases have common interface. Also more plot options could be added to the program and multiple plot options could be added to the same chart.

## Authors

Julia Harttunen
Verna Leisti
Krista Mätäsniemi
Eero Tarri


