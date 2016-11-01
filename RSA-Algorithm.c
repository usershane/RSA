/*
 *    本代码只实现一个简单的RSA加密算法。生成基本的公钥和密钥。 
 *
 * 让我写这个的想法是，在工作中很多人都会使用，用Java PHP C C++ ...
 *
 * 总之有各种各样的语言，但很多使用的人并不明白期中的原理，只有当我们明
 *
 * 白期中的数学原理后，就可以最小化的实现我们自己的加解密算法,所以本节
 *
 * 代码实只体现数学原理，并不考虑实际的应用。
 *
 * ********************************************************************/

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>


typedef struct
{
	int m_nPublic;	// Public key
	int m_nPrivate;	// Private key
	int m_nCircle;	// Circle the number
}SecretKey;


/*
 *  JudgePrimeNumber is a tool function.
 *
 ***********************************************************************/
bool
JudgePrimeNumber( int nNumber )
{
	/*
	 * Function	: To determine whether unNumber is a prime number?
	 * Percondition	: NULL
	 * Postcondition: Is to return true,no return false.
	 * *************************************************************/
	int i = 2;
	while( i < nNumber )
	{
		if( nNumber % i == 0 )
			break;
		i++;
	}
	if( i == nNumber )
		return true;
	else
		return false;
}

int
GenerateRandomNumber( int nMin, int nMax )
{
	/*
	 * Function	: Generate a greater than nMin random number less than nMax.
	 * Percondition	: nMax > nMin; 
	 * Postcondition: Return a random number.
	 * *************************************************************/
	int nRandom, i = nMax - nMin;

	srand( time( 0 ) );
	while( i < nMax ){
		nRandom = rand() % nMax;
		if( nMin < nRandom )
			return nRandom;
		i++;
	}
	return 0;
}

int
GenerateRandomPrimeNumber( int nMin )
{

	/*
	 * Function	: Generate a prime number of random.
	 * Percondition	: 0 < nMin  < 900
	 * Postcondition: Return a random prime number.
	 * *************************************************************/
	int i, nRandom = 0;
	for( i = nMin ; i < 1000; i++ )
		if( JudgePrimeNumber( i ) )
			return i;
	return 0;
}

int
LeastCommonMultiple( int nA,int nB )
{

	/*
	 * Function	: Seek nA and nB common multiple
	 * Percondition	: NULL
	 * Postcondition: Return nA and nB common multiple
	 * *************************************************************/
	int i;
	
	for( i = 1; ; i++ )
		if( i % nA == 0 && i % nB ==0 )
			break;
	return i;
}

int
Gcd( int nx, int ny )
{
	/*
	 * Function 	: Seek nx and ny greatest common divisor.
	 *
	 * ************************************************************/
	if( nx < ny )
		return Gcd( ny, nx );
	if( 0 == ny )
		return nx;
	else
	{
		if( 0 == ( nx % 2 ) )
		{
			if( 0 == ( ny % 2 ) )
				return ( Gcd( nx >> 1,ny >> 1 ) << 1 );
			else
				return Gcd( nx >> 1, ny );

		}
		else
		{
			
			if( 0 == ( ny % 2 ) )
				return Gcd( nx ,ny >> 1 );
			else
				return Gcd( ny, nx - ny );
		}
	}
}

int
GreatestCommonDivisor( int nNumber )
{
	/*
	 * Function	: Generate the Greatest common divisor of 1 and 
	 * 		  nNumber number;
	 * Percondition	: NULL
	 * Postcondition: Return the Greatest common divisor of 1 and
	 * 		  nNumber number;
	 * *************************************************************/
	int nTemp = 0,nRet = 0;
	nTemp = GenerateRandomNumber( 50,100 );
	
	while( nTemp < 200 )
	{
		nRet = Gcd( nTemp, nNumber );
		if( nRet == 1 )
			return nTemp;
		nTemp++;
	}
	return 0;
}

int
IndexCalculate( int nNumber, int nIndex,int nMod )
{
	/*
	 * Function	: nNumber ^ nIndex % nMod
	 * Percondition	: nNumber < nMod
	 * Postcondition: Return nNumber ^ nIndex % nMode is values.
	 * *************************************************************/
	int nt = 1,nTemp = nNumber;
	
	while( nIndex != 0 )
	{
		if( 1 == nIndex % 2 )
			nt = nt * nTemp % nMod;
		nTemp = nTemp * nTemp % nMod;
		nIndex /= 2;
	}
	return nt;
}

/*
 *
 * Use GenerateSecretKey function generate secret key.
 *
 * Use Encryption function encryption express.
 *
 * Use DecryptFuction function decrypt ciphertext.
 *
 * *********************************************************************/

int
Encryption( int nExpress,SecretKey sk)
{
	/*
	 * Function	: Use sk encryption express.
	 * Percondition	: n < 
	 * Postcondition: Return ciphertext.
	 * *************************************************************/
	int nCiphertext = 0;
	nCiphertext = IndexCalculate( nExpress,sk.m_nPublic,sk.m_nCircle);
	return nCiphertext;
}

int
Decrypt( int nCiphertext,SecretKey sk)
{
	/*
	 * Function	: Use sk decrypt ciphertext
	 * Percondition	: 
	 * Postcondition: Return express.
	 * *************************************************************/
	int nExpress = 0;
	nExpress = IndexCalculate( nCiphertext, sk.m_nPrivate, sk.m_nCircle );
	return nExpress;
}

void
PrintKey( SecretKey sk )
{
	/*
	 * Function	: Print secret key
	 *
	 * *************************************************************/
	printf("公钥：%.2d %.2d\n密钥：%.2d %.2d\n ",sk.m_nPublic,\
			sk.m_nCircle, sk.m_nPrivate,sk.m_nCircle);

}

SecretKey
GenerateSecretKey( void )
{
	/*
	 * Function	: Generate public key and private key.
	 * Percondition	: NULL
	 * Postcondition: Return secret key.
	 * *************************************************************/
	int na = 0, nb = 0, nTemp, i = 0;
	SecretKey stKey = {0};

	na = GenerateRandomPrimeNumber( GenerateRandomNumber( 10,50 ) );	
	nb = GenerateRandomPrimeNumber( GenerateRandomNumber( 70,100 ) );

	stKey.m_nCircle = na * nb;

	nTemp = LeastCommonMultiple( na - 1, nb - 1 );
	stKey.m_nPublic = GreatestCommonDivisor( nTemp );

	i = GenerateRandomNumber( 10, 50 );
	while( i++ )
	{
		if( ( stKey.m_nPublic * i ) % nTemp == 1 )
		{
			stKey.m_nPrivate = i;
			break;
		}
	}
	return stKey;
}



/*
 *	main函数中只提供实现实例。
 *
 ***********************************************************************/
int
main(void)
{	
	int nText,nTemp = 0;
	SecretKey stKey = {0};
	stKey = GenerateSecretKey();
	while( stKey.m_nPrivate == stKey.m_nPublic )
		stKey = GenerateSecretKey();
	PrintKey( stKey );
	printf("请输入明文(%d < Number < -%d)：",stKey.m_nCircle - 2, \
			stKey.m_nCircle - 2 );
	scanf("%d",&nTemp);
	nText = Encryption( nTemp, stKey );
	printf(" 密文: %d \n",nText );
	nText = Decrypt( nText, stKey );
	printf(" 明文: %d \n",nText );
	
	return 0;
}
