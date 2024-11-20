#include <bits/stdc++.h>
using namespace std;

// 定义学生信息结构体
typedef struct stuInfo {
    char stuName[10];  // 姓名
    long Birth_Date;   // 生日（格式19940424）
} ElemType;

// 定义链表节点数据结构体
typedef struct node {
    ElemType data;
    struct node *next;
} ListNode, *ListPtr;

// 创建带头结点的空链表
ListPtr CreateList() {
    ListPtr head = new ListNode;  // 创建头结点
    head->next = nullptr;         // 头结点的next指针置空
    return head;
}

// 删除整个链表
void DestroyList(ListPtr &head) {
    if (!head)
        return;

    ListPtr p = head;  // 从头结点开始
    while (p) {
        ListPtr temp = p;  // 保存当前节点
        p = p->next;       // 移动到下一个节点
        delete temp;       // 释放当前节点
    }
    head = nullptr;  // 头指针置空
}

// 创建新节点
ListPtr createNode(ElemType data) {
    ListPtr newNode = new ListNode;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 向链表末尾添加节点
void AddNode(ListPtr *head, ListPtr *tail, ElemType data) {
    ListPtr newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

// 删除指定学生信息的节点
void DeleteNode(ListPtr *head, char *name, long Birth_Date) {
    if (*head == NULL) {
        printf("空表。\n");
        return;
    }
    ListPtr temp = *head;
    ListPtr prev = NULL;
    while (temp != NULL) {
        if (strcmp(temp->data.stuName, name) == 0 && temp->data.Birth_Date == Birth_Date) {
            if (prev == NULL) {
                *head = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp;
            printf("删除节点： %s %ld\n", name, Birth_Date);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("节点未找到： %s %ld\n", name, Birth_Date);
}

// 打印链表中的所有节点
void PrintList(ListPtr head) {
    if (head == NULL) {
        printf("空表\n");
        return;
    }
    ListPtr temp = head;
    while (temp != NULL) {
        printf("姓名: %s, 生日: %ld\n", temp->data.stuName, temp->data.Birth_Date);
        temp = temp->next;
    }
}

// 交换两个节点的数据
void SwapData(ListPtr a, ListPtr b) {
    ElemType temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// 冒泡排序实现链表排序（从小到大）
void SortList(ListPtr head) {
    if (head == NULL || head->next == NULL)
        return;

    bool swapped;
    ListPtr ptr1;
    ListPtr lptr = NULL;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data.Birth_Date > ptr1->next->data.Birth_Date) {
                SwapData(ptr1, ptr1->next);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// 合并
ListPtr Merge(ListPtr list1, ListPtr list2) {
    // 先对输入链表排序
    SortList(list1);
    SortList(list2);

    ListPtr mergedList = NULL, tail = NULL;

    // 合并两个有序链表
    while (list1 != NULL && list2 != NULL) {
        if (list1->data.Birth_Date < list2->data.Birth_Date) {
            AddNode(&mergedList, &tail, list1->data);
            list1 = list1->next;
        } else {
            AddNode(&mergedList, &tail, list2->data);
            list2 = list2->next;
        }
    }

    // 剩下的直接加上
    while (list1 != NULL) {
        AddNode(&mergedList, &tail, list1->data);
        list1 = list1->next;
    }

    while (list2 != NULL) {
        AddNode(&mergedList, &tail, list2->data);
        list2 = list2->next;
    }

    return mergedList;
}

ListPtr list1 = NULL, tail1 = NULL;
ListPtr list2 = NULL, tail2 = NULL;

int main() {
    freopen("Linear_List_StuInfo/result.txt", "w", stdout);

    std::ifstream file1("Linear_List_StuInfo/students1.txt");
    std::string line1;

    // 逐行读取文件
    while (std::getline(file1, line1)) {
        std::stringstream ss(line1);
        ElemType student;

        std::string temp_name;
        long temp_birthday;

        ss >> temp_name >> temp_birthday;

        // 将 std::string 转换为 char 数组
        std::strncpy(student.stuName, temp_name.c_str(), sizeof(student.stuName) - 1);
        student.stuName[sizeof(student.stuName) - 1] = '\0';

        // 将生日保存到结构体中
        student.Birth_Date = temp_birthday;
        AddNode(&list1, &tail1, student);
    }

    file1.close();

    std::ifstream file2("Linear_List_StuInfo/students2.txt");
    std::string line2;

    // 逐行读取文件
    while (std::getline(file2, line2)) {
        std::stringstream ss(line2);
        ElemType student;

        std::string temp_name;
        long temp_birthday;

        ss >> temp_name >> temp_birthday;

        // 将 std::string 转换为 char 数组
        std::strncpy(student.stuName, temp_name.c_str(), sizeof(student.stuName) - 1);
        student.stuName[sizeof(student.stuName) - 1] = '\0';

        // 将生日保存到结构体中
        student.Birth_Date = temp_birthday;
        AddNode(&list2, &tail2, student);
    }

    file2.close();

    // 打印初始链表
    printf("List 1:\n");
    PrintList(list1);
    printf("List 2:\n");
    PrintList(list2);

    // 合并链表并打印结果
    ListPtr mergedList = Merge(list1, list2);
    printf("合并后的链表（年龄降序）:\n");
    PrintList(mergedList);

    return 0;
}
