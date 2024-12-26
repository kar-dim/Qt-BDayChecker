# BDayChecker

## Overview
The Birthday Reminder is a simple GUI application developed in C++ using the Qt framework. Its purpose is to notify users of birthdays on the current day by displaying a pop-up window with a list of names. 
The application reads birthday data from a configuration file `config.ini` located in the same directory as the executable.

## Features
- **Daily Notifications**: Automatically checks for birthdays matching today's date. Can be run at startup by creating a Shortcut of the .exe in this Windows folder: `C:\Users\{Username}\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup`.
- **User-Friendly Interface**: Displays a pop-up with a list of names when a birthday is found.
- **Customizable Data Source**: Specify birthdays data source and other settings from a user-editable `config.ini` file.

## Installation
1. Ensure that the required Qt libraries are installed on your system.
2. Download or clone the project files.
3. Build the project using Qt Creator or a compatible build system (e.g., CMake).
4. Place the compiled executable in the desired folder.
5. Ensure that a valid `config.ini` file is in the same directory as the executable, and a valid birthday data source exists

## Usage
1. **Prepare the Configuration File:**
   - Create a `config.ini` file in the following format:
     
     ```ini
     [options]
     bday_file_path = C:\{...}\bday.txt
     #music_path = C:\{...}\bg_ost.mp3 #music is optional
     ````
     - Ensure the section `[options]` exists.
     - The above file names are examples, they can have whatever name is desired.

2. **Prepare the Birthdays Data Source:**
   - Create a text file that contains the birthdays:
   - Each entry should have the format: `Name MM/DD`, for example:
     
   ```
   Mother 25/1
   John Kyprios 11/2
   Luis Garcia 14/5
   ````
   
4. **Run the Application:**
   - Launch the executable. The application will check today's date against the birthdays in `config.ini`.
   - If there is a match, a pop-up window will display the names of individuals with birthdays today.
   - **NOTE** The application is mostly intented to run at OS startup, create a Shortcut of the .exe in this Windows folder: `C:\Users\{Username}\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup`.
