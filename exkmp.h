#include <string.h>
#define REP(i, n) for (i = 0; i < (n); i++)
#define REP1(i, n) for (i = 1; i <= (n); i++)
using namespace std;

int max(int a, int b) {return a > b ? a : b;}
int min(int a, int b) {return a < b ? a : b;}

class EXKMP
{
	public:
	
	void getPref(char *s, int n, int *pref) /*get pref array*/
	{
		int i, f, g;
		
		pref[0] = n;
		g = 0;
		REP(i, n - 1)
			if (i < g && pref[i - f] != g - i)
				pref[i] = min(pref[i - f], g - i);
			else
			{
				g = max(g, i); f = i;
				while (g < n && s[g] == s[g - f]) g++;
				pref[i] = g - f;
			}
	}
};
