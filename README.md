![](https://github.com/Sur1ive/42tokyo_piscine/blob/master/42.png)
# minitalk
**Final grade: 125%**:white_check_mark:</br>

You must create a communication program in the form of a client and a server.
The communication between your client and your server has to be done only using UNIX signals.
- You can only use these two signals: SIGUSR1 and SIGUSR2.

I send messages and check if it is correct with 32byte-package like this.</br>
```
/*                    32byte-package                         */
/*  [ PID bytes(4B) | message bytes(24B) | check bytes(4B)]  */
/*     client PID    6 utf8 char 1char/4B     sum of 28B     */
```

## How to use
```
'''console A'''
make
./server
'''console B '''
./client [file descriptor] [message]
```

## NOTICE 
42 Project must be written in accordance with the 42 school norm, otherwise the grade is 0:
* Declarations must be at the beginning of a function
* Declaration and an initialisation cannot be on the same line
* Each function cannot have more than 25 lines of code
* You can only use allowed functions
* ...

English: https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf <br />
Japanese: https://github.com/42School/norminette/blob/master/pdf/ja.norm.pdf
