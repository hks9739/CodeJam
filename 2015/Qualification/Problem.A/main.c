#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#define LINE_MAX	4096
#define TOKEN_MAX	16


#define ERROR_EXIT(fmt, args...)	do{ fprintf(stderr, fmt, ##args); exit(-1); } while(0)
#define CHECK_ERROR_EXIT(condition, fmt, args...)	\
	do{ if(condition) ERROR_EXIT(fmt, ##args); } while(0)
	

#ifdef DEBUG
#define LOG_DEBUG(fmt, args...)		printf(fmt, ##args)
#else
#define LOG_DEBUG(fmt, args...)		do{}while(0)	
#endif

#define OUTPUT(fmt, args...)		fprintf(output_stream, fmt, ##args)


static FILE *output_stream;

static char line[LINE_MAX];
static int get_next_line_tokens(FILE *in_file, char **token, int max)
{
	const char *sep = " \t\r\n";
	char *s, *lasts;
	int idx = 0;

	if(fgets(line, LINE_MAX, in_file) == NULL) return -1;

	for(s=strtok_r(line, sep, &lasts); s; s=strtok_r(NULL, sep, &lasts))
	{
		token[idx++] = s;
		if(idx >= max) break;
	}

	return idx;
}

static int process(FILE *in_file)
{
	char *token[TOKEN_MAX];
	int i,T, num, s_max;
	char *str_persons;
	int num_person;

	if(get_next_line_tokens(in_file, token, TOKEN_MAX) != 1) ERROR_EXIT("invalid 1st line format\n");
	
	T = strtoul(token[0], NULL, 0);
	if(T < 1 || T > 100) ERROR_EXIT("T(%d) invalid\n", T);
	
	LOG_DEBUG("T=%d\n", T);
	for(num=1; num<=T; num++)
	{
		int num_friends = 0;
		int standup_persons = 0;
		
		if(get_next_line_tokens(in_file, token, TOKEN_MAX) != 2) ERROR_EXIT("invalid input format - line[%d]\n", num);
		
		s_max = strtoul(token[0], NULL, 0);
		str_persons = token[1];

		if((s_max+1) != strlen(str_persons)) ERROR_EXIT("Smax(%d)+1 != PersonCount(%d)\n", s_max, (int)strlen(str_persons));
		
		for(i=0; i<=s_max; i++)
		{
			num_person = str_persons[i] - '0';
			if(i > standup_persons)
			{
				num_friends += (i - standup_persons);
				standup_persons = i;
			}
			
			standup_persons += num_person;
		}
		
		LOG_DEBUG("Smax=%d Persons=%s\n", s_max, str_persons);
		
		OUTPUT("Case #%d: %d\n", num, num_friends);
	}

	return 0;	
}


int main(int argc, char **argv)
{
	int rc;
	FILE *in_file, *out_file;
	
	CHECK_ERROR_EXIT(argc != 2 && argc != 3, "%s input [output]\n", basename(argv[0]));

	in_file = fopen(argv[1], "rb");
	CHECK_ERROR_EXIT(!in_file, "can't open file %s - %s\n", argv[1], strerror(errno));
	
	if(argc == 3)
	{
		out_file = fopen(argv[2], "wb");
		CHECK_ERROR_EXIT(!out_file, "can't open file %s - %s\n", argv[1], strerror(errno));
		
		output_stream = out_file;
	}
	else
	{
		out_file = NULL;
		output_stream = stdout;
	}
	
	rc = process(in_file);
	
	fclose(in_file);
	if(out_file) fclose(out_file);

	return rc;	
}
