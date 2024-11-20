#include <bits/stdc++.h>

// 定义学生信息结构体
typedef struct stuInfo {
    char stuName[10];  // 姓名
    long age;          // 生日（格式19940424）
} ElemType;

// 定义链表节点结构体
typedef struct node {
    ElemType data;
    struct node *next;
} ListNode, *ListPtr;

// 创建新节点
ListPtr createNode(ElemType data) {
    ListPtr newNode = (ListPtr)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 向链表末尾添加节点
void AddNode(ListPtr *head, ElemType data) {
    ListPtr newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        ListPtr temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// 删除指定学生信息的节点
void DeleteNode(ListPtr *head, char *name, long age) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }
    ListPtr temp = *head;
    ListPtr prev = NULL;
    while (temp != NULL) {
        if (strcmp(temp->data.stuName, name) == 0 && temp->data.age == age) {
            if (prev == NULL) {
                *head = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Node deleted: %s %ld\n", name, age);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Node not found: %s %ld\n", name, age);
}

// 打印链表中的所有节点
void PrintList(ListPtr head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    ListPtr temp = head;
    while (temp != NULL) {
        printf("Name: %s, Age: %ld\n", temp->data.stuName, temp->data.age);
        temp = temp->next;
    }
}

// 合并两个按年龄递增排序的链表并按年龄递减排序
ListPtr Merge(ListPtr list1, ListPtr list2) {
    ListPtr mergedList = NULL;
    ListPtr temp1 = list1;
    ListPtr temp2 = list2;

    // 使用 set 来保证每个学生只出现一次
    while (temp1 != NULL) {
        AddNode(&mergedList, temp1->data);
        temp1 = temp1->next;
    }
    while (temp2 != NULL) {
        ListPtr temp = mergedList;
        int found = 0;
        while (temp != NULL) {
            if (strcmp(temp->data.stuName, temp2->data.stuName) == 0 && temp->data.age == temp2->data.age) {
                found = 1;
                break;
            }
            temp = temp->next;
        }
        if (!found) {
            AddNode(&mergedList, temp2->data);
        }
        temp2 = temp2->next;
    }

    // 将合并后的链表按年龄递减排序
    ListPtr sortedList = NULL;
    ListPtr current = mergedList;
    while (current != NULL) {
        ListPtr next = current->next;
        if (sortedList == NULL || current->data.age > sortedList->data.age) {
            current->next = sortedList;
            sortedList = current;
        } else {
            ListPtr temp = sortedList;
            while (temp->next != NULL && temp->next->data.age > current->data.age) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }

    return sortedList;
}

ListPtr list1 = NULL;
ListPtr list2 = NULL;

int main() {
    freopen("Linear_List_StuInfo/result.txt", "w", stdout);

    std::ifstream file1("Linear_List_StuInfo/students1.txt");  // 请替换为你的文件名
    std::string line1;

    // 逐行读取文件
    while (std::getline(file1, line1)) {
        std::stringstream ss(line1);
        ElemType student;

        std::string temp_name;
        long temp_birthday;

        // 从当前行中读取姓名和生日
        ss >> temp_name >> temp_birthday;

        // 将 std::string 转换为 char 数组
        std::strncpy(student.stuName, temp_name.c_str(), sizeof(student.stuName) - 1);
        student.stuName[sizeof(student.stuName) - 1] = '\0';  // 确保字符串以 null 结尾

        // 将生日保存到结构体中
        student.age = temp_birthday;
        AddNode(&list1, student);
    }

    file1.close();

    std::ifstream file2("Linear_List_StuInfo/students2.txt");  // 请替换为你的文件名
    std::string line2;

    // 逐行读取文件
    while (std::getline(file2, line2)) {
        std::stringstream ss(line2);
        ElemType student;

        std::string temp_name;
        long temp_birthday;

        // 从当前行中读取姓名和生日
        ss >> temp_name >> temp_birthday;

        // 将 std::string 转换为 char 数组
        std::strncpy(student.stuName, temp_name.c_str(), sizeof(student.stuName) - 1);
        student.stuName[sizeof(student.stuName) - 1] = '\0';  // 确保字符串以 null 结尾

        // 将生日保存到结构体中
        student.age = temp_birthday;
        AddNode(&list2, student);
    }

    file2.close();

    // 打印初始链表
    printf("List 1:\n");
    PrintList(list1);
    printf("List 2:\n");
    PrintList(list2);

    // 合并链表并打印结果
    ListPtr mergedList = Merge(list1, list2);
    printf("Merged List (Age Descending):\n");
    PrintList(mergedList);

    return 0;
}
