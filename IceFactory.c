#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <linux/kernel.h>
#include <time.h>

	

sem_t fCounter, tCounter, topCounter, paymentCounter;

void *IceCreamFactory(void *num);
int flavors[4];
int toppings[3];
int priceTop[3];
int priceFlav[4];

int main(){
printf("----------WELCOME TO THE ICE CREAM FACTORY PROGRAM-----------\n");
srand(time(0));	

int n = 10;

for (int i = 0; i < 4; i += 1)
{
	flavors[i] = (rand()%(20 - 15 + 1)) + 15;
	priceFlav[i] = (rand()%(5 - 1 + 1)) + 1;
}

for (int i = 0; i < 3;  i += 1)
{
	toppings[i] = (rand()%(20 - 15 + 1)) + 15;
	priceTop[i] = (rand()%(3 - 1 + 1)) + 1;
}
	int c;
	printf("Enter Number of customers: ");
	scanf("%d" , &c);
	int cus[c];
	
	sem_init(&tCounter , 0 , 1);
	sem_init(&fCounter , 0 , 1);
	sem_init(&topCounter , 0 , 1);	
    sem_init(&paymentCounter, 0 , 1);
	pthread_t customers[c];
	
	for(int i = 0; i < c; i++){
		cus[i] = i+1;
	}
	
	for(int i = 0; i < c; i++){
		pthread_create(&customers[i], NULL, IceCreamFactory, &cus[i]);
	}
	
	for(int i = 0; i < c; i++){
		pthread_join(customers[i], NULL);
	}
	
	printf("ALL CUSTOMERS HAVE BEEN SERVED!");
	printf("CLOSING SHOP NOW!");
	
}

void *IceCreamFactory(void *num){
	float bill = 0.0;
	int no = *(int *)num;
	printf("Customer %d arrives at the ticket counter! \n", no);
	syscall(335, " arrives at the ticket counter! \n" , no);	
	sleep(2);
	sem_wait(&tCounter);
	printf("--------------------------------------------------\n");
	printf("Customer %d arrives at the flavor counter! \n", no);
	syscall(335, " arrives at the flavor counter! \n" , no);
	sleep(2);
	sem_post(&tCounter);
	sem_wait(&fCounter);
	printf("--------------------------------------------------\n");
	int fChoice = rand() % 3;
	if(flavors[fChoice] > 0){
		printf("Customer %d has selected flavor %d!\n", no, fChoice+1);
		bill = bill + priceFlav[fChoice];
		flavors[fChoice]--;
	}
	else{
		printf("Customer %d has selected flavor %d!\n", no, fChoice+1);	
		printf("The selected flavor has finished! Customer %d is leaving the shop!\n", no);
		sem_post(&fCounter);
		return 0;
	}
	sem_post(&fCounter);
	sem_wait(&topCounter);
	printf("--------------------------------------------------\n");
	printf("Customer %d has arrived at the toppings counter! \n" , no);
	syscall(335, " arrived at the toppings counter! \n" , no);	
	sleep(2);	
	int tChoice = rand() % 2;
	
	if(toppings[tChoice] > 0){
		printf("Customer %d has selected topping %d!\n", no, tChoice+1);
		bill + bill + priceTop[tChoice];
		toppings[tChoice]--;
	}
	else{
		printf("Customer %d has selected topping %d!\n", no, tChoice+1);	
		printf("The selected topping has finished! Customer %d is leaving the shop!\n", no);
		pthread_exit(NULL);
	}
	sem_post(&topCounter);
	
	sem_wait(&paymentCounter);
	printf("--------------------------------------------------\n");
	syscall(335, " has arrived at the payment counter! \n" , no);
	printf("Customer %d has arrived at the Payment Counter!\n", no);
	printf("Total Bill for Customer %d = %.2f", no, bill);
	printf("\n");
	sem_post(&paymentCounter);
	printf("--------------------------------------------------\n");
	syscall(335, " has recieved their Ice Cream! \n" , no);	
	printf("----CUSTOMER %d HAS RECIEVED THEIR ICE CREAM!---- \n" , no);
	printf("----CUSTOMER %d IS LEAVING THE SHOP!---- \n" , no);	
	sleep(2);
}

























