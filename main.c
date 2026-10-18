#include <stdio.h>
#include "student.h"
#include "utils.h"

static void showMenu(void) {
    puts("\n========================================");
    puts("       STUDENT MANAGEMENT SYSTEM");
    puts("========================================");
    puts("1.  Talaba qo'shish");
    puts("2.  Barcha talabalarni ko'rish");
    puts("3.  Talaba qidirish");
    puts("4.  Talaba ma'lumotini tahrirlash");
    puts("5.  Talabani o'chirish");
    puts("6.  Baholar bo'yicha saralash");
    puts("7.  Statistika");
    puts("0.  Chiqish");
    puts("----------------------------------------");
}

int main(void) {
    int choice;

    loadStudents();
    printf("Dastur ishga tushdi. Fayldan %d ta talaba yuklandi.\n",
           studentCount);

    do {
        showMenu();
        choice = readInt("Tanlovingiz: ");

        switch (choice) {
            case 1: addStudent(); break;
            case 2: listStudents(); break;
            case 3: searchStudents(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: sortStudentsByGrade(); break;
            case 7: showStatistics(); break;
            case 0: puts("Dastur yakunlandi. Xayr!"); break;
            default: puts("Noto'g'ri tanlov. 0-7 oralig'ida tanlang.");
        }
    } while (choice != 0);

    return 0;
}
