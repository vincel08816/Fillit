/*
**	hmmm...
**	parsing the data.
**	
**	transform/ push function?
**	<< ^^ function
**	
**	1.)	check if 4 by 4
**	2.)	check if it's 4 spaces taken up
**	3.)	check if valid piece by the table
**	
**	int push left
**	this is interesting
*/

void	row_swap(int count, char **ret)
{
	int flag;
	int i;
	int j;

	set_zero(&i, &j, 0, 0);
	while (!flag)
	{
		ft_swap((int*),(int*))
	}
}
void	col_swap()
{

}

void push_left(char **ret)
{
	int i;
	int j;

	set_zero(&i, &j, 0, 0);
	while (i)
	{
		if (ret[j][i] == '.' || (i  == 3 && j == 3))
			break ;
		if (i == 3)
		{
			column++;
			i = 0;
			j++;
		}
		i++;
	}

}
set_zero(&i, &j, &flag, NULL);
int push_up(char **ret)
{

}