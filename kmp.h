class KMP
{
	int *next;

	void getnext(string s)
	{
		int i, j = -1, l = s.size();

		next = new int[l +10];
		REP1(i, l - 1)
		{
			while (j != -1 && s[i] != s[j + 1]) j = next[j];
			j += s[i] == s[j + 1];
			next[i] = j;
		}
	}

	void cmp(string a, string b) /***find a in b***/
	{
		int i, j = -1, l = b.size();

		getnext(a);
		REP(i, l)
		{
			while (j != -1 && b[i] != a[j + 1]) j = next[j];
			j += b[i] == a[j + 1];
			if (j == a.size() - 1)
				/***pass***/;
		}
	}
};
