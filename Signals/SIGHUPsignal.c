/*Program to catch SIGHUP signal, if we terminate/close the terminal/session-leader
while the process running at foreground 
1) First run this program on your current terminal/session-leader. 
2) This program goes to pause/sleep mode or infinite mode. 
3) Close/Kill your current session/terminal.
4) The kernel will send SIGHUP signal to this process/program. 
5) We are catching this signal by our signal handler. 
6) Our Signal handler will create a file in your current directory where the proccess was running.
7) This process will write sighup to the file i.e HURRAY we able to caught the signal
8) This is just simple example we have tried as an example.*/

/*SIGHUP
The kernel sends this signal to the session leader whenever the session’s terminal
disconnects. The kernel also sends this signal to each process in the foreground
process group when the session leader terminates. The default action is to terminate,
which makes sense—the signal suggests that the user has logged out. Daemon pro‐
cesses “overload” this signal with a mechanism to instruct them to reload their
configuration files. Sending SIGHUP to Apache, for example, instructs it to reread
httpd.conf. Using SIGHUP for this purpose is a common convention but not manda‐
tory. The practice is safe because daemons do not have controlling terminals and
thus should never normally receive this signal.*/
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void myHandler(int signumber)
{
	/*Technically ,you shouldn't use printf()
	in a signal handler (Reference linux system programming)
	please see note.txt for the answer */
	if(signumber == SIGHUP)
		system("echo sighup caught HURRAY! > my.txt");
	exit(EXIT_SUCCESS);	
}

int main()
{
	if((signal(SIGHUP,myHandler)) == SIG_ERR)
	{
		perror("signal");
		exit(EXIT_FAILURE);
	}
	printf("Waiting for you to close the terminal\n");
	for(;;)
		pause();
	return 0;
}

/*OUTPUT :- 
$ ./a.out
Waiting for you to close the terminal

$ ls -l | grep my.txt
-rw-rw-r-- 1 root root    1 Aug 10 12:33 my.txt

$ cat my.txt 
sighup caught HURRAY!
 */
