void multiplyPower(ll a[N][N], ll b[N][N], int s)
{
	ll cc[N][N];
	for(int i = 1; i <= s; ++i)
	      for(int j = 1; j <= s; ++j)
		cc[i][j] = 0;
	for(int i = 1; i <= s; ++i)
	   for(int j = 1; j <= s; ++j)
	      for(int k = 1; k <= s; ++k)
		cc[i][k] = (cc[i][k] + a[i][j] * b[j][k]) % mod;
	for(int i = 1; i <= s; ++i)
	      for(int j = 1; j <= s; ++j)
		b[i][j] = cc[i][j];
}
void power(ll a[N][N], int p, int s, ll r[N][N])    //powers a^n where a is sXs matrix into r
{
	ll cp[N][N];
	for(int i = 1; i <= s; ++i)
		for(int j = 1; j <= s; ++j)
			r[i][j] = ((i == j) ? 1 : 0);
	for(int i = 1; i <= s; ++i)
		for(int j = 1; j <= s; ++j)
			cp[i][j] = a[i][j];
	while(p > 0)
	{
		if(p & 1)multiplyPower(cp, r, s);
		multiplyPower(cp, cp, s);
		p >>= 1;
	}
}
void mul(ll A[N][N], ll B[N][2], int a, int b, int c = 1)
{
		ll rr[N][2];
			for(int i = 1; i <= a; ++i)
						for(int j = 1; j <= c; ++j)
										rr[i][j] = 0;
				for(int i = 1; i <= a; ++i)
							for(int j = 1; j <= b; ++j)
											for(int k = 1; k <= c; ++k)
																rr[i][k] = (A[i][j] * B[j][k] + rr[i][k]) % mod;
					for(int i = 1; i <= a; ++i)
								for(int j = 1; j <= c; ++j)
												B[i][j] = rr[i][j];
}
