#include <bits/stdc++.h>
using namespace std;

int n, m;
int father[1000000];
struct bian {
    int x, y, w;
};
bian a[1000000];
int ans = 0, k = 0;

bool cmp(const bian &a, const bian &b) {    //从小到大排序
    return a.w < b.w;
}

int getfather(int x) {
    if (father[x] == x)
        return x;
    else
        father[x] = getfather(father[x]);
    return father[x];
}

void getogether(int x, int y) {
    int fa, fb;
    fa = getfather(x), fb = getfather(y);
    if (fa != fb)
        father[fa] = fb;
}

int main() {
    freopen("EXP3/Kruskal.in", "r", stdin);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {  //初始化并查集
        father[i] = i;
    }

    for (int i = 1; i <= m; i++) {
        cin >> a[i].x >> a[i].y >> a[i].w;
    }

    sort(a + 1, a + m + 1, cmp);

    for (int i = 1; i <= m; i++) {
        if (getfather(a[i].x) != getfather(a[i].y)) {
            ans += a[i].w;
            getogether(a[i].x, a[i].y);
            k++;
            cout<< a[i].x<<" "<<a[i].y<<" "<<a[i].w<<endl;
        }
        if (k == n - 1)
            break;
    }

    if (k != n - 1)
        cout << "false" << endl; //如果不连通输出false
    else
        cout << ans << endl;

    return 0;
}