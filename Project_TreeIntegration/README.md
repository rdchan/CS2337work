Project worth 10% of the class grade
Objective is to compute definite and indefinite integrals
-Wrote a binary tree to hold tokenized inputs
-Used inheritance to handle polynomial and trig terms

example input of 5 indefinite followed by 2 definite:
| sin x- cos x dx
| cos x +x^2 + x + sin xdx
| 7x^6 - x^-2 + x^-7 + sin 10x + 5x - cos 4xdx
| 30 cos 30x + 45 sin 45x - 5x + x^2 + 15 sin 15x + 3x^-2 dx
| 1 - cos 5x + x^3 dx
-2|2 x^3-4x dx
1|4 x^-2 +3x+4 dx
1|3 5x^-3 dx

example output:
-cos x - sin x + C
(1/3)x^3 + (1/2)x^2 + sin x - cos x + C
x^7 + (5/2)x^2 + x^-1 - (1/6)x^-6 - (1/10)cos 10x - (1/4)sin 4x + C
(1/3)x^3 - (5/2)x^2 - 3x^-1 + sin 30x - cos 45x - cos 15x + C
(1/4)x^4 + x - (1/5)sin 5x + C
(1/4)x^4 - 2x^2, -2|2 = 0.000
(3/2)x^2 + 4x - x^-1, 1|4 = 35.250

