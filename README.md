# You Used to Call Me on My Semaphone

#JIEYU XU, XINHUI XU
## How to Use your Semaphone
1. Type make to compile the c files
2. To create a semaphore, shared memory, and new story, type ```./control.out -c```
3. To view the full story, type ```./control.out -v```
4. To remove the semaphore, shared memory, type ```./control.out -r```
5. To update a story, type ```./writer.out```. You will be shown the last update (blank if this is your first update), and a prompt to type your story update.

## Sample Run
```
Amys-MacBook-Air:youusedtocallmeonmysemaphone amy$ make
gcc -g -o control.out control.c
gcc -g -o writer.out writer.c
Amys-MacBook-Air:youusedtocallmeonmysemaphone amy$ ./control.out -c
semaphore created: 720896
shared mem created: 655360
Amys-MacBook-Air:youusedtocallmeonmysemaphone amy$ ./writer.out
[2927]: hello.
>> 
>> this is my first update, that's why the above line is blank
[2927]: thank you for your contribution.
Amys-MacBook-Air:youusedtocallmeonmysemaphone amy$ ./control.out -v
Full story:
this is my first update, that's why the above line is blank

Amys-MacBook-Air:youusedtocallmeonmysemaphone amy$ ./writer.out
[2929]: hello.
>> this is my first update, that's why the above line is blank

>> this is my second update.
[2929]: thank you for your contribution.
Amys-MacBook-Air:youusedtocallmeonmysemaphone amy$ ./control.out -r
Full story:
this is my first update, that's why the above line is blank
this is my second update.

```
