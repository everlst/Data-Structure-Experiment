#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;
int a[MAXN];  // 存储数据的数组
int n;          // 数据个数

// 检查重复元素
void Check() {
    bool flag = false;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] == a[j]) {
                flag = true;
                break;
            }
        }
    }
    if (flag) {
        cout << "序列中存在重复元素" << endl;
    } else {
        cout << "序列中无重复元素" << endl;
    }
}

// 快速排序
void Quick_Sort(int left, int right) {
    if (left >= right)
        return;

    int i = left, j = right;
    int pivot = a[left];  // 选择第一个元素作为基准

    while (i < j) {
        while (i < j && a[j] >= pivot) j--;
        if (i < j)
            a[i] = a[j];

        while (i < j && a[i] <= pivot) i++;
        if (i < j)
            a[j] = a[i];
    }
    a[i] = pivot;

    Quick_Sort(left, i - 1);
    Quick_Sort(i + 1, right);
}

// 折半查找
void H_Find(int key) {
    int left = 0, right = n - 1;
    int count = 0;  // 记录找到的次数
    bool found = false;

    // 找到第一个等于key的位置
    while (left <= right) {
        int mid = (left + right) / 2;
        if (a[mid] == key) {
            found = true;
            count++;

            // 统计相同元素个数
            int temp = mid - 1;
            while (temp >= 0 && a[temp] == key) {
                count++;
                temp--;
            }
            temp = mid + 1;
            while (temp < n && a[temp] == key) {
                count++;
                temp++;
            }
            break;
        } else if (a[mid] > key) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if (found) {
        cout << "查找成功！关键字 " << key << " 出现了 " << count << " 次" << endl;
    } else {
        cout << "查找不成功！未找到关键字 " << key << endl;
    }
}

int main() {
    freopen("EXP4/input.txt", "r", stdin);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // 检查重复元素
    cout << "\n检查重复元素：" << endl;
    Check();

    // 快速排序
    cout << "\n排序前：";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    Quick_Sort(0, n - 1);

    cout << "排序后：";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    // 折半查找
    int key;
    cout << "\n请输入要查找的关键字：";
    cin >> key;
    H_Find(key);

    return 0;
}