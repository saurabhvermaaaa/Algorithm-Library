ll mul(ll a,ll b,ll c)
{
    ll ret = 0;
    while(b > 0)
    {
        if(b & 1)
        {
            ret = (ret + a) % c;
        }
        a = (a + a) % c;
        b >>= 1;
    }
    return ret;
}
ll power(ll a,ll b,ll c)
{
    ll ret = 1;
    while(b > 0)
    {
        if(b & 1)
        {
            ret = mul(ret, a, c);
        }
        a = mul(a, a, c);
        b >>= 1;
    }
    return ret;
}
const int ITERATIONS = 1000;
//power function may overflow, use mul
bool isprime(ll n)
{
    if((n & 1) && n > 6)
    {
        ll d = n - 1, p = n - 5, s = 0;
        while(d % 2 == 0)
        {
            d /= 2;
            ++s;
        }
        --s;
        for(ll it = 0; it < ITERATIONS; ++it)
        {
            srand(it * it + it);
            ll a = rand() % p + 3;
            ll b = power(a, d, n);
            if(b != 1 && b != n - 1)
            {
                bool flag = false;
                for(int i = 0; i < s; ++i)
                {
                    b = mul(b, b, n);
                    if(b == 1)
                    {
                        return false;
                    }
                    else if(b == n - 1)
                    {
                        flag = true;
                        break;
                    }
                }
                if(!flag) return false;
            }
        }
        return true;
    }
    else if(n == 2 || n == 3 || n == 5) return true;
    else return false;
}
