/*
 * Using mcrypt and libmcrypt libraries 
 * 
 * Using DES in CBC mode
 * 
 */

#include <assert.h>
#include <mcrypt.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void printBitwise(char []);

int main() 
{
	
	//Initializations
	MCRYPT crh;
	unsigned char *key, *hash;
	unsigned char *encrypted;
	int data_size, max_key_size, iv_size;
	int out;
	char *IV;
	char input[100];
	int keysize, ivsize, block_size;
	
	
	IV = "vdsfsdad";
	
	//String to be encrypted

	printf("Enter the string to be encrypted :\t");
	gets(input);
	encrypted = strdup(input);
	
	
	//Initializing Encryption handler
	crh = mcrypt_module_open(MCRYPT_DES, NULL, MCRYPT_CBC, NULL);
	keysize = mcrypt_enc_get_key_size(crh);//Gets the maximum supported key size of the algorithm in bytes. 

/*

What is an initialization vector?

An initialization vector (IV) is an arbitrary number that can be used along with a secret key for data encryption. This number, also called a nonce, is employed only one time in any session. 

The use of an IV prevents repetition in data encryption, making it more difficult for a hacker using a dictionary attack to find patterns and break a cipher. For example, a sequence might appear twice or more within the body of a message. If there are repeated sequences in encrypted data, an attacker could assume that the corresponding sequences in the message were also identical. The IV prevents the appearance of corresponding duplicate character sequences in the ciphertext. 

The ideal IV is a random number that is made known to the destination computer to facilitate decryption of the data when it is received. The IV can be agreed on in advance, transmitted independently or included as part of the session setup prior to exchange of the message data. The length of the IV (the number of bits or bytes it contains) depends on the method of encryption. The IV length is usually comparable to the length of the encryption key or block of the cipher in use.

*/


	ivsize = mcrypt_enc_get_iv_size(crh);//This function returns the size of the IV of the algorithm specified by the encryption descriptor in bytes. An IV is used in cbc, cfb and ofb modes, and in some algorithms in stream mode. 

	block_size = mcrypt_enc_get_block_size(crh);// Returns the block size of the specified algorithm in bytes. 
	
	data_size = ((int)(strlen(encrypted)/(float)block_size)+1)*block_size;
	
	assert(strlen(IV)<=ivsize);
	
	key = "keyforec";
	//data_size=strlen(encrypted);
	

	//Encryption starts
	mcrypt_generic_init(crh, key, keysize, IV);//The function returns a negative value on error: -3 when the key length was incorrect, -4 when there was a memory allocation problem and any other return value is an unknown error. If an error occurs a warning will be displayed accordingly. FALSE is returned if incorrect parameters were passed. 

	printf("Original String :\t\t\t%s\n", encrypted);


	out = mcrypt_generic(crh, encrypted, data_size);//This function encrypts data. The data is padded with "\0" to make sure the length of the data is n * blocksize. This function returns the encrypted data. Note that the length of the returned string can in fact be longer than the input, due to the padding of the data. 


	printf("Encrypted String :\t\t\t%s\nBitwise Representation :\t\t", encrypted);

	printBitwise(encrypted);

	mcrypt_generic_deinit(crh);
	//Encryption ends
	
	//Decryption starts
	mcrypt_generic_init(crh, key, keysize, IV);//This function terminates encryption specified by the encryption descriptor (td). It clears all buffers, but does not close the module. You need to call mcrypt_module_close() yourself. 


	out = mdecrypt_generic(crh, encrypted, data_size);//This function decrypts data. Note that the length of the returned string can in fact be longer than the unencrypted string, due to the padding of the data. 

	printf("Retrieved String :\t\t\t%s\nBitwise Representation:\t\t\t", encrypted);
	printBitwise(encrypted);
	
	mcrypt_generic_deinit(crh);	
	//Decryption ends
	
	//Deleting encryption handler
	mcrypt_module_close(crh);
	
	return 0;
}

void printBitwise(char a[])
{
	int i;
	for(i=0; a[i]!='\0'; i++)
	{
		printf("%x ",(int)a[i]);
	}
	printf("\n");
}
