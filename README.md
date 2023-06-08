# SUPERCOMP Project - Movie Marathon

## Project Details

You want to spend a weekend watching as many movies as possible, but there are restrictions on the available schedules and the number of titles that can be watched in each category (comedy, drama, action, etc).

#### Input 
An integer N representing the number of available movies to watch and N triples of integers (H[i], F[i], C[i]), representing the start time, end time, and category of the i-th movie. In addition, an integer M representing the number of categories and a list of M integers representing the maximum number of movies that can be watched in each category. Example:
```
10 4
1 3 1 2 
11 13 3
14 15 3
10 16 2
10 14 1
11 17 2
11 14 3
13 15 3
14 15 1
12 16 4
12 13 4
```


#### Input 
An integer representing the maximum number of movies that can be watched according to the schedule and the maximum number per category restrictions. Example: ``` 8 movies ```.


#### Heuristics 

The first implementation of the heuristic for our project consists of a greedy implementation.

Implement a greedy version that sorts the movies by increasing end time and chooses those that start first and do not conflict with the already chosen movies, as well as checking for available slots in the movie's category.

As we have seen in class, randomness is a common strategy for building local search algorithms, which can be used in isolation or complementarily with another strategy for scanning a space of solutions.

This implementation consists of adapting our project's greedy heuristic. The proposal is that you modify your greedy heuristic so that during the selection of a movie, you have a 25% chance of picking any other movie that respects the schedule. This will make your heuristic have a little more exploration and we can have some better results.

**Important:** it is essential that you keep all the inputs used throughout the project, so that you can compare the performance of your algorithms as we change the heuristic. That is, all heuristics must be submitted to the same input files. Your result should be compared from at least two perspectives: (i) execution time as a function of the increase in movies and categories, and (ii) screen time (that is, are we able to fill the 24 hours of the day watching movies well?).

#### Exaustive search

Another implementation that is being used in our project is the exaustive search.

Exhaustive search, also known as brute-force search, algorithms are computational methods that explore all possible solution combinations for a problem. 

They are used when it is necessary to examine all solutions without relying on optimizations or heuristics. Exhaustive search algorithms are applied to optimization, combinatorial, password cracking, and game problems. However, they can become impractical for problems with a large number of possible combinations, which is our case in the selection of movies.

It is a systematic method of solving a problem by evaluating all possible solutions. It involves systematically examining every candidate solution in a problem space until the correct solution is found or all possibilities have been exhausted. All potential solutions are evaluated one by one, without applying any optimization or heuristic techniques to narrow down the search space. This means that every possible combination or configuration is considered, ensuring that no potential solution is missed.
