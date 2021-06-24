/*
* RSA Algorithm
Step 1: Enter 2 prime numbers (p and q)
Step 2: Calculate product of primes (n = p * q)
Step 3: Calculate phi(n) or (t) (t = (p - 1)*(q - 1))
Step 4: Calculate values for (e) which is encryption key values using ce()
		e is calculated by values between 2 and t following the 3 below conditions
		1. e should be a prime
		2. e should not be equal to p or q
		3. e should not be a factor of t
Step 5: Calculate values for (d) which is decrytion key values using cd(). d values are dependent on e value
Step 6: Encrypt character with the steps (k = k * <char>; k = k % n) 'e' times with k = 1 initialization
Step 7: Decrypt character with the steps (k = k * <enc_char>; k = k % n) 'd' times with k = 1 initialization
*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

/*
p, q - holds the prime numbers entered by the user
n - product of primes entered by the user
t - holds the product of (primes - 1)
e - array holding maximum 500 encryption keys possible between 2 and sqrt(t)
d - array holding maximum 500 decryption keys for each e value
temp - intermediate array used to convert the value from char to int before storing in e
j - another intermediate value which stores sqrt(t) for calculating e values
m - second array holding the message as integer, to prevent original message from being modified
en - array of integers holding the encrypted value integers after calling encrypt
i - variable for iteration in loops 
*/
long int p, q, n, t, flag, e[500], d[500], temp[500], j, m[500], en[500], i;

// stores the original message input by the user for encryption 
char msg[500];

//determines if number is a prime or not
int prime(long int);

//calculates the 'e' value or encryption key
void ce();

//calculates the 'd' value or decryption key
long int cd(long int);

//encrypts the data passed
void encrypt();

//decrypts the data passed
void decrypt();

void main() {
	printf("\nEnter first prime number\n");
	//user enters the first number
	scanf_s("%d", &p);
	//check and return 0 if the value entered is not prime
	flag = prime(p);

	if (flag == 0) {
		//if not prime, throw error message
		printf("\n wrong input\n");
		//exit program waiting for user to press a key
		_getch();
		exit(1);
	}

	printf("\nEnter second Prime Number\n");
	//user enters the second number
	scanf_s("%d", &q);
	flag = prime(q);
	//with previous check of prime, also check if both values entered are different
	if (flag == 0 || p == q) {
		//values entered should be different 
		printf("\n Wrong Input\n");
		_getch();
		exit(1);
	}

	printf("\n enter Message\n");
	//user enters the message with max message size as 500 characters
	scanf_s("%s", msg, 500);
	//copy the message from character array to integer array, so original message is not modified
	for (i = 0; msg[i] != '\0'; i++)
		m[i] = msg[i];
	//calculate n value which is product of primes
	n = p * q;
	//calculate t value which is product of (primes - 1)
	t = (p - 1) * (q - 1);
	//call function to calculate e values, which internally also calls cd to calculate respective d values
	ce();
	printf("\nPossible Values Of e and d are\n");
	//print all possible e and d values calculated
	for (i = 0; i < j - 1; i++)
		printf("\n%ld\t%ld", e[i], d[i]);
	//encrypt the message passed
	encrypt();
	//decrypt the encrypted message
	decrypt();
	//wait for user to type a character before exit
	_getch();
}

int prime(long int pr) {

	int i;

	//we need to loop only till sqrt of value to check if its prime
	j = (long int)sqrt(pr);

	for (i = 2; i <= j; i++) {

		//if any value between 2 and sqrt(pr) is dividing the value easily, its not a prime number
		if (pr % i == 0)

			return 0;

	}

	return 1;

}

void ce() {

	//calculate e values or encryption keys in this method

	int k;

	k = 0;

	for (i = 2; i < t; i++) {

		//1. value shouldn't be factor of t
		if (t % i == 0)

			continue;

		flag = prime(i);

		//2. value should be a prime
		//3. value shouldn't be equal to p or q
		if (flag == 1 && i != p && i != q) {

			e[k] = i;
			printf("\ne:%d  ", e[k]);

			//calculate d or decryption key for respective encryption key or e
			flag = cd(e[k]);

			//store decryption key in d array
			if (flag > 0) {

				d[k] = flag;

				k++;

			}

			//stop calculating e or d values when 99 values are found
			if (k == 99)

				break;

		}

	}

}

long int cd(long int x) {

	printf("(p-1)(q-1):%d ", t);
	long int k = 1;

	while (1) {

		//add t to k every iteration
		k = k + t;

		//if k is divisible by e value , then k / e => d
		if (k % x == 0) {
			printf("valid k: %d", k);
			//return the d value for k when k % e == 0
			return(k / x);
		}

		printf("k: %d ", k);

	}

}

void encrypt() {

	long int pt, key = e[0], k, len;
	//long int ct;

	i = 0;

	//calculate length of message
	len = strlen(msg);


	while (i != len) {
		//select ith character for encryption with key e
		pt = m[i];

		k = 1;
		// run loop e times for below operations
		printf("\nkey: %d", key);
		for (j = 0; j < key; j++) {
			k = k * pt;
			k = k % n;

		}

		//store result k after e time operations in temp
		temp[i] = k;
		//add random value to k to get a different encrypted string which still results in same decrypted string
		//random value must also be subtracted on the decryption side to get proper results
		//ct = k + 96;
		//en[i] = ct;
		en[i] = k;
		i++;
	}

	//end the encrypted message with -1 as final value to denote end of string
	en[i] = -1;
	printf("\nTHE ENCRYPTED MESSAGE IS\n");
	//print encrypted message with -1 as the delimiter in integer array
	for (i = 0; en[i] != -1; i++)
		printf("%c", en[i]);

}

void decrypt() {

	long int ct, key = d[0], k;

	i = 0;

	while (en[i] != -1) {
		ct = en[i];
		k = 1;

		printf("\nkey: %d", key);

		//Run decryption steps for each encrypted character d times or decryption key times
		for (j = 0; j < key; j++) {
			k = k * ct;
			k = k % n;

		}
		//store decrypted value in m array to print string
		m[i] = k;
		i++;

	}
	//end the decrypted string with delimiter as -1
	m[i] = -1;

	//print decrypted string on screen with delimiter as -1
	printf("\nTHE DECRYPTED MESSAGE IS\n");
	for (i = 0; m[i] != -1; i++)
		printf("%c", m[i]);

}
