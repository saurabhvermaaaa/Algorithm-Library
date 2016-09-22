int last[LG][N], pos[N];
struct node
{
	int index;
	int first, second;
	bool operator < (const node b) const
	{
		return (first == b.first) ? (second < b.second) : (first < b.first);
	}
	bool operator == (node b)
	{
		return (first == b.first && second == b.second);
	}
}arr[N];
vi buildSA(string s)
{
	vi sa(s.size());
	for(int i = 0; i < s.size(); ++i)
		last[0][i] = s[i] -'a';
	for(int step = 1, done = 1; done < s.size(); done <<= 1, ++step)
	{
		for(int i = 0; i < s.size(); ++i)
		{
			arr[i].index = i;
			arr[i].F = last[step - 1][i];
			arr[i].S = ((i + done < s.size()) ? last[step - 1][i + done] : -1);
		}

		sort(arr, arr + s.size());

		for(int i = 0; i < s.size(); ++i)
		{
			if(i > 0 && arr[i] == arr[i - 1])
				last[step][arr[i].index] = last[step][arr[i - 1].index];
			else
				last[step][arr[i].index] = i;
		}
	}

	int step = ceil(log2(s.size()));

	for(int i = 0; i < s.size(); ++i)
	{
		sa[last[step][i]] = i;
		pos[i] = last[step][i];
	}
	return sa;
}
vi buildLCP(string s, vi sa)
{
	vi lcp(s.size());
	for(int i = 0, k = 0; i < s.size(); ++i)
	{
		if(pos[i] == s.size() - 1)
		{
			k = 0;
			continue;
		}
		int j = sa[pos[i] + 1];
		while(i + k < s.size() && j + k < s.size() && s[i + k] == s[j + k])
			++k;
		lcp[pos[i]] = k;
		(k > 0) ? --k : 0;
	}
	return lcp;
}
