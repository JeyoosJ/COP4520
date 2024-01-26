# COP4520
Processes of Parallel and Distributed Processing

Summary:
I created 8 threads and assigned work to each thread to calculate prime numbers. One major observation is that even numbers, except for 2 are never prime. So I assigned starting values to each thread as 1,3,5,7,9,11,13,15. Each thread would check the numbers in multiples of 16, starting from this number. This was done to avoid double-counting. If I assigned ranges to the threads, each thread would not perform equal amount of work as the thread assigned larger numbers would take much more time to finish evaluating compared to a thread assigned smaller numbers. This distribution of work I came up with will ensure that each thread is given approximately equal amount of work. Giving each thread equal amount of work will reduce the total runtime, as otherwise if one thread takes long, the entire program will take long. 

I also optimized my isPrime function using the Sieve of Eratosthenes technique. Instead of using the sqrt function, I used i*i. I also tried switching between push_back and emplace_back in some places to see what reduces runtime. To prevent sorting the list of primes to find the 10 largest primes, I used a max heap (priority queue) to keep the numbers sorted from largest to smallest, thereby saving runtime.

I also checked my results for correctness using an online prime calculator tool to cross-check the number of primes and sum of primes output that I got. I also compared my results before and after using the multi-threading approach.


Instructions:
Open Command Prompt
Navigate to the folder where the file is in, using the command cd
Then type and enter the following commands 
g++ assignment1.cpp -o assignment1.exe
./assignment1
