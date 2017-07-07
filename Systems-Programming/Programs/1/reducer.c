/////////////////////////////////////////////////////////
////////////////////////////////code by Arpita S Tugave
/////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//defines number of rows in the array
enum { MAXLINES = 100 };

//////////////////////////////////////////// Helper funtions

/* appends three strings */
char* stradd(const char* string1, const char* string2, const char* string3){
	size_t len = strlen(string1) + strlen(string2) + strlen(string3);
	char *return_r = (char*)malloc(len * sizeof(char) + 1);
	*return_r = '\0';
	return strcat(strcat(strcat(return_r, string1) ,string2) ,string3);
}

/* converts int to string */
char *itoa (int value, char *result, int base){
	// check for base validity
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
	        tmp_value = value;
	        value /= base;
	        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

	// Negative sign applied
	if (tmp_value < 0) *ptr++ = '-';
		*ptr-- = '\0';
   
	while (ptr1 < ptr) {
	        tmp_char = *ptr;
	        *ptr--= *ptr1;
	        *ptr1++ = tmp_char;
    	}
    	return result;
}

//////////////////////////////////////////// Reducer Function

int main()
{
	int count_name = 0 , j = 0 , i = 0, count = 0 ,count_array;
	char str[50],name[MAXLINES][BUFSIZ], temp[BUFSIZ], arranged_array[MAXLINES][BUFSIZ];

	//read value from stdin for the mapper function
	for( count_name = 0; gets(temp) != NULL; count_name++ ){
		strcpy(name[count_name],temp);
	}

	//count the number of words in the array
	while (i <= count_name-1) {
		count = 1;

		if (i != count_name) {
			for (j = i + 1; j <= count_name; j++) {
				if (strcmp(name[i], name[j]) == 0 ) {
					count++;
					//equate detected string to space character; for not to be detected again
					strcpy(name[j]," ");
				}
			}

		}
		
		if(strcmp(name[i], " ") != 0)
		{
			char snum[2];
			itoa(count, snum, 10);
			//truncate thelast two characters of the string
	       		char *p = name[i];
			p[strlen(p)-2] =  0;

			p = stradd(p,snum,")\n"); //assign key
			strcpy(arranged_array[count_array],p);

			//final value is strored in the arranaged_array
			printf("%s", arranged_array[count_array]);

			count_array++;
		}
		i = i + 1;
	}

   return 0;
}
