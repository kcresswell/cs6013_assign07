#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<errno.h>

#define BUFFER_SIZE 10

void printStuff(unsigned char *buffer, int size){
   int i; 
   for(i = 0; i < size; i++){
     printf("%d ", buffer[i]); 
   }
   printf("\n");
}

int main(int argc, char **argv) {
     int ret, fd; 
     unsigned char buff1[BUFFER_SIZE];
     unsigned char buff2[BUFFER_SIZE];
     unsigned char key[5] = "hello"; 

     printf("Testing stuff..."); 
	
     fd = open("/dev/myRand", O_RDWR);

     if(fd < 0){
       perror("Device failed to open :'(");
       return errno;
     }
//need to make a loop to print out each char rather than a string, same with strlen issue

     printf("Keystream: "); 
     for(int i = 0; i < 5; i++){
        printf("%c", key[i]);
     
      }
     printf("\n");      
     //printf("Keystream for RC4: [%s].\n", key);

    // printf("Test size strlen in write: %lu\n", strlen(key));
    printf("Size of key array: %lu ", sizeof(key));
    printf("\n"); 

     ret = write(fd, key, strlen(key));
     if(ret < 0){
	     perror("Failed to write the message"); 
	     return errno; 
     }

     //RC4 random test, returns different result each time
     //read buffer1
     ret = read(fd, buff1, 10);
     //read buffer2
     ret = read(fd, buff2, 10);
     printStuff(buff1, 10);
     printStuff(buff2, 10);

     /*
      * * RC4 Reinitialize Test
      * *  * Returns same result each time it is read 
      
     printf("Reinitialize Test, should print the same value in buff1 and buff2\n"); 
     ret = write(fd, key, strlen(key)); 
     ret = read(fd, buff1, 10); 
     ret = write(fd, key, strlen(key));
     ret = read(fd, buff2, 10);
     //print stuff
     printStuff(buff1, 10); 
     printStuff(buff2, 10); 
     */

     return 1; 
}
