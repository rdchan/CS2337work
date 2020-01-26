Project worth 10% of the class grade
Objective is to simulate an AI playing a game in which Beetles and Ants run around a board trying to eat each other/not get eaten
-Wrote a abstract Creature parent class with children Beetle and Ant
-Used inheritance and polymorphism to clean/simplify code base


Test cases that I wrote are in input/   

example board:
   aaa
 B  aa
 B   a
 B    aaa
      aaa
a     aaa
a
a   aaaa
    aaaa

Stored the game board as a 2d array of Creature pointers, using dynamic casting to distinguish between beetles and ants
Turns would be simulated with move orders for each object, both species could breed, move, die, and starve.
