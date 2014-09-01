Compilation
-----------------------
From command line run 
1. qmake
2. nmake -f Minsense.Debug
3. nmake -f Minsense.Release

or alternatively
Open Minsense.pro in Qt Creator and compile

Run application after compilation


Program Guide
-----------------------
The program has four menu items.

1. Open
Opens files to display line graph data

2. Save
Saves any changes made to the line graph data back to the file

3. Close
Closes any open line graphs

4. Exit
Exits the application


Test Run
----------------------
Open mcvdata.csv file in the program. Then take mouse over any red points (the data points). Once data point 
is highlighted, click and drag point. The point should move with mouse and the lines should adjust as 
well around the point. Save file, close and open again. The changes should now be persistent.

To test case, select the left most, right most and a point anywhere else and change the data. Save and reload
file and check if the changes persisted.


Known Bugs
----------------------
The axis right now is hard coded but it could be easily changed in the future.
When a data point is selected, a text label is displayed. It is however inverted. I tried to invert it again,
but to no avail as yet. To be fixed in the future.