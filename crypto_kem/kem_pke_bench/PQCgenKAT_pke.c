/*
NIST-developed software is provided by NIST as a public service. You may use, copy, and distribute copies of the software in any medium, provided that you keep intact this entire notice. You may improve, modify, and create derivative works of the software or any portion of the software, and you may copy and distribute such modifications or works. Modified works should carry a notice stating that you changed the software and should note the date and nature of any such change. Please explicitly acknowledge the National Institute of Standards and Technology as the source of the software.
 
NIST-developed software is expressly provided "AS IS." NIST MAKES NO WARRANTY OF ANY KIND, EXPRESS, IMPLIED, IN FACT, OR ARISING BY OPERATION OF LAW, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND DATA ACCURACY. NIST NEITHER REPRESENTS NOR WARRANTS THAT THE OPERATION OF THE SOFTWARE WILL BE UNINTERRUPTED OR ERROR-FREE, OR THAT ANY DEFECTS WILL BE CORRECTED. NIST DOES NOT WARRANT OR MAKE ANY REPRESENTATIONS REGARDING THE USE OF THE SOFTWARE OR THE RESULTS THEREOF, INCLUDING BUT NOT LIMITED TO THE CORRECTNESS, ACCURACY, RELIABILITY, OR USEFULNESS OF THE SOFTWARE.
 
You are solely responsible for determining the appropriateness of using and distributing the software and you assume all risks associated with its use, including but not limited to the risks and costs of program errors, compliance with applicable laws, damage to or loss of data, programs or equipment, and the unavailability or interruption of operation. This software is not intended to be used in any situation where a failure could cause risk of injury or damage to property. The software developed by NIST employees is not subject to copyright protection within the United States.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../common/rng.h"
#include "api.h"

#define	MAX_MARKER_LEN		50

#define KAT_SUCCESS          0
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR      -3
#define KAT_CRYPTO_FAILURE  -4

int		FindMarker(FILE *infile, const char *marker);
int		ReadHex(FILE *infile, unsigned char *A, int Length, char *str);
void	fprintBstr(FILE *fp, char *S, unsigned char *A, unsigned long long L);

int
main()
{
    char                fn_req[32], fn_rsp[32];
    FILE                *fp_req, *fp_rsp;
    unsigned char       seed[48];
    unsigned char       msg[CRYPTO_MAXPLAINTEXT];
    unsigned char       entropy_input[48];
    unsigned char       *m, *c, *m1;
    unsigned long long  mlen, clen, mlen1;
    int                 count;
    int                 done;
    unsigned char       pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES];
    int                 ret_val;
    
    // Create the REQUEST file
    sprintf(fn_req, "PQCencryptKAT_%d.req", CRYPTO_SECRETKEYBYTES);
    if ( (fp_req = fopen(fn_req, "w")) == NULL ) {
        printf("Couldn't open <%s> for write\n", fn_req);
        return KAT_FILE_OPEN_ERROR;
    }
    sprintf(fn_rsp, "PQCencryptKAT_%d.rsp", CRYPTO_SECRETKEYBYTES);
    if ( (fp_rsp = fopen(fn_rsp, "w")) == NULL ) {
        printf("Couldn't open <%s> for write\n", fn_rsp);
        return KAT_FILE_OPEN_ERROR;
    }
    
    for (int i=0; i<48; i++)
        entropy_input[i] = i;

    randombytes_init(entropy_input, NULL, 256);
    for (int i=0; i<3; i++) {
        for (int j=0; j<25; j++) {
            fprintf(fp_req, "count = %d\n", i*25+j);
            randombytes(seed, 48);
            fprintBstr(fp_req, "seed = ", seed, 48);
            mlen = 16+i*8;
            fprintf(fp_req, "mlen = %lld\n", mlen);
            randombytes(msg, mlen);
            fprintBstr(fp_req, "msg = ", msg, mlen);
            fprintf(fp_req, "pk =\n");
            fprintf(fp_req, "sk =\n");
            fprintf(fp_req, "clen =\n");
            fprintf(fp_req, "c =\n\n");
        }
    }
    fclose(fp_req);
    
    //Create the RESPONSE file based on what's in the REQUEST file
    if ( (fp_req = fopen(fn_req, "r")) == NULL ) {
        printf("Couldn't open <%s> for read\n", fn_req);
        return KAT_FILE_OPEN_ERROR;
    }
    
    fprintf(fp_rsp, "# %s\n\n", CRYPTO_ALGNAME);
    done = 0;
    do {
        if ( FindMarker(fp_req, "count = ") )
            fscanf(fp_req, "%d", &count);
        else {
            done = 1;
            break;
        }
        fprintf(fp_rsp, "count = %d\n", count);
        
        if ( !ReadHex(fp_req, seed, 48, "seed = ") ) {
            printf("ERROR: unable to read 'seed' from <%s>\n", fn_req);
            return KAT_DATA_ERROR;
        }
        fprintBstr(fp_rsp, "seed = ", seed, 48);
        
        randombytes_init(seed, NULL, 256);
        
        if ( FindMarker(fp_req, "mlen = ") )
            fscanf(fp_req, "%llu", &mlen);
        else {
            printf("ERROR: unable to read 'mlen' from <%s>\n", fn_req);
            return KAT_DATA_ERROR;
        }
        fprintf(fp_rsp, "mlen = %llu\n", mlen);
        
        m = (unsigned char *)calloc(CRYPTO_MAXPLAINTEXT, sizeof(unsigned char));
        m1 = (unsigned char *)calloc(CRYPTO_MAXPLAINTEXT, sizeof(unsigned char));
        c = (unsigned char *)calloc(CRYPTO_CIPHERTEXTBYTES, sizeof(unsigned char));
        
        if ( !ReadHex(fp_req, m, (int)mlen, "msg = ") ) {
            printf("ERROR: unable to read 'msg' from <%s>\n", fn_req);
            return KAT_DATA_ERROR;
        }
        fprintBstr(fp_rsp, "msg = ", m, mlen);
        
        // Generate the public/private keypair
        if ( (ret_val = crypto_encrypt_keypair(pk, sk)) != 0) {
            printf("crypto_encrypt_keypair returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }
        fprintBstr(fp_rsp, "pk = ", pk, CRYPTO_PUBLICKEYBYTES);
        fprintBstr(fp_rsp, "sk = ", sk, CRYPTO_SECRETKEYBYTES);
        
        if ( (ret_val = crypto_encrypt(c, &clen, m, mlen, pk)) != 0) {
            printf("crypto_encrypt returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }
        fprintf(fp_rsp, "clen = %llu\n", clen);
        fprintBstr(fp_rsp, "c = ", c, clen);
        fprintf(fp_rsp, "\n");
        
        if ( (ret_val = crypto_encrypt_open(m1, &mlen1, c, clen, sk)) != 0) {
            printf("crypto_encrypt_open returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }
        
        
        if ( mlen != mlen1 ) {
            printf("crypto_encrypt_open returned bad 'mlen': Got <%llu>, expected <%llu>\n", mlen1, mlen);
            return KAT_CRYPTO_FAILURE;
        }
        
        if ( memcmp(m, m1, mlen) ) {
            printf("crypto_encrypt_open returned bad 'm' value\n");
            return KAT_CRYPTO_FAILURE;
        }
        
        free(m);
        free(m1);
        free(c);

    } while ( !done );
    
    fclose(fp_req);
    fclose(fp_rsp);

    return KAT_SUCCESS;
}

//
// ALLOW TO READ HEXADECIMAL ENTRY (KEYS, DATA, TEXT, etc.)
//
//
// ALLOW TO READ HEXADECIMAL ENTRY (KEYS, DATA, TEXT, etc.)
//
int
FindMarker(FILE *infile, const char *marker)
{
	char	line[MAX_MARKER_LEN];
	int		i, len;
	int curr_line;

	len = (int)strlen(marker);
	if ( len > MAX_MARKER_LEN-1 )
		len = MAX_MARKER_LEN-1;

	for ( i=0; i<len; i++ )
	  {
	    curr_line = fgetc(infile);
	    line[i] = curr_line;
	    if (curr_line == EOF )
	      return 0;
	  }
	line[len] = '\0';

	while ( 1 ) {
		if ( !strncmp(line, marker, len) )
			return 1;

		for ( i=0; i<len-1; i++ )
			line[i] = line[i+1];
		curr_line = fgetc(infile);
		line[len-1] = curr_line;
		if (curr_line == EOF )
		    return 0;
		line[len] = '\0';
	}

	// shouldn't get here
	return 0;
}

//
// ALLOW TO READ HEXADECIMAL ENTRY (KEYS, DATA, TEXT, etc.)
//
int
ReadHex(FILE *infile, unsigned char *A, int Length, char *str)
{
	int			i, ch, started;
	unsigned char	ich;

	if ( Length == 0 ) {
		A[0] = 0x00;
		return 1;
	}
	memset(A, 0x00, Length);
	started = 0;
	if ( FindMarker(infile, str) )
		while ( (ch = fgetc(infile)) != EOF ) {
			if ( !isxdigit(ch) ) {
				if ( !started ) {
					if ( ch == '\n' )
						break;
					else
						continue;
				}
				else
					break;
			}
			started = 1;
			if ( (ch >= '0') && (ch <= '9') )
				ich = ch - '0';
			else if ( (ch >= 'A') && (ch <= 'F') )
				ich = ch - 'A' + 10;
			else if ( (ch >= 'a') && (ch <= 'f') )
				ich = ch - 'a' + 10;
            else // shouldn't ever get here
                ich = 0;
			
			for ( i=0; i<Length-1; i++ )
				A[i] = (A[i] << 4) | (A[i+1] >> 4);
			A[Length-1] = (A[Length-1] << 4) | ich;
		}
	else
		return 0;

	return 1;
}

void
fprintBstr(FILE *fp, char *S, unsigned char *A, unsigned long long L)
{
	unsigned long long  i;

	fprintf(fp, "%s", S);

	for ( i=0; i<L; i++ )
		fprintf(fp, "%02X", A[i]);

	if ( L == 0 )
		fprintf(fp, "00");

	fprintf(fp, "\n");
}

