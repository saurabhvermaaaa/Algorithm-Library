int z[N];
void Z(string s)
{
	int l = 0, r = 0;
	for(int i = 1; i < s.size(); ++i)
	{
		if(i > r)
		{
			l = r = i;
			while(r < s.size() && s[r] == s[r - l])
				++r;
			--r;
			z[i] = r - l + 1;
		}
		else if(z[i - l] >= r - i + 1)
		{
			l = i;
			while(r < s.size() && s[r] == s[r - l])
				++r;
			--r;
			z[i] = r - l + 1;
		}
		else
		{
			z[i] = z[i - l];
		}
	}
}
