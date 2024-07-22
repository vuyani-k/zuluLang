#include "lexer.h"

int lex(FILE *fp, struct token *tokens){ 

	return tokenize(fp, tokens);
}

int tokenize(FILE *fp, struct token *tokens){

	printf("processing tokens...\n\n");

	//TODO: temp solution, allocating const space for a 
	//word is insufficient, small words will waste 
	//extra allocated memory!
	char *word;
	word = malloc(sizeof(char) * MAX_WORD);

	if(word == NULL)
		lex_error("failed to load token into memory", 
				sys_err, fp, word);

	if(fp == NULL)
		lex_error("failed to load source file", 
				sys_err, fp, word);

	if(fseek(fp, 0, SEEK_SET) != 0)
		lex_error("error reading source file"
				, sys_err, fp, word);

	char f;
	int char_count = 0 ;
	int charCount = 0, digitCount = 0;
	struct token t;

	while((f = fgetc(fp)) != EOF){

		if(isalpha(f)){
			/** WORDS **/
			if((char_count++) >= MAX_WORD){
				lex_error("identifier too long", 
						syn_err, fp, word);
			}
			*word++ = f;
			continue;
		}

		//add word token to tokens array and reset word pointer
		if(char_count > 0){

			*word = '\0';

			//take pointer back to first byte in block 
			//so word can be read from the beginning
			word -= char_count;

			strcpy(t.tk, word);

			if(strcmp(word, "buyisa") == 0){
				t.type = RETURN;
				print_tokens("token: RETURN \n");
			}else{
				t.type = IDEN;
				//adding 3 as an extra buffer for spaces
				char print_tk[sizeof("token:")
				       	+ sizeof(word) + 3];
				strcpy(print_tk, "token: ");
				print_tokens(strcat(print_tk, word));
			}

			*tokens++ = t;

			t.tk[0] = '\0';

			char_count = 0;

		}

		/** NUMBERS **/
		/**
		if(isdigit(f)){
			continue;
		}
		**/

		if(isdigit(f)){

			print_tokens("token: NUMBER \n");

			t.type = INT;

			//TODO change the 15 to represent the max int value
			//also the the token max is 15, so maybe look into 
			//storing it in a different array
			//accepting short ints for now
			snprintf(t.tk, MAX_WORD, "%c", f);
			*tokens++ = t;

			t.tk[0] = '\0';

			continue;
		}

		switch(f){
			case '(':
				/** OPEN PAREN**/

				print_tokens("token: OPEN PAREN \n");

				t.type = OPEN_PAREN;

				*tokens++ = t;

				break;
			case ')':
				/** CLOSE PARENS**/

				print_tokens("token: CLOSE PAREN \n");

				t.type = CLOSE_PAREN;

				*tokens++ = t;

				break;
			case ':':
				/** COLON **/

				print_tokens("token: COLON \n");

				t.type = COLON;

				*tokens++ = t;

				break;
			case ';':
				/** SEMI COLON **/

				print_tokens("token: SEMI COLON \n");

				t.type = SEMI_COLON;

				*tokens++ = t;

				break;
			case '[':
				/** OPEN BRACKETS **/

				print_tokens("token: OPEN BRACKETS\n");

				t.type = OPEN_BRACKETS;

				*tokens++ = t;

				break;
			case ']':
				/** CLOSE BRACKETS **/

				print_tokens("token: CLOSE BRACKETS\n");

				t.type = CLOSE_BRACKETS;

				*tokens++ = t;

				break;
			case '{':
				/** OPEN BRACES **/

				print_tokens("token: OPEN BRACES\n");

				t.type = OPEN_BRACES;

				*tokens++ = t;

				break;
			case '}':
				/** CLOSE BRACES **/

				print_tokens("token: CLOSE BRACES\n");

				t.type = CLOSE_BRACES;

				*tokens++ = t;

				break;
			case '/':
				/** DIVISION **/

				print_tokens("token: DIVISION \n");

				t.type = DIVISION;

				*tokens++ = t;

				break;
			case '*':
				/** ASTERISKS **/

				print_tokens("token: ASTERISKS \n");

				t.type = ASTS;

				*tokens++ = t;

				break;
			case '-':
				/** MINUS **/

				print_tokens("token: MINUS\n");

				t.type = MINUS;

				*tokens++ = t;

				break;
			case '+':
				/** ADDITION **/

				print_tokens("token: ADDITION\n");

				t.type = PLUS;

				*tokens++ = t;

				break;
			case '%':
				/** MODULUS**/

				print_tokens("token: MODULUS\n");

				t.type = MOD;

				*tokens++ = t;

				break;
			case '"':
				/** DOUBLE QUOTES **/

				print_tokens("token: QUOTES\n");

				t.type = QUOTES;

				*tokens++ = t;

				break;
			case '\'':
				/** SINGLE QUOTES**/

				print_tokens("token: SINGLE QUOTES\n");

				t.type = SINGLE_QUOTES;

				*tokens++ = t;

				break;
			case '\t':
				/** TAB SPACE **/

				print_tokens("token: TAB\n");

				t.type = TAB;

				*tokens++ = t;

				break;
			case ' ': case '\n':
				/** WHITE SPACE **/


				/**
				  print_tokens("token: WHITE SPACE\n");

				  t.type = WHITESPACE;

				 *tokens++ = t;

				 **/
				break;
		}

	}

	free(word);

	return 1;

}

int get_no_of_tokens(FILE *fp){

	if(fp == NULL)
		error("failed to load source file", 1);

	if(fseek(fp, 0, SEEK_SET) != 0)
		error("error reading source file", 1);

	char f;
	int char_count = 0;
	int tokens_count = 0;

	while((f = fgetc(fp)) != EOF){

		if(isalpha(f)){

			/** WORDS **/
			if((char_count++) >= MAX_WORD){
				error("identifier too long", 2);
			}
		}else{

			//add word token to tokens list and reset word
			if(char_count > 0){
				tokens_count++;
			}

			char_count = 0;
		}

		switch(f){
			case '(':
			case ')':
			case ':':
			case '[':
			case ']':
			case '{':
			case '}':
			case '/':
			case '*':
			case '-':
			case '+':
			case '%':
			case '"':
			case '\'':
				//case ' ': 
			case '\n':
			case '\t':
				/** TAB SPACE **/
				tokens_count++;
				break;

		}

	}

	//reset pointer to beginning of file, so it can be read again by the lexer
	fseek(fp, 0, SEEK_SET);	

	printf("found %d tokens \n\n", tokens_count);

	//+1 for EOF
	return tokens_count + 1;

}

void error(char *msg, enum err_t err){
	printf("COMPILATION ERROR: .. %s \n\n", msg);
	exit(1);
}

void lex_error(char *msg, enum err_t err, FILE *fp, char *token){
	printf("COMPILATION ERROR: .. %s \n\n", msg);
	fclose(fp);
	free(token);
	exit(1);
}
void print_tokens(char* tk){
	//printf("%s \n", tk);
}

