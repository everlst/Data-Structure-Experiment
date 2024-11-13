#include<bits/stdc++.h>
using namespace std;

// 定义学生信息结构体
struct Student {
    string name;
    int age;
    Student* next;
};

// 创建一个带头结点的链表
class StudentList {
   public:
    StudentList() {
        head = new Student();  // 创建头结点
        head->next = nullptr;  // 初始化为空链表
    }

    // 从标准输入中读取学生信息并添加到链表中
    void readFromStdin() {
        string name;
        int age;

        while (cin >> name >> age) {
            addStudent(name, age);
        }
    }

    // 添加学生到链表
    void addStudent(const string& name, int age) {
        Student* newStudent = new Student{name, age, nullptr};
        Student* temp = head;

        // 找到链表末尾
        while (temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = newStudent;
    }

    // 打印链表
    void printList() {
        Student* temp = head->next;  // 跳过头结点
        while (temp != nullptr) {
            cout << temp->name << " " << temp->age << endl;
            temp = temp->next;
        }
    }

    // 删除学生节点
    void deleteStudent(const string& name, int age) {
        Student* temp = head;
        while (temp->next != nullptr) {
            if (temp->next->name == name && temp->next->age == age) {
                Student* toDelete = temp->next;
                temp->next = temp->next->next;
                delete toDelete;
                return;
            }
            temp = temp->next;
        }
    }

    // 合并两个按年龄递增顺序排列的链表为一个按年龄递减排序的链表
    static StudentList mergeLists(StudentList& list1, StudentList& list2) {
        StudentList mergedList;

        Student* p1 = list1.head->next;
        Student* p2 = list2.head->next;
        Student* prev = nullptr;

        // 合并
        while (p1 != nullptr || p2 != nullptr) {
            if (p1 == nullptr) {
                prev->next = p2;
                break;
            }
            if (p2 == nullptr) {
                prev->next = p1;
                break;
            }

            if (p1->age > p2->age) {
                prev = p1;
                p1 = p1->next;
            } else if (p1->age < p2->age) {
                prev = p2;
                p2 = p2->next;
            } else {
                if (p1->name == p2->name) {
                    p2 = p2->next;
                } else {
                    prev = p1;
                    p1 = p1->next;
                }
            }
        }

        return mergedList;
    }

   private:
    Student* head;
};

int main() {
    // 使用freopen将文件重定向到标准输入
    freopen("student1.txt", "r", stdin);  // 将输入重定向到students.txt文件

    StudentList list1, list2;
    int n1, n2;

    // 读取学生数量
    cin >> n1;
    list1.readFromStdin();

    cin >> n2;
    list2.readFromStdin();

    // 打印链表
    cout << "List 1:" << endl;
    list1.printList();
    cout << "List 2:" << endl;
    list2.printList();

    // 合并链表并打印
    StudentList mergedList = StudentList::mergeLists(list1, list2);
    cout << "Merged List:" << endl;
    mergedList.printList();

    return 0;
}