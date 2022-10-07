//////////////////////////////////////////////////////
// Classe de cryptage Base64 aléatoire
// By Aurélien BOUDOUX.
//////////////////////////////////////////////////////

#include <windows.h>
#include <stdio.h>

#define PCRYPT_LEN 65500

const char BaseTable[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

class CB64crypt  
{

public :

	// constuction
	CB64crypt  () 
	{ 
		this->pCrypt = new char [PCRYPT_LEN];
		RtlZeroMemory( this->pCrypt, PCRYPT_LEN );
	}

	// destruction
	~CB64crypt  ()
	{
		delete[] this->pCrypt;
	}


//////////////////////////////////////////////////////////////////////
// Fonction de decryptage proprietaire, le resultat est placé
// dans this->pCrypt
//////////////////////////////////////////////////////////////////////
BOOL DeCrypt(char *data)
{
    unsigned char key;
    int i=0, bufsize;
    unsigned char binbyte[4];
    int cpos[5]; 
    char *p;

	memset( this->pCrypt, 0, PCRYPT_LEN );

	if( (p = strrchr( data, '-')) )
		*p = 0x00;
	else
		return FALSE;

    key = (unsigned char)atoi( ++p );

    ModifTable( key );

    bufsize = strlen( data );
    unsigned char * buftemp = new unsigned char[ (bufsize * 2) + 5 ];
    memset( buftemp, 0, (bufsize * 2) + 5 );

    lstrcpyn( (char *)buftemp, data, strlen (data)+1 );

    while( i<bufsize ) 
	{ 
       cpos[0]                 = strchr( this->Base64Table, buftemp[i]   ) - Base64Table; 
       cpos[1]                 = strchr( this->Base64Table, buftemp[i+1] ) - Base64Table; 
       cpos[2]                 = strchr( this->Base64Table, buftemp[i+2] ) - Base64Table; 
       cpos[3]                 = strchr( this->Base64Table, buftemp[i+3] ) - Base64Table; 
       
       binbyte[0]              = ( (cpos[0] << 2 ) |(cpos[1] >> 4 ) ); 
       binbyte[1]              = ( (cpos[1] << 4 ) |(cpos[2] >> 2 ) ); 
       binbyte[2]              = ( ( (cpos[2] & 0x03 ) << 6 ) | (cpos[3] & 0x3f) ); 

       this->pCrypt[i-(i/4)]   = (unsigned char)binbyte[0]; 
       this->pCrypt[i-(i/4)+1] = (unsigned char)binbyte[1]; 
       this->pCrypt[i-(i/4)+2] = (unsigned char)binbyte[2]; 
       i+=4; 
	}

    delete buftemp;
    return TRUE;

}

//////////////////////////////////////////////////////////////////////
// Fonction de cryptage proprietaire, le resultat est placé
// dans this->pCrypt
//////////////////////////////////////////////////////////////////////
void Crypt(char *data)
{
    SYSTEMTIME systime;
    unsigned char key;
	
    int i=0, bufsize; 
    unsigned char b64byte[5]; 

    // genere une cle
	GetLocalTime( &systime );
	key = (unsigned char)systime.wMilliseconds / 12;
	
	// modifie la table de hash selon la cle
	ModifTable( key );

    bufsize = strlen( data );

    //Allocate space for the temporary string 
	unsigned char * buftemp = new unsigned char[ (bufsize * 2) + 5 ];
	memset( buftemp, 0,(bufsize * 2) + 5 );

	memset( this->pCrypt, 0 ,PCRYPT_LEN );

	lstrcpyn( (char *)buftemp, data, bufsize+1 );
   
    while( i < bufsize ) 
	{ 
       b64byte[0]              = buftemp[i] >> 2; 
       b64byte[1]              = ( (buftemp[i] & 3 ) << 4 )     | (buftemp[i+1] >> 4 ); 
       b64byte[2]              = ( (buftemp[i+1] & 0x0F) << 2 ) | (buftemp[i+2] >> 6 ); 
       b64byte[3]              = buftemp[i+2] & 0x3F; 

       this->pCrypt[i+(i/3)]   = (unsigned char)this->Base64Table[b64byte[0]]; 
       this->pCrypt[i+(i/3)+1] = (unsigned char)this->Base64Table[b64byte[1]]; 
       this->pCrypt[i+(i/3)+2] = (unsigned char)this->Base64Table[b64byte[2]]; 
       this->pCrypt[i+(i/3)+3] = (unsigned char)this->Base64Table[b64byte[3]]; 

       i+=3; 
	} 
	
	sprintf( this->pCrypt,"%s-%u\x00", this->pCrypt, key );

    delete buftemp;

}

	// variable publique
	char * pCrypt;
	
private :

	char Base64Table[65];
	/*#################################################
	fonctions necessaire a la rotation de la table 64
	##################################################*/
	void swap( char *a, char *b )
	{
		char temp = *a;
		*a = *b;
		*b = temp;	
	}
	/////////////////////////////////////////////////////
	void ModifTable( unsigned char key )
	{
		unsigned int i;
		
		lstrcpy( Base64Table, BaseTable );

		for (i=0; i < 64; i++)
		{
			while( i+key < 63 )
				this->swap( &Base64Table[i+key],&Base64Table[i++] );				
		}

	}

};