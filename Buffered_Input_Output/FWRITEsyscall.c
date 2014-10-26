/* Program to write structure to the  file */
#include<stdio.h>
#include<string.h>

int main()
{
	FILE *in,*out;
	size_t fw,fr,fcl1,fcl2;
	struct test{
		char name[100];
		unsigned long salary;
		unsigned int age;
		}p,man = {"MYNAME",34100,25};

		out = fopen("data.txt","w");
		if(out == NULL)
			perror("fopen");
		
		fw = fwrite(&man,sizeof(struct test),1,out);
		if(fw == 0)
			perror("fwrite");
		else
			printf("written no .of elements %d\n",fw);
		
		fcl1 = fclose(out);
		if(fcl1 == EOF)
			perror("fclose");

		in = fopen("data.txt","r");
		if(in == NULL)
			perror("fopen");
/*A call to fread will read upto 1 elements of data, each of size bytes */
		fr = fread(&p,sizeof(struct test),1,in);
		if(fr == 0)
			perror("fread");
		
		fcl2 = fclose(in);
                if(fcl2 == EOF)
                        perror("fclose");
		printf("name = %s,salary = %lu,age = %u \n",p.name,p.salary,p.age);

		return 0;	
}

/*OUTOUT :-
	$ ./executable
written no .of elements 1
name = MYNAME,salary = 34100,age = 25 
	*/
