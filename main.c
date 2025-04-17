#include <stdio.h>
#include <stdlib.h>
#include<crtdbg.h>

int Lenght(char const* str) {
	int x = 0;
	while ( str[x]!='\0') {
		x += 1;
	}
	return x;
}

char* Realloc_s(char* arr, int size) {
	char* new_arr = realloc(arr, size * sizeof(char));
	if (new_arr == NULL) {
		free(arr);
		return NULL;
	}
	return new_arr;
}
int IsChar(char s) {
	int x = 0;
	if ((s >= 48 && s <= 57) || (s >= 65 && s <= 90) || (s >= 97 && s <= 122)) {
		x = 1;
	}
	return x;
}
int CountWords(char const* arr,int len) {
	int cnt = 0;
	int x = 0;
	while (x < len) {
		if (IsChar(arr[x]) == 1 && (IsChar(arr[x + 1] )== 0)) {
			cnt++;
		}
		x++;
	}
	return cnt;
}


int WordLenght(char const* str) {
	int x = 0;
	while (IsChar(str[x] )!= 0) {
		x++;
	}
	return x;
}

char* ReadLine(void) {
	char* arr = malloc(sizeof(char));
	if (arr == NULL) return NULL;
	char simb = getchar();
	int cnt = 0;
	while (simb != '\n' && simb!=EOF) {
		arr[cnt] = simb;
		simb = getchar();
		cnt++;
		arr = Realloc_s(arr, (cnt + 1));

	}
	arr[cnt] = '\0';
	return arr;
}


char** Crushing(char* str,int lenght, int cntwords) {
	char** arr = malloc(sizeof(char*)*cntwords);
	if (arr == NULL) return NULL;
	int cnt = 0;
	for (int x = 0; x < lenght; x++) {
		if ((x==0 && IsChar(str[x])==1) || (IsChar(str[x]) == 1 && IsChar(str[x - 1]) == 0)) {
			arr[cnt] =(char*) & str[x];
			cnt += 1;
		}
	}
	return arr;
}

int IsChain(char* x, char* y) {
	int cnt = 0;
	int ca = 0;
	int flag = 1;
	while (flag!=0 && IsChar(*(x+cnt+ca))!=0) {
		if (flag == 1 && ca!=0) {
			cnt++;
			ca = 0;
		}
		while (*(x + cnt) != *y && IsChar(*(x + cnt)) != 0) {
			cnt++;
		}
		while ((*(x + cnt + ca) == *(y + ca))) {
			ca++;
			if (IsChar(*(x + cnt + ca)) == 0) {
				flag = 0;
				break;
			}
			if (*(x + cnt + ca) != *(y + ca)) {
				break;
			}
		}
	}
	if (flag == 1) {
		ca = 0;
	}
	return ca;
}


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	int k = 0;
	while (k == 0) {
		printf("Input : ");
		char* words = ReadLine();
		if (words[0] == '\0'|| words==NULL) {
			free(words);
			k = 1;
			break;
		}
		int cntwords = CountWords(words, Lenght(words));
		char** crwords = Crushing(words, Lenght(words), cntwords);
		if (crwords == NULL) {
			free(words);
			continue;
		}
		char* result = malloc(sizeof(char));
		if (result == NULL) {
			free(words);
			free(crwords);
			continue;
		}
		result[0] = '\0';
		int klen = 0;
		int i = 0;
		for (int x = 0; x < cntwords; x++) {
		    for (int y = 0; y < cntwords; y++) {
				if (x != y) {
					int klen = IsChain(crwords[x], crwords[y]);
					int len1 = WordLenght(crwords[x]);
					int len2 = WordLenght(crwords[y]);

					if (klen >= 2) {
						int k = 0;
						while (k < len1) {
							result = Realloc_s(result, (i + 1));
							if (result == NULL) {
								free(words);
								free(crwords);
								return 1;
							}
							result[i] = ((crwords[x][k]));
							k++;
							i++;

						}
						int u = klen;
						while (u < len2) {
							result = Realloc_s(result, (i + 1));
							if (result == NULL) {
								free(words);
								free(crwords);
								return 1;
							}
							result[i] =((crwords[y] [u]));
							u++;
							i++;
						}
						result = Realloc_s(result,  (i + 3));
						if (result == NULL) {
							free(words);
							free(crwords);
							return 1;
						}
						result[i] = ',';
						result[i + 1] = ' ';
						i += 2;
					}
				}
		    }
		}
		result[i-2] = '\0';
		printf("Result: %s\n", result);
		free(result);
		free(crwords);
		free(words);
	}
}
