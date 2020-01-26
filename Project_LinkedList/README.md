Project worth 10% of the class grade
Objective is to display leaders and stats for a baseball league
-Wrote a linked list to hold the players

Pipeline:
1. Read in the stats file, which is lines of Name <space> String_of_baseball_stats
2. Create a player with that name and those stats
3. Add them to the linked list of players
4. Sort the linked list by different metrics and display

example input:
Peach OOOHHHWWWSSSKWOOOS
Zelda SSSSSSSSSS
DK HHHOHHHHHHH
Mario HWKPOSHWKPOSHWKPOS
Link HHHHHWWWWKKKKOOOOHHHHHKKKKOOOHHHHHKKKK
Pit SH
Wario KKKKKPKKKKKKHOKKPKKKPOKKKHKPKOKKKPKK

example output:
DK      11      10      0       0       0       0       0.909   0.909
Link    34      15      4       12      0       0       0.441   0.500
Mario   9       3       3       3       3       3       0.333   0.500
Peach   10      3       4       1       0       4       0.300   0.389
Pit     1       1       0       0       0       1       1.000   0.500
Wario   31      2       0       26      5       0       0.065   0.194
Zelda   0       0       0       0       0       10      0.000   0.000

LEAGUE LEADERS
BATTING AVERAGE
1.000   Pit
0.909   DK
0.441   Link

ON-BASE PERCENTAGE
0.909   DK
0.500   Link, Mario, Pit

HITS
15      Link
10      DK
3       Mario, Peach

