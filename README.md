# dot-selection
A simple implementation of genetic algorithms.

A number of dots are spawned on a certain area of the screen, together with a goal area, and the entire population slowly mutates such that the average frequency of a dot reaching the goal post gradually increases until it hits a plateau.

Each dot has a _brain_, which consists of a sequence of accelerations applied to it. These are chosen at random when a dot is initialized via a uniform random distribution, and have a mutation chance after each epoch.

The performance of the dots is judged via the final distance between them and the goal posts.

At the end of each epoch, a certain portion of the best performing dots are chosen and transplanted into the next epoch. This is called Elitism. After that, the fitnesses of these elites are normalized and the population is inflated back to its beginning size by adding copies of the elites depending on how much their fitness contrubuted to the cumulative fitness. 

All variables such as the number of dots, the mutation chance, the position of the goal area, etc are initialized at compile time.
