#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "student.h"
#include "utils.h"

Student students[MAX_STUDENTS];
int studentCount = 0;

int findStudentIndexById(int id) {
    int i;
    for (i = 0; i < studentCount; i++) {
        if (students[i].id == id) return i;
    }
    return -1;
}

static void printStudent(const Student *s) {
    printf("%-7d %-28s %-6d %-16s %7.2f\n",
           s->id, s->name, s->age, s->group, s->grade);
}

static void printHeader(void) {
    printf("\n%-7s %-28s %-6s %-16s %7s\n",
           "ID", "ISM-FAMILIYA", "YOSH", "GURUH", "BAHO");
    puts("--------------------------------------------------------------------------");
}

void addStudent(void) {
    Student s;

    if (studentCount >= MAX_STUDENTS) {
        puts("Talabalar uchun xotira limiti to'ldi.");
        return;
    }

    s.id = readInt("ID (musbat va takrorlanmas): ");
    if (s.id <= 0 || findStudentIndexById(s.id) != -1) {
        puts("Xato: ID musbat bo'lishi va takrorlanmasligi kerak.");
        return;
    }

    readText("Ism-familiya: ", s.name, sizeof s.name);
    s.age = readInt("Yosh: ");
    if (s.age < 16 || s.age > 100) {
        puts("Yosh 16 dan 100 gacha bo'lishi kerak.");
        return;
    }

    readText("Guruh: ", s.group, sizeof s.group);
    s.grade = readFloat("Baho (0-100): ");
    if (s.grade < 0 || s.grade > 100) {
        puts("Baho 0 dan 100 gacha bo'lishi kerak.");
        return;
    }

    students[studentCount++] = s;
    if (saveStudents()) puts("Talaba qo'shildi va faylga saqlandi.");
    else puts("Talaba xotiraga qo'shildi, lekin faylga saqlashda xatolik yuz berdi.");
}

void listStudents(void) {
    int i;
    if (studentCount == 0) {
        puts("Hozircha talabalar mavjud emas.");
        return;
    }
    printHeader();
    for (i = 0; i < studentCount; i++) printStudent(&students[i]);
    printf("\nJami: %d ta talaba\n", studentCount);
}

static int containsIgnoreCase(const char *text, const char *query) {
    size_t i, j, n = strlen(query);
    if (n == 0) return 1;
    for (i = 0; text[i]; i++) {
        for (j = 0; j < n && text[i + j]; j++) {
            if (tolower((unsigned char)text[i + j]) !=
                tolower((unsigned char)query[j])) break;
        }
        if (j == n) return 1;
    }
    return 0;
}

void searchStudents(void) {
    int mode, i, found = 0;
    char query[NAME_LEN];

    puts("\nQidirish turi:");
    puts("1. ID bo'yicha");
    puts("2. Ism-familiya bo'yicha");
    puts("3. Guruh bo'yicha");
    mode = readInt("Tanlov: ");

    if (mode == 1) {
        int id = readInt("Talaba ID si: ");
        int index = findStudentIndexById(id);
        if (index < 0) puts("Talaba topilmadi.");
        else { printHeader(); printStudent(&students[index]); }
        return;
    }

    if (mode != 2 && mode != 3) {
        puts("Noto'g'ri tanlov.");
        return;
    }

    readText("Qidiruv matni: ", query, sizeof query);
    printHeader();
    for (i = 0; i < studentCount; i++) {
        const char *field = (mode == 2) ? students[i].name : students[i].group;
        if (containsIgnoreCase(field, query)) {
            printStudent(&students[i]);
            found = 1;
        }
    }
    if (!found) puts("Mos talaba topilmadi.");
}

void updateStudent(void) {
    int id = readInt("Tahrirlash uchun talaba ID si: ");
    int index = findStudentIndexById(id);
    Student old, updated;

    if (index < 0) {
        puts("Talaba topilmadi.");
        return;
    }

    old = students[index];
    updated = old;
    puts("Yangi ma'lumotlarni kiriting:");

    readText("Ism-familiya: ", updated.name, sizeof updated.name);
    updated.age = readInt("Yosh: ");
    if (updated.age < 16 || updated.age > 100) {
        puts("Yosh 16 dan 100 gacha bo'lishi kerak. O'zgarish bekor qilindi.");
        return;
    }

    readText("Guruh: ", updated.group, sizeof updated.group);
    updated.grade = readFloat("Baho (0-100): ");
    if (updated.grade < 0 || updated.grade > 100) {
        puts("Baho noto'g'ri. O'zgarish bekor qilindi.");
        return;
    }

    students[index] = updated;
    if (saveStudents()) puts("Ma'lumotlar yangilandi.");
    else {
        students[index] = old;
        puts("Saqlash xatosi. O'zgarish bekor qilindi.");
    }
}

void deleteStudent(void) {
    int id = readInt("O'chirish uchun talaba ID si: ");
    int index = findStudentIndexById(id);
    int i;
    char confirm[16];

    if (index < 0) {
        puts("Talaba topilmadi.");
        return;
    }

    printf("Haqiqatan ham %s ni o'chirmoqchimisiz? (ha/yo'q): ",
           students[index].name);
    if (!fgets(confirm, sizeof confirm, stdin)) return;
    confirm[strcspn(confirm, "\r\n")] = '\0';

    if (strcmp(confirm, "ha") != 0 && strcmp(confirm, "HA") != 0 &&
        strcmp(confirm, "Ha") != 0) {
        puts("O'chirish bekor qilindi.");
        return;
    }

    {
        Student removed = students[index];
        for (i = index; i < studentCount - 1; i++)
            students[i] = students[i + 1];
        studentCount--;

        if (saveStudents()) puts("Talaba o'chirildi.");
        else {
            for (i = studentCount; i > index; i--)
                students[i] = students[i - 1];
            students[index] = removed;
            studentCount++;
            puts("Saqlash xatosi. O'chirish bekor qilindi.");
        }
    }
}

void sortStudentsByGrade(void) {
    int i, j;
    Student temp;

    for (i = 0; i < studentCount - 1; i++) {
        for (j = 0; j < studentCount - i - 1; j++) {
            if (students[j].grade < students[j + 1].grade) {
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    puts("Talabalar bahosi bo'yicha kamayish tartibida saralandi.");
    listStudents();
    /* Save order too, so the displayed order remains after restart. */
    if (!saveStudents()) puts("Eslatma: saralash tartibini faylga saqlab bo'lmadi.");
}

void showStatistics(void) {
    int i, best = 0, worst = 0;
    float total = 0.0f;

    if (studentCount == 0) {
        puts("Statistika uchun talabalar mavjud emas.");
        return;
    }

    for (i = 0; i < studentCount; i++) {
        total += students[i].grade;
        if (students[i].grade > students[best].grade) best = i;
        if (students[i].grade < students[worst].grade) worst = i;
    }

    printf("\n===== STATISTIKA =====\n");
    printf("Talabalar soni: %d\n", studentCount);
    printf("O'rtacha baho: %.2f\n", total / studentCount);
    printf("Eng yuqori baho: %.2f (%s)\n",
           students[best].grade, students[best].name);
    printf("Eng past baho: %.2f (%s)\n",
           students[worst].grade, students[worst].name);
}
