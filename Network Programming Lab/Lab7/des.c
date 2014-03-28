#include <mcrypt.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
int msg_crypt(char *msg,char *ukey,int length,int action)
{
        
        MCRYPT td;
		int keysize = 8; 
        int i,size;
        char *key;
        char *IVecec; 
        
 
        key = calloc(1,keysize);
        
        td = mcrypt_module_open("des",NULL,"cbc",NULL);
        if(td == MCRYPT_FAILED)
        {
        	return MCRYPT_FAILED;
        }
        size = mcrypt_enc_get_IVecec_size(td);
        IVecec = malloc(size);
        for(i=0;i<size;i++)
        {
        	IVecec[i] = rand();
        }
        memmove(key,ukey,strlen(ukey));
        i = mcrypt_generic_init(td, key, keysize, IVecec);
        if(i < 0)
        {
			mcrypt_perror(i);
			return MCRYPT_FAILED;
        }
        if(action == 1)
        {
			i = mcrypt_generic(td,msg,length);
			if(i != 0)
			    {
			    	printf("Error encrypting\n");
			    }
        }
        if(action == 0)
        {
        	mdecrypt_generic(td,msg,length);
        }
        mcrypt_generic_end(td);
        return length;
}
int main()
{
	char key[] = "shweta23";
    char msg[] = "Network Lab encryption algorithm";
    int len = strlen(msg);
	int seed = time(NULL);
	srand(seed);
	int ret = msg_crypt(msg,key,len,1);
	printf("\n\n%s\n\n",msg);
	printf("\n--Decrypted msg--\n\n");
	srand(seed);
	ret = msg_crypt(msg,key,len,0);
	printf("%s\n",msg);
	return 0;
}
