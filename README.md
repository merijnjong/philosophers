# philosophers
In this project, I will learn the basics of threading a process.<br />
I will see how to create threads and I will discover mutexes.
Program name | philo |
|:--- |:---
Turn in files | [Makefile](https://github.com/merijnjong/philosophers/blob/main/Makefile), [philo.h](https://github.com/merijnjong/philosophers/blob/main/philo.h), [philo.c](https://github.com/merijnjong/philosophers/blob/main/philo.c), in directory philo/ |
Makefile | NAME, all, clean, fclean, re |
Arguments | number_of_philosophers time_to_die time_to_eat time_to_sleep<br />[number_of_times_each_philosopher_must_eat] |
External functions | memset, printf, malloc, free, write,<br />usleep, gettimeofday, pthread_create,<br />pthread_detach, pthread_join, pthread_mutex_init,<br />pthread_mutex_destroy, pthread_mutex_lock,<br />pthread_mutex_unlock |
Libft authorized | No |

### Instructions
The specific rules for the mandatory part are:
* Each philosopher should be a thread.
* There is one fork between each pair of philosophers. Therefore, if there are several<br />
philosophers, each philosopher has a fork on their left side and a fork on their right<br />
side. If there is only one philosopher, there should be only one fork on the table.<br />
* To prevent philosophers from duplicating forks, you should protect the forks state<br />
with a mutex for each of them.

### Overview
Here are the things you need to know if you want to succeed this assignment:<br />
* One or more philosophers sit at a round table. There is a large bowl of spaghetti<br />
in the middle of the table.
* The philosophers alternatively eat, think, or sleep. While they are eating, they are<br />
not thinking nor sleeping; while thinking, they are not eating nor sleeping; and, of course,<br />
while sleeping, they are not eating nor thinking.<br />
* There are also forks on the table. There are as many forks as philosophers.<br />
* Because serving and eating spaghetti with only one fork is very inconvenient, a philosopher<br />
takes their right and their left forks to eat, one in each hand.<br />
* When a philosopher has finished eating, they put their forks back on the table and start<br />
sleeping. Once awake, they start thinking again. The simulation stops when a philosopher<br />
dies of starvation.<br />
* Every philosopher needs to eat and should never starve.<br />
* Philosophers don’t speak with each other.<br />
* Philosophers don’t know if another philosopher is about to die.<br />
* No need to say that philosophers should avoid dying!<br />

### Global rules
You have to write a program for the mandatory part it has to comply with the following rules:
* Global variables are forbidden!
* Your program should take the following arguments:<br />
number_of_philosophers time_to_die time_to_eat time_to_sleep<br />[number_of_times_each_philosopher_must_eat]<br />
  ◦ number_of_philosophers: The number of philosophers and also the number of forks.<br />
  ◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die<br />
  milliseconds since the beginning of their last meal or the beginning of the simulation<br />
  they die.<br />
  ◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time,<br />
  they will need to hold two forks.<br />
  ◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.<br />
  ◦ number_of_times_each_philosopher_must_eat (optional argument): If all philosophers<br />
  have eaten at least number_of_times_each_philosopher_must_eat times, the simulationstops.<br />
  If not specified, the simulation stops when a philosopher dies.<br />
* Each philosopher has a number ranging from 1 to number_of_philosophers.
* Philosopher number 1 sits next to philosopher number number_of_philosophers. Any other<br />
philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.<br />

About the logs of your program:
* Any state change of a philosopher must be formatted as follows:<br />
  ◦ timestamp_in_ms X has taken a fork<br />
  ◦ timestamp_in_ms X is eating<br />
  ◦ timestamp_in_ms X is sleeping<br />
  ◦ timestamp_in_ms X is thinking<br />
  ◦ timestamp_in_ms X died<br />

  Replace timestamp_in_ms with the current timestamp in milliseconds and X with the<br />
  philosopher number.
* A displayed state message should not be mixed up with another message.
* A message announcing a philosopher died should be displayed no more than 10 ms after the<br />
actual death of the philosopher.
* Again, philosophers should avoid dying!
