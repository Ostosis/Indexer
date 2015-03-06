#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ftw.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include "hashmap.h"

struct Token
{

	char * str;
	CompareFuncT cf;

};
typedef struct Token * Token_p;

void indexLocalToken(Token_p token, HashMap_p hm)
{
	int * count;
	if (containsKey(hm, token->str, token->cf))
	{
		count = get(hm, token->str);
		*count = *count + 1;
		free(token->str);
		free(token);
	}
	else
	{

		count = calloc(1, sizeof(int));
		*count = 1;
		put(hm, token->str, count);
	}

}

Token_p newToken(int len)
{

	Token_p token = calloc(1, sizeof(struct Token));
	token->str = calloc(1, len + 1);
	token->cf = (CompareFuncT) strcmp;

	return token;

}

void indexFile(char * str, const char *fpath, int file_Size)
{

	int start = 0, end = 0;
	int inToken = 0;
	HashMap_p hm = newHashMap();
	for (int i = 0; i < file_Size; i++)
	{
		if (inToken)
		{
			if (isalnum(str[i]))
			{
				end++;
				continue;
			}
			else
			{
				int len = end - start + 1;

				Token_p token = newToken(len);
				memcpy(token, str + start, len);

				indexLocalToken(token, hm);
			}
			continue;
		}

		if (isalpha(str[i]))
		{
			start = end = i;
			inToken = 1;
		}

	}

}

int parsePath(const char *fpath, const struct stat *sb, int flag)
{

	struct stat file_stat;

	if (stat(fpath, &file_stat) < 0)
	{
		printf("client: stat of %s failed \n", fpath);
		return -1;
	}

	if (!(file_stat.st_mode & __S_IFREG))
	{
		return 0; // path is not a file

	}
	int file_size = file_stat.st_size + 1;
	char * str = calloc(1, file_size);

	int fd = open(fpath, 0);

	if (fd < 0)
	{
		return 0;

	}

	read(fd, str, file_size);

	printf("%s\n", str);

	indexFile(str, fpath, file_size);

	free(str);
	close(fd);
	return 0;

}

void usage()
{
	printf("Usage: index <inverted-index file name> <directory or file name>\n");
}

int main(int argc, char ** argv)
{

	puts("hello\n");

	char * output_file_name, *directory;
	if (argc != 3)
	{

		usage();
		return EXIT_FAILURE;

	}
	directory = argv[2];

	if (ftw(directory, (__ftw_func_t) parsePath, 0) == -1)
	{
		puts("Could not read directory/file.\n");

	}

	output_file_name = argv[1];

	return 0;
}
