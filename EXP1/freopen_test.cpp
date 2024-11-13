#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

// 定义学生信息结构体
typedef struct stuInfo {
    char stuName[10];  // 姓名
    long age;          // 生日（格式19940424）
} ElemType;

int main() {
    std::ifstream file("EXP1/students1.txt");  // 请替换为你的文件名
    if (!file.is_open()) {
        std::cerr << "无法打开文件!" << std::endl;
        return 1;
    }

    std::string line;

    // 逐行读取文件
    while (std::getline(file, line)) {
        std::stringstream ss(line);
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

        // 输出结果，确认数据读取成功
        std::cout << "姓名: " << student.stuName << ", 出生日期: " << student.age << std::endl;
    }

    file.close();
    return 0;
}
