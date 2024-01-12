#include <stdio.h>
#include <string.h>

#define MAX_BUF  256

#define IV  0b10110001
#define KEY 0b11001011
#define CTR 0b00110101

void encode(unsigned char*, unsigned char*, int);
void decode(unsigned char*, unsigned char*, int);

unsigned char processCtr(unsigned char, unsigned char);
unsigned char encryptByte(unsigned char, unsigned char, unsigned char);
unsigned char decryptByte(unsigned char, unsigned char, unsigned char);

unsigned char getBit(unsigned char, int);
unsigned char setBit(unsigned char, int);
unsigned char clearBit(unsigned char, int);

int main()
{
	char str[8];
	int  choice;

    printf("\nYou may:\n");
    printf("  (1) Encrypt a message \n");
    printf("  (2) Decrypt a message \n");
    printf("  (0) Exit\n");
    printf("\n  what is your selection: ");
    fgets(str, sizeof(str), stdin);
    sscanf(str, "%d", &choice);

    if (choice == 0) {
    	return 0;
	}

	unsigned char plaintext[MAX_BUF];
	unsigned char cyphertext[MAX_BUF];
	int userInput;
  	switch (choice) {
    	case 1:
		  	printf("Enter a message to encrypt: ");
		  	fgets((char*)plaintext, MAX_BUF, stdin);
		  	encode(plaintext, cyphertext, MAX_BUF);
		  
		  	int i = 0;
		  	while(1){
		  		if(i >= MAX_BUF){
		  			break;
		  		} else if (plaintext[i] == '\0'){
		  			break;
		  		}
		  		printf("%d ", cyphertext[i]);
		  		i++;
		  	}
		  	
      	break;
    	case 2:
    		printf("Enter a sequence of integers: ");    		
    		
    		for(int k = 0; k < MAX_BUF; k++){
    			scanf("%d", &userInput);
    			if(userInput == -1 || userInput > 255){
            		break;
        		}
        		cyphertext[k] = (unsigned char)userInput;
    		}
    		
    		decode(cyphertext, plaintext, MAX_BUF);
    		
    		int j = 0;
    		while(1){
    			if(j >= MAX_BUF){
    				break;
    			} else if (plaintext[j] == '\0'){
    				break;
    			}
    			
    			printf("%c", plaintext[j]);
    			j++;
    		}
      	break;
  	}

  	return(0);
}

/*
Function: ProcessCtr
Purpose: This function takes in a counter and key and processes the counter and returns the new counter 
in: The current counter
in: The key
return: Temporary counter which is the new value of the counter
*/
unsigned char processCtr(unsigned char ctr, unsigned char key){
	unsigned char tempCounter = ctr;
	
	unsigned char startingBit;
	
	if(tempCounter % 2 == 0){
		startingBit = 0;
	} else {
		startingBit = 1;
	}
	
	for (int i = startingBit; i < 8; i += 2){
		if((getBit(ctr, i) ^ getBit(key, i)) == 1){
			tempCounter = setBit(tempCounter, i);
		} else {
			tempCounter = clearBit(tempCounter, i);
		}
		
	}
		
	return tempCounter;
}

/*
Function: EncryptByte
Purpose: This function takes in a byte of plaintext and the previous byte of cyphertext and encrypts it into a byte of cypher text
in: Byte of plaintext, previous byte of cyphertext, and byte of cypher text that is to be encrypted
return: Temporary byte which is the encrypted byte of cypher text
*/
unsigned char encryptByte(unsigned char pt, unsigned char ctr, unsigned char prev){
	unsigned char tempByte = 0;
	
	for(int i = 0; i < 8; i++){
		if(getBit(ctr, i) == 1){
			if((getBit(pt, i) ^ getBit(prev, i)) == 1){
				tempByte = setBit(tempByte, i);
			}
		} else {
			if((getBit(pt, i) ^ getBit(prev, 7 - i)) == 1){
				tempByte = setBit(tempByte, i);
			}
		}
		
	}
	
	return tempByte;
}

/*
Function: Encode
Purpose: This function will encode the entire plaintext into an array of encrypted cypher text bytes
in: Array of plaintext, byte of cyphertext, and number of bytes 
out: Encrypted array of cyphertext
*/
void encode(unsigned char *pt, unsigned char* ct, int numBytes){
	unsigned char ctr = CTR;
	unsigned char prev = IV;
	
	for(int i = 0; i < numBytes; i++){
		ctr = processCtr(ctr, KEY);
		
		prev = encryptByte(pt[i], ctr, prev);
		 
		if(pt[i] == '\0'){
			break;
		}
		
		ct[i] = prev;
		ctr++;
	}
}

/*
Function: DecryptByte
Purpose: This function will decrypt a byte of cyphertext into plaintext using the ctr and previous value and it will return the decrypted plaintext byte
in: Byte of cyphertext, previous byte of cyphertext, and the counter value
return: Byte of plaintext that has been decrypted
*/
unsigned char decryptByte(unsigned char ct, unsigned char ctr, unsigned char prev){
	unsigned char tempByte = 0;
	
	for(int i = 0; i < 8; i++){
		if(getBit(ctr, i) == 1){
			if((getBit(ct, i) ^ getBit(prev, i)) == 1){
				tempByte = setBit(tempByte, i);
			}
		} else {
			if((getBit(ct, i) ^ getBit(prev, 7 - i)) == 1){
				tempByte = setBit(tempByte, i);
			}
		}
		
	}
	
	return tempByte;
}

/*
Function: Decode 
Purpose: This function will take an array of cyphertext and decrypt each byte into plaintext
in: The array of encrypted cyphertext, and the number of bytes
out: The decrypted array of plaintext
*/
void decode (unsigned char *ct, unsigned char *pt, int numBytes){
	unsigned char ctr = CTR;
	unsigned char prev = IV;
	
	for(int i = 0; i < numBytes; i++){
		if(i > 0){
			prev = ct[i - 1];
		}
		ctr = processCtr(ctr, KEY);
		
		prev = decryptByte(ct[i], ctr, prev);
		
		if(prev == '\n'){
			break;
		}
		
		pt[i] = prev;
		ctr++;
	}
}
/*
  Function:  getBit
  Purpose:   retrieve value of bit at specified position
       in:   character from which a bit will be returned
       in:   position of bit to be returned
   return:   value of bit n in character c (0 or 1)
*/
unsigned char getBit(unsigned char c, int n)
{
	return ((c & (1 << n)) >> n);
}

/*
  Function:  setBit
  Purpose:   set specified bit to 1
       in:   character in which a bit will be set to 1
       in:   position of bit to be set to 1
   return:   new value of character c with bit n set to 1
*/
unsigned char setBit(unsigned char c, int n)
{
	return (c | (1 << n));
}

/*  Function:  clearBit
  Purpose:   set specified bit to 0
       in:   character in which a bit will be set to 0
       in:   position of bit to be set to 0
   return:   new value of character c with bit n set to 0
*/
unsigned char clearBit(unsigned char c, int n)
{
	return (c & ~(1 << n));
}


