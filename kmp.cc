const int N = 112345, M = 112345;
int F[M];
void buildF(int pattern[M], int m)
{
	F[0] = 0, F[1] = 0;
	for(int i = 2; i <= m; ++i)
	{
		F[i] = 0;
		int j = F[i-1];
		while(j > 0)
		{
			if(pattern[i-1] == pattern[j])
			{
				F[i] = j + 1;
				break;
			}
			else
                j = F[j];
		}
		if(j == 0 && pattern[i - 1] == pattern[0])
            F[i] = 1;
	}
}
int match(int text[N], int n, int pattern[M], int m)
{
	int ans = 0;
	int j = 0;
	for(int i = 0; i < n; ++i)
	{
		if(text[i] == pattern[j])
		{
			++j;
			if(j == m)
			{
				++ans;
				j = F[m];
			}
		}
		else
		{
			while(j > 0)
			{
				if(text[i] == pattern[j])
				{
					++j;
					break;
				}
				else
                    j = F[j];
			}
			if(j == 0 && pattern[0] == text[i])
                j = 1;
		}
	}
	return ans;
}
