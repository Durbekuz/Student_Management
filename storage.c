#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"

int saveStudents(void) {
    FILE *file = fopen(DATA_FILE, "w");
    int i;

    if (!file) {
        perror("Ma'lumot faylini saqlab bo'lmadi");
        return 0;
    }

    for (i = 0; i < studentCount; i++) {
        if (fprintf(file, "%d|%s|%d|%s|%.2f\n",
                    students[i].id, students[i].name,
                    students[i].age, students[i].group,
                    students[i].grade) < 0) {
            perror("Faylga yozishda xatolik");
            fclose(file);
            return 0;
        }
    }

    if (fclose(file) != 0) {
        perror("Faylni yopishda xatolik");
        return 0;
    }
    return 1;
}

void loadStudents(void) {
    FILE *file = fopen(DATA_FILE, "r");
    char line[512];
    Student s;

    studentCount = 0;
    if (!file) return; /* First run: file does not exist yet. */

    while (studentCount < MAX_STUDENTS && fgets(line, sizeof line, file)) {
        char *idText, *name, *ageText, *group, *gradeText;
        line[strcspn(line, "\r\n")] = '\0';

        idText = strtok(line, "|");
        name = strtok(NULL, "|");
        ageText = strtok(NULL, "|");
        group = strtok(NULL, "|");
        gradeText = strtok(NULL, "|");

        if (!idText || !name || !ageText || !group || !gradeText) continue;

        s.id = atoi(idText);
        s.age = atoi(ageText);
        s.grade = (float)atof(gradeText);

        if (s.id <= 0 || s.age <= 0 || s.grade < 0 || s.grade > 100 ||
            strlen(name) >= sizeof s.name || strlen(group) >= sizeof s.group)
            continue;

        strcpy(s.name, name);
        strcpy(s.group, group);

        /* Ignore duplicate IDs in a damaged or manually edited file. */
        {
            int duplicate = 0, i;
            for (i = 0; i < studentCount; i++) {
                if (students[i].id == s.id) { duplicate = 1; break; }
            }
            if (!duplicate) students[studentCount++] = s;
        }
    }
    fclose(file);
}
