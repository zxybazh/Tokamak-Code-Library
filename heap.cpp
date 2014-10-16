class heap{
    private:
        int l;
        int h[N], w[N];
        bool cmp(int x, int y) {
            return (a[x] < a[y]);
        }
    public:
        heap(){
            l = 0;
        }
        void up(int x){
            int fa = x / 2, son = x;
            while (son != 1 && cmp(h[son], h[fa])) {
                swap(h[fa], h[son]);
                w[h[son]] = son;
                w[h[fa]] = fa;
                son = fa;
                fa >>= 1;
            }
        }
        void down(int x){
            int fa = x, son;
            bool stop = false;
            while (fa * 2 <= l && !stop) {
                if (fa * 2 + 1 > l ||
		cmp(h[fa * 2], h[fa * 2 + 1]))
			son = fa * 2;
                else son = fa * 2 + 1;
                if (cmp(h[son], h[fa])) {
                    swap(h[son], h[fa]);
                    w[h[son]] = son;
                    w[h[fa]] = fa;
                    fa = son;
                } else stop = true;
            }
        }
        void push(int x){
            h[++l] = x;
            w[x] = l;
            up(l);
        }
        int pop(){
            return h[1];
        }
        void mov(int x){
            up(w[x]);
            down(w[x]);
        }
        void del(int x){
            x = w[x];
            h[x] = h[l--];
            w[h[x]] = x;
            mov(h[x]);
        }
};
