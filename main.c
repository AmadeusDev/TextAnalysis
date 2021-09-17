#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct WORD
{
	char was;
	char*w;
	int cnt;
	int amo;
};

char flag = 0;
int l,t;

char znak(char *c) {
	if (*c >= '0' && *c <= '9' )
	{
		return 1;
	}
	else if (*c >= 'a' && *c <= 'z')
	{
		return 1;
	}
	else if (*c >= 'A' && *c <= 'Z')
	{
		return 1;
	}
	else if (*c == '_' || *c == '-' || *c == '`')
	{
		return 1;
	}
	
	return 0;
}

char abeceda(struct WORD *first, struct WORD *second) {
	int length = first->cnt < second->cnt ? first->cnt : second->cnt;
	for (int i = 0; i < length; i++)
	{
		if (first->w[i]<second->w[i])
		{
			return 1;
		}
		else if (first->w[i]>second->w[i])
		{
			return 0;
		}
	}
	return 0;
}

void vypis_slovo(struct WORD *w)
{
	char *gl = malloc(22);
	for (int a = 0; a < 22; a++)
		gl[a] = ' ';
	if (flag & 4)
	{
		if (l == w->cnt - 1)
		{
			gl[21 - w->cnt] = 0;
			printf("%s %s%d\n", w->w, gl, w->amo);
			gl[21 - w->cnt] = ' ';
		}
	}
	else
	{
		gl[21 - w->cnt] = 0;
		printf("%s %s%d\n", w->w, gl, w->amo);
		gl[21 - w->cnt] = ' ';
	}
	free(gl);
}

char test(struct WORD *w)
{

	if (flag & 4)
	{
		if (l == w->cnt - 1)
			return 1;
		return 0;
	}
	else
		return 1;
}

int vypis(struct WORD**words, int cnt)
{
	int ammo = 0;
	int L;
	if (flag&4)
	{
		L = l;
		if (L > cnt)
		{
			L = cnt;
		}
	}
	else
	{
		L = cnt;
	}

	if (flag & 2)
	{
		if (t == 1)
		{
			struct WORD*words2 = malloc(sizeof(struct WORD)*cnt);
			for (int i = 0; i < cnt; i++)
			{
				struct WORD *highest = 0;
				for (int i = 0; i < cnt; i++)
				{
					if (highest == 0)
					{
						if ((*words)[i].was == 1)
							continue;
						else
							highest = &(*words)[i];
					}
					else if ((*words)[i].amo < highest->amo && (*words)[i].was == 0)
					{
						highest = &(*words)[i];
					}
				}
				ammo += test(&(*words)[i]);
				words2[i].amo = highest->amo;
				words2[i].w = highest->w;
				words2[i].cnt = highest->cnt;
				words2[i].was = highest->was;
				highest->was = 1;
			}
			free(*words);
			*words = words2;

		}
		else if (t == 2)
		{
			struct WORD*words2 = malloc(sizeof(struct WORD)*cnt);
			for (int i = 0; i < cnt; i++)
			{
				struct WORD *highest = 0;
				for (int i = 0; i < cnt; i++)
				{
					if (highest == 0)
					{
						if ((*words)[i].was == 1)
							continue;
						else
							highest = &(*words)[i];
					}
					else if (abeceda(&(*words)[i],highest) && (*words)[i].was==0)
					{
						//printf("%s\n", (*words)[i].w);
						highest = &(*words)[i];
					}
				}

				ammo += test(&(*words)[i]);
				words2[i].amo = highest->amo;
				words2[i].w = highest->w;
				words2[i].cnt = highest->cnt;
				words2[i].was = highest->was;
				highest->was = 1;
			}
			free(*words);
			*words = words2;
		}
		else
		{
			for (int i = 0; i < cnt; i++)
			{
				ammo += test(&(*words)[i]);
			}
		}
	}
	else
	{
		for (int i = 0; i < cnt; i++)
		{
			ammo += test(&(*words)[i]);
		}
	}
	return ammo;
}

void vypisVsechno(struct WORD *words, int cnt)
{
	for (size_t i = 0; i < cnt; i++)
	{
		vypis_slovo(&words[i]);
	}
}

char porovnani(struct WORD*words, int cnt, char*s) {
	for (int i = 0; i < cnt; i++)
	{
		char same = 1; 
		int j = 0;
		for (; znak(&words[i].w[j]); j++)
		{

			if (s[j] == words[i].w[j])
			{
				continue;
			}
			else
			{
				same = 0;
				break;
			}
		}
		if (same && znak(&words[i].w[j]) == znak(&s[j]))
		{
			words[i].amo++;
			return 1;
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	if (argc != 0)
		for (int i = 0; i < argc; i++)
		{
			if (argv[i][0] == '-')
			{
				if (argv[i][1] == 'c')
				{
					flag |= 1;
				}
				if (argv[i][1] == 's')
				{
					flag |= 2;
					i++;
					t = atoi(argv[i]);
					if (t != 1 && t != 2)
					{
						fprintf(stderr, "Warning: Chybna hodnota parametru -s!\n");
						flag &= ~2;
					}
				}
				if (argv[i][1] == 'l')
				{
					flag |= 4;
					i++;
					l = atoi(argv[i]);
					if (l < 0)
					{
						fprintf(stderr, "Warning: Chybna hodnota parametru -l!\n");
						flag &= ~4;
					}
				}
			}

		}

	struct WORD*words;
	char*s=malloc(50);
	int cnt = 0;
	int cnt2 = 0;

	while (scanf("%s", s) == 1) {
		cnt2++;
		if (!(flag & 1))
		{
			for(int a = 0;s[a] != 0;a++)
				if (s[a] >= 'A' && s[a] <= 'Z')
				{
					s[a] += 'a' - 'A';
				}
		}

		if (porovnani(words,cnt,s))
		{
			continue;
		}
		cnt++;
		if (cnt == 1)
		{
			words = malloc(sizeof(struct WORD));
		}
		else
		{
			words = realloc(words,sizeof(struct WORD)*cnt);
		}

		for (int i = 0; ;)
		{
			i++;
			if (i == 1)
			{
				words[cnt - 1].w = malloc(i);
			}
			else
			{
				words[cnt - 1].w = realloc(words[cnt - 1].w, i);
			}

			if (znak(&s[i - 1]))
			{
				words[cnt - 1].w[i - 1] = s[i - 1];
			}
			else
			{
				words[cnt - 1].w[i - 1] = 0;
				words[cnt - 1].amo = 1;
				words[cnt - 1].cnt = i;
				words[cnt - 1].was = 0;
				break;
			}

		}
	}
	if (vypis(&words, cnt))
	{
		printf("Seznam slov:\n");
		vypisVsechno(words, cnt);
	}

	vypis(&words, cnt);
	printf("Pocet slov:          %d\n", cnt);
	int n = 0;
	for (int a = 0; a < cnt; a++)
	{
		if (words[a].amo > n)
			n = words[a].amo;
	}
	printf("Nejcastejsi:        ");
	for (int a = 0; a < cnt; a++)
	{
		if (words[a].amo == n)
			printf(" %s", words[a].w);
	}
	
	for (int a = 0; a < cnt; a++)
	{
		if (words[a].amo < n)
			n = words[a].amo;
	}
	printf("\nNejmene caste:      ");
	for (int a = 0; a < cnt; a++)
	{
		if (words[a].amo == n)
			printf(" %s", words[a].w);
	}
	printf("\n");

	for (int i = 0; i < cnt; i++)
	{
		free(words[i].w);
	}
	free(s);
	free(words);
	return 0;
}
