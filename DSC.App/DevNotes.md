# DevNotes

Here is the information about the DSC namespace structure, api, main variables etc.

## DSC.GUI

This is the main execution core. It launches the window and makes use of the other components

## DSC.Projects

All about the Project class and its components

## DSC.Session

Global resources available at runtime, including user settings:

- Project : The current project instance

- ExecutablePath : The path containing the running DSC.exe file
- AppDataPath : Path to store user preferences
- DefaultProjectPath : The default path to store projects