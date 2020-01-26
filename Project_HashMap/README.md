Project worth 10% of the class grade.
Objective is to display leaders and stats for a baseball league
- Wrote a templated hash table with double-hashing

Pipeline:
1. Read in the keyfile to figure out what baseball terms different codes correspond to
2. Create a hash table to quickly map the codes to baseball terms
3. Read in the play by play, which is a list of Team:Player:Code tuples
4. Populate a hash table with the players, adding to it for new names, modifying the entry for repeated names
At this point, the objects in the players hash table has all the data
5. Display individual player stats, sorted alphabetically
6. Display leaders from each team in each baseball stat