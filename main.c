#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>
#include <errno.h>

extern int errno;

int main(int argc, char **argv)
{
	regex_t regex;
	regmatch_t group[8];
	int ret;
	char *expr = NULL;
	char *str = NULL;
	size_t expr_len = 0;
	size_t str_len = 0;


	if(argc < 3) {
		fprintf(stderr, "usage: regx <regex> <string>\n");
		return 0;
	}

	expr_len = snprintf(NULL, 0, "%s", argv[1]) + 1;
	str_len = snprintf(NULL, 0, "%s", argv[2]) + 1;

	expr = calloc(expr_len, sizeof(char));
	str = calloc(str_len, sizeof(char));

	if(expr == NULL) {
		fprintf(stderr, "%s\n", strerror(errno));
		exit(errno);
	}
	if(str == NULL) {
		fprintf(stderr, "%s\n", strerror(errno));
		exit(errno);
	}

	snprintf(expr, expr_len, "%s", argv[1]);
	snprintf(str, str_len, "%s", argv[2]);

	printf("%s %s\n", expr, str);

	/* compile regular expression */
	ret = regcomp(&regex, expr, REG_EXTENDED);

	if(ret != 0)  {
		fprintf(stderr, "could not compile regex, error: %d\n", ret);
		exit(1);
	}


	/* execute regular expression */
	ret = regexec(&regex, str, 4 ,group, 0);
	if(ret == REG_NOMATCH) {
		fprintf(stderr, "No match\n");
	}

	else if(ret == 0) {
		for(int i = 0; i < 4; i++) {
			/* no more groups */
			if(group[i].rm_so == -1) {
				break;
			}

			char copy[strlen(str) + 1];

			strcpy(copy, str);
			copy[group[i].rm_eo] = 0;

			printf("group: %u: [%2u-%2u]: %s\n", i, group[i].rm_so, group[i].rm_eo,
				copy + group[i].rm_so);
		}
	}

	else {
		fprintf(stderr, "Regex match failed");
	}
	
	free(expr);
	free(str);
	regfree(&regex);

	return 0;
}
