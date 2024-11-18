#include <bits/stdc++.h>
using namespace std;

// 哈夫曼树节点结构
typedef struct {
    char ch;     // 字符
    int weight;  // 权重/频率
    int parent;  // 父节点
    int left;    // 左子节点
    int right;   // 右子节点
} HTNode, *HuffmanTree;

// 哈夫曼编码结构
typedef struct {
    char ch;      // 字符
    string code;  // 编码
} HuffmanCode;

// 全局变量
HuffmanTree HT;       // 哈夫曼树
HuffmanCode* HC;      // 哈夫曼编码表
int CH_Count;         // 叶子节点数
map<char, int> freq;  // 频率表

// 统计字符频率
void Frequency(const string& str) {
    freq.clear();
    for (char c : str) {
        freq[c]++;
    }
    CH_Count = freq.size();
}

// 选择最小的两个节点
void selectMin(int end, int& s1, int& s2) {
    int min1 = INT_MAX, min2 = INT_MAX;  // 令min1为最小，min2为次小

    for (int i = 1; i <= end; i++) {
        if (HT[i].parent == 0) {  // 位于森林中未被选中
            if (HT[i].weight < min1) {
                min2 = min1;  // 更新次小值
                s2 = s1;
                min1 = HT[i].weight;
                s1 = i;
            } else if (HT[i].weight < min2) {
                min2 = HT[i].weight;  // 更新次小值
                s2 = i;
            }
        }
    }
}

// 构建哈夫曼树
void Build() {
    int n = 2 * CH_Count - 1;  // 节点总数
    HT = new HTNode[n + 1];    // 0号位置不使用

    // 初始化叶子节点（建立森林）
    int i = 1;
    for (auto& pair : freq) {
        HT[i].ch = pair.first;
        HT[i].weight = pair.second;
        HT[i].parent = HT[i].left = HT[i].right = 0;
        i++;
    }

    // 初始化非叶子节点（剩下的）
    for (; i <= n; i++) {
        HT[i].parent = HT[i].left = HT[i].right = 0;
        HT[i].weight = 0;
    }

    // 构建树
    for (i = CH_Count + 1; i <= n; i++) {  // 从第一个非叶子节点开始
        int s1 = 0, s2 = 0;
        selectMin(i - 1, s1, s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].left = s1;
        HT[i].right = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}

// 生成哈夫曼编码
void Encode() {
    HC = new HuffmanCode[CH_Count + 1];  // 编码表
    char* temp = new char[CH_Count];
    temp[CH_Count - 1] = '\0';

    for (int i = 1; i <= CH_Count; i++) {
        int p = CH_Count - 1;  // 从后往前存放编码
        int currt = i;
        int father = HT[i].parent;
        while (father != 0) {
            p--;
            temp[p] = (HT[father].left == currt) ? '0' : '1';
            currt = father;
            father = HT[father].parent;
        }
        HC[i].ch = HT[i].ch;
        HC[i].code = string(temp + p);
    }
    delete[] temp;
}

// 初始化哈夫曼编码
void initHuffman(const string& str) {
    Frequency(str);
    Build();
    Encode();
}

// 编码
string encode(const string& str) {
    string result;
    map<char, string> Code_T;

    for (int i = 1; i <= CH_Count; i++) {
        Code_T[HC[i].ch] = HC[i].code;
    }

    for (char c : str) {
        result += Code_T[c];
    }
    return result;
}

// 解码
string decode(const string& code) {
    string result;
    int pos = 0;
    while (pos < code.length()) {
        int p = 2 * CH_Count - 1;
        while (HT[p].left != 0 && HT[p].right != 0) {
            if (code[pos] == '0') {
                p = HT[p].left;
            } else {
                p = HT[p].right;
            }
            pos++;
        }
        result += HT[p].ch;
    }
    return result;
}

// 打印频率统计
void printFrequencyStats() {
    int totalChars = 0;
    for (const auto& pair : freq) {
        totalChars += pair.second;
    }

    cout << "\n=== 字符频率统计 ===" << endl;
    cout << "总字符数: " << totalChars << endl;
    cout << "不同字符数: " << CH_Count << endl;
    cout << "\n字符\t出现次数\t频率" << endl;
    cout << "--------------------------------" << endl;

    for (const auto& pair : freq) {
        double percentage = (double)pair.second / totalChars * 100;
        cout << (pair.first == ' ' ? "空格" : string(1, pair.first)) << "\t"
             << pair.second << "\t\t"
             << fixed << setprecision(2) << percentage << "%" << endl;
    }
    cout << "--------------------------------" << endl;
}

// 打印编码表
void printCodes() {
    cout << "\nHuffman编码表：" << endl;
    cout << "--------------------------------" << endl;
    for (int i = 1; i <= CH_Count; i++) {
        cout << "字符: " << HC[i].ch
             << " \t编码: " << HC[i].code << endl;
    }
    cout << "--------------------------------" << endl;
}

// 清理内存
void cleanup() {
    delete[] HT;
    delete[] HC;
}

int main() {
    freopen("EXP2/string.txt", "r", stdin);
    freopen("EXP2/OUT.txt", "w", stdout);

    string str;
    getline(cin, str);  // 使用getline读取整行，包括空格

    initHuffman(str);
    printFrequencyStats();
    printCodes();

    string encoded = encode(str);
    cout << "\n编码结果：" << encoded << endl;

    string unencodeed;
    cin >> unencodeed;
    string decoded = decode(unencodeed);
    cout << "\n解码结果：" << decoded << endl;

    string ans;
    cin >> ans;
    // 验证结果
    cout << "\n验证结果：" << (ans == decoded ? "正确" : "错误") << endl;

    cleanup();  // 清理内存
    return 0;
}