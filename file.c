#include <stdio.h>
#include <string.h>
#define ROW 129
#define COL 8
#define MINSUPPORTp 50
#define MINCONFIDENCEp 80
#define ITEMLOOP 116

// to make data ITEM PAIR.
typedef struct countValueofTransactionItems
{

	char c[3];
	int count; //frequency of items
} itemFrequency;

void countFrequencyverboseL1(char a[ROW][COL], itemFrequency (*candidate1)[52], int minsupValue)
{
	int intchars, i, j, count = 0, k = 0;
	char chars[1] = {'A'};
	char charsa[1] = {'a'};

	for (intchars = chars[0]; intchars <= ITEMLOOP; intchars++)
	{

		if (intchars >= chars[0] && intchars <= 90)
			strncpy((*candidate1)[k].c, chars, 1);
		else if (intchars >= 91 && intchars <= 116)
			strncpy((*candidate1)[k].c, charsa, 1);

		for (i = 0; i < ROW; i++)
		{

			if (strchr(*(a + i), (*candidate1)[k].c[0]))
			{
				count++;
			}

			if (i == ROW - 1)
			{

				(*candidate1)[k].count = count;
			}
		}

		if (intchars <= ITEMLOOP)
		{
			if (intchars >= chars[0] && intchars <= 90)
				++chars[0];
			else if (intchars >= 91 && intchars <= 116)
				++charsa[0];
			count = 0;
			k++;
		}
	}

	k = 0;
	printf(" L1 :: Candidates set extracted for min.Support 50\n \n");
	printf("\tPRODUCT\t\t SUPPORT\n ");
	for (i = 0; i < 52; i++)
	{
		if ((*candidate1)[i].count >= minsupValue)
		{

			printf("\t{ %c } \t  -->\t %d\n ", (*candidate1)[i].c[0], (*candidate1)[i].count); //printing final L1 set
		}
		else
		{
			(*candidate1)[i].count = 0;
			strncpy((*candidate1)[i].c, "", 1);
		}
	}
}

int countFrequencyverboseL2(char a[ROW][COL], itemFrequency (*candidate1)[52], itemFrequency (*candidate2)[52], int minsupValue)
{

	int i, j = 0, m = 1, rows = 0, count = 0, x, z, fin = 0;
	char *concatCondition, c1, c2;

	//concation condition
	for (i = 0; i < 519; i++)
	{

		if (m < 52)
		{
			c1 = (*candidate1)[j].c[0];
			c2 = (*candidate1)[m].c[0];

			if (j != m && c1 && c2)
			{

				(*candidate1)[j].c[1] = c2;
				concatCondition = strncat((*candidate1)[j].c, (*candidate1)[m].c, 1);
				strncpy((*candidate2)[rows].c, concatCondition, 2);

				rows++;
			}

			m++;
		}
		else
		{
			m = 1;
			j = j + 1;
			m = m + j;
		}
	}
	//concatination condition finished

	printf("\n\n\n\n");
	fin = rows;
	rows = 0;

	//concated pair counted
	for (z = 0; z < fin; z++)
	{
		for (x = 0; x < ROW; x++)
		{ // THERE ARE 65 ROWS IN DATABASE

			if (strchr(*(a + x), (*candidate2)[rows].c[0]) && strchr(*(a + x), (*candidate2)[rows].c[1]))
			{
				count++;
			}

			if (x == ROW - 1)
			{
				(*candidate2)[rows].count = count;
			}
		}
		count = 0;
		rows++;
	}

	//overidiing values
	printf("\n\n\n");
	printf(" L2 :: Candidates set extracted for min.Support 50\n \n");
	printf("\tPRODUCT\t\t SUPPORT\n ");
	rows = 0;
	for (z = 0; z < fin; z++)
	{

		if ((*candidate2)[z].count >= minsupValue)
		{
			(*candidate2)[rows].count = (*candidate2)[z].count;
			strncpy((*candidate2)[rows].c, (*candidate2)[z].c, 2);

			printf("\t{ %c,%c }    -->\t %d\n ", (*candidate2)[rows].c[0], (*candidate2)[rows].c[1], (*candidate2)[rows].count); //printing final L2 set
			rows++;
		}
	}

	printf("\n\n");

	return rows;
}

int countFrequencyverboseL3(char a[ROW][COL], itemFrequency (*candidate2)[52], itemFrequency (*candidate3)[52], int minsupValue, int count)
{

	int i, j, k = 0, c = 0, rows, x, count1 = 0, count2 = 0;
	char *second, *first, *third, f, t;

	for (i = 0; i < count; i++)
	{
		for (j = i + 1; j < count; j++)
		{

			if (((*candidate2)[i].c[0] == (*candidate2)[j].c[0]))
			{

				second = &(*candidate2)[j].c[1];
				strncpy((*candidate3)[k].c, (*candidate2)[i].c, 2);
				strncat((*candidate3)[k].c, second, 1);
				//	printf(" %d -- > %s\n",k ,(*candidate3)[k].c);
				k++;
				count1++;
			}
		}
	}

	rows = 0;
	//concated pair counted
	for (k = 0; k < count1; k++)
	{ //FOR 13 PAIR  CHARS
		for (x = 0; x < ROW; x++)
		{ // THERE ARE 65 ROWS IN DATABASE

			if (strchr(*(a + x), (*candidate3)[rows].c[0]) && strchr(*(a + x), (*candidate3)[rows].c[1]) && strchr(*(a + x), (*candidate3)[rows].c[2]))
			{
				c++;
			}

			if (x == ROW - 1)
			{
				(*candidate3)[rows].count = c;
			}
		}
		c = 0;
		rows++;
	}

	k = 0;

	for (j = 0; j < count1; j++)
	{
		for (i = 0; i < count; i++)
		{

			if (strstr((*candidate3)[j].c, (*candidate2)[i].c) || (strchr((*candidate2)[i].c, (*candidate3)[j].c[0]) && strchr((*candidate2)[i].c, (*candidate3)[j].c[2])))
			{
				count2++;
			}
		}
		if (count2 == 3 && (*candidate3)[k].count >= minsupValue)
		{
			(*candidate3)[k].count = (*candidate3)[j].count;
			strncpy((*candidate3)[k].c, (*candidate3)[j].c, 3);
		}
		else
		{
			(*candidate3)[k].count = 0;
			strncpy((*candidate3)[k].c, "", 3);
		}
		count2 = 0;
		k++;
	}

	printf("\n\n\n");
	printf(" L3 :: Candidates set extracted for min.Support 50\n \n");
	printf("\tPRODUCT\t\t SUPPORT\n ");

	for (i = 0; i < count1; i++)
	{
		if ((*candidate3)[i].count >= minsupValue)
			printf("\t{%c,%c,%c}  -->  \t%d\n", (*candidate3)[i].c[0], (*candidate3)[i].c[1], (*candidate3)[i].c[2], (*candidate3)[i].count);
	}

	printf("\n\n\n\n");
	return count1;
}

void generateStrongRules(char a[ROW][COL], itemFrequency (*candidate3)[52], int count)
{

	int i, x, rows = 0, e = 2, d = 0, b = 1, z;
	int countConf1 = 0, countConf2 = 0;
	float confCountTotal;

	for (i = 0; i < count; i++) // only count is 6
	{
		// the code for strong association rules goes here.
		if ((*candidate3)[i].count != 0 && (*candidate3)[i].c)
		{
			z = 0;
		label:
			if (z < 3)
			{
				countConf1 = countConf2 = 0;

				for (x = 0; x < ROW; x++)
				{

					if (strchr(*(a + x), (*candidate3)[rows].c[0]) && strchr(*(a + x), (*candidate3)[rows].c[1]) && strchr(*(a + x), (*candidate3)[rows].c[2]))
					{
						countConf1++;
					}
					if (strchr(*(a + x), (*candidate3)[rows].c[d]) && strchr(*(a + x), (*candidate3)[rows].c[b]))
					{
						countConf2++;

						//	printf("%c,%c\n",(*candidate3)[rows].c[d],(*candidate3)[rows].c[b]);
					}

					if (x == ROW - 1)
					{
						confCountTotal = ((float)(countConf1) / (float)(countConf2)) * 100;

						if (confCountTotal > 80)
						{
							printf("\tThe strong rule is   %c,%c-->%c :: %d/%d -- > %f%\n", (*candidate3)[rows].c[d], (*candidate3)[rows].c[b], (*candidate3)[rows].c[e], countConf1, countConf2, confCountTotal);
						}
					}
				}
				z++;
				if (z == 1)
				{
					d = 1;
					b = 2;
					e = 0;
				}
				else if (z == 2)
				{
					d = 0;
					b = 2;
					e = 1;
				}
				goto label;
			}
		}

		//	countConf1 = countConf2 = 0;
		rows++;
	}
}

int main()
{

	/** variables and defined types declared **/
	int noOfTransaction, count = 1, i = 0, j = 0, minsupValue = 0, minconValue = 0, intchars;

	/** cache miss is less in case of array , so used wrt linked list**/
	itemFrequency candidate1[52] = {};
	itemFrequency candidate2[52] = {};
	itemFrequency candidate3[52] = {};
	/**candidate array done **/

	char currentValue, a[ROW][COL] = {};
	FILE *fp;

	/** declaration end**/

	fp = fopen("a.txt", "r");
	if (fp)
	{

		printf("\n\t\t\t\t\t\t\t CUSTOMERIOR :  WHAT TO BUY ?\n\n");

		printf("\t\t\t\t NOTE: EACH TRANSACTION LIMIT COMTAINS MAX. 8 ITEMS\n\n\n");

		/** Extract characters from file and store in character c **/
		for (currentValue = fgetc(fp); currentValue != EOF; currentValue = fgetc(fp))
		{
			if (currentValue == '\n') // Increment count if this character is newline
				count = count + 1;
		}
		/** count closed **/
		fclose(fp);

		//open file again to store the input data.
		fp = fopen("a.txt", "r");

		while ((currentValue = fgetc(fp)) != EOF)
		{

			if (currentValue != ' ' && currentValue != '\n')
			{
				a[i][j] = currentValue;
				j = j + 1;
			}
			else
			{

				if (currentValue == '\n')
				{
					i++;
					j = 0;
				}
			}
		}
	}

	else
	{
		puts("Note: Either file is empty or not avalable");
	}

	//input done. so close the file.
	fclose(fp);

	/**calcluate support first**/
	minsupValue = (int)((((float)(MINSUPPORTp) / 100)) * count); // This comes out to be 25.

	/**support closed **/

	//	system("COLOR 27");
	countFrequencyverboseL1(a, &candidate1, minsupValue);							  //this is for L1 which is done.
	count = countFrequencyverboseL2(a, &candidate1, &candidate2, minsupValue);		  // this is for L2 which is done.
	count = countFrequencyverboseL3(a, &candidate2, &candidate3, minsupValue, count); //this is for L3 which is  done.
	generateStrongRules(a, &candidate3, count);

	return 0;
}
