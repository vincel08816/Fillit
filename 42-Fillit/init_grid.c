
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_init_grid
{
	int			size;
	int			wtf[27][27];
	char		location[27][27];
}				t_grid;

int		count_digits(int i)
{
	int count;

	if (i == 0)
		return (1);
	count = 0;
	while (i)
	{
		i /= 10;
		count++;
	}
	return (count);
}

static void        crap_grid(t_grid **g)
{
	int num = 26;
	int i = 0;
	int j = 0;
	int k = 26;

	while (num >= 1)
	{
		j = 0;
		while (k - i > 26 - k)
		{
			(**g).wtf[k - j][k - i] = num;
			i += 1;
		}
		i = 0;
		while (k - j > 26 - k)
		{
			(**g).wtf[k - j][k - i] = num;
			j += 1;
		}
		k -= 1;
		num -= 2;
	}
}

static void        init(t_grid **g)
{
	int num = 27;
	int i = 0;
	int j = 0;
	int k = 0;

	while (num >= 1)
	{
		j = 0;
		while (i + k < 27 - k)
		{
			(**g).wtf[j + k][i + k] = num;
			i += 1;
		}
		i = 0;
		while (j + k < 27 - k)
		{
			(**g).wtf[j + k][i + k] = num;
			j += 1;
		}
		k += 1;
		num -= 2;
	}
	crap_grid(g);
}

static void		re_grid(t_grid **g)
{
	int i = 1;
	int j = 1;
	int k;
	int c = 13;		//center
	int odd = 0;
	int	m;			//movement

	(**g).size = 26;
	m = (**g).size / 2;
	if ((**g).size % 2)
		odd++;
	k = 13 - m + odd;
	while (k + j < 27 - k)
	{
		i = 1;
		while(k + i  < 27 - k)
		{
			printf("%d", ((**g).wtf[k + j][k + i]));
			i++;
		}
	j++;
		printf("\n");
	}
}


int     main(void)
{
	static		t_grid	*g;
  int       i = 0;
  int       j = 0;

	if (!g)
		if (!(g = (t_grid *)malloc(sizeof(t_grid))))
			return (0);
	init(&g);
	re_grid(&g);

  /*while (j < 27)
  {
		i = 0;
		while (i < 27)
		{
			printf("%d  ", ((*g).wtf[j][i]));
			(count_digits((*g).wtf[j][i]) == 1) ? printf(" ") : 0; 
			i++;
		}
		printf("\n\n");
		j++;
	}*/
}