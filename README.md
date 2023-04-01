# SUPERCOMP Project - Movie Marathon

## Project Details

You want to spend a weekend watching as many movies as possible, but there are restrictions on the available schedules and the number of titles that can be watched in each category (comedy, drama, action, etc).

**Input:** An integer N representing the number of available movies to watch and N triples of integers (H[i], F[i], C[i]), representing the start time, end time, and category of the i-th movie. In addition, an integer M representing the number of categories and a list of M integers representing the maximum number of movies that can be watched in each category.

**Output:** An integer representing the maximum number of movies that can be watched according to the schedule and the maximum number per category restrictions.

The first implementation of the heuristic for our project consists of a greedy implementation.

Implement a greedy version that sorts the movies by increasing end time and chooses those that start first and do not conflict with the already chosen movies, as well as checking for available slots in the movie's category.

As we have seen in class, randomness is a common strategy for building local search algorithms, which can be used in isolation or complementarily with another strategy for scanning a space of solutions.

This implementation consists of adapting our project's greedy heuristic. The proposal is that you modify your greedy heuristic so that during the selection of a movie, you have a 25% chance of picking any other movie that respects the schedule. This will make your heuristic have a little more exploration and we can have some better results.

Important: it is essential that you keep all the inputs used throughout the project, so that you can compare the performance of your algorithms as we change the heuristic. That is, all heuristics must be submitted to the same input files. Your result should be compared from at least two perspectives: (i) execution time as a function of the increase in movies and categories, and (ii) screen time (that is, are we able to fill the 24 hours of the day watching movies well?).


## Output Example
'''
18 movies.
19 1 25
1 2 82
2 3 11
3 4 62
5 5 53
6 6 79
8 8 89
9 9 89
10 10 95
11 11 97
12 12 79
14 14 63
15 15 79
16 16 44
17 17 77
18 18 98
19 19 40
20 20 72
'''
