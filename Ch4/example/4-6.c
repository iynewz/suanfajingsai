// A Typical Homework, UVa 12412
#include<stdio.h> 
#include<string.h>

#define MAX_LEN 22
#define EPS 1.0E-3

typedef struct {
    char SID[MAX_LEN]; 
    int CID;
    char name[MAX_LEN];
    int scores[5];
    int total;
    float avg;
    int is_removed;
} Student;

Student students[1000]; // 全局学生数组
int student_count = 0;  // 当前学生数量

void print_menu() {
    printf("Welcome to Student Performance Management System (SPMS).\n\n1 - Add\n2 - Remove\n3 - Query\n4 - Show ranking\n5 - Show Statistics\n0 - Exit\n\n");
}

int get_rank(int curr_total) {
    int rank = 1;
    for (int i = 0; i < student_count; i++) {
        if (students[i].is_removed == 0) {
            if (curr_total < students[i].total) {
                rank++;
            }
        }
    }
    return rank;
}


void add() {
    char SID[MAX_LEN];
    int CID;
    char name[20];
    int scores[4];

    for (;;) {
        printf("Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");
        scanf("%s", SID);
        if (strcmp(SID, "0") == 0) break;
        // 检查 SID 是否重复
        int duplicate = 0;
        for (int i = 0; i < student_count; ++i) {
            if (strcmp(students[i].SID, SID) == 0 && students[i].is_removed == 0) {
                duplicate = 1;
                break;
            }
        }
        if (duplicate) {
            printf("Duplicated SID.\n");
            while (getchar() != '\n'); // 清除输入缓冲区的剩余内容
            continue; // 跳过当前迭代，重新开始输入
        }

        scanf("%d %s %d %d %d %d", &CID, name, &scores[0], &scores[1], &scores[2], &scores[3]);
        int total = scores[0] + scores[1] + scores[2] + scores[3];
        float avg = total / 4.0 + EPS;
        Student new_student;
        strcpy(new_student.SID, SID);
        new_student.CID = CID;
        strcpy(new_student.name, name);
        memcpy(new_student.scores, scores, sizeof(scores));
        new_student.is_removed = 0;
        new_student.total = total;
        new_student.avg = avg;
        students[student_count++] = new_student;
    }
}


void DQ(int isq) {
    char s[MAX_LEN];
    for (;;) {
        printf("Please enter SID or name. Enter 0 to finish.\n");
        scanf("%s", s);
        if (strcmp(s, "0") == 0) break;
        int removed_count = 0;
        for (int i = 0; i < student_count; i++) {
            if (students[i].is_removed == 0) {
                if ((strcmp(students[i].SID, s) == 0) || (strcmp(students[i].name, s) == 0)) {
                    // find the target
                    if (isq) {
                        //e.g.: 2 0022334455 1 Tom 59 72 60 81 272 68.00
                        int rank = get_rank(students[i].total);
                        printf("%d %s %d %s %d %d %d %d %d %.2f\n", rank, students[i].SID, students[i].CID, students[i].name, students[i].scores[0], students[i].scores[1], students[i].scores[2], students[i].scores[3], students[i].total, students[i].avg );
                    }
                    else {
                        students[i].is_removed = 1;
                        removed_count++;
                    }
                }
            }

        }
        if (!isq) {
            printf("%d student(s) removed.\n", removed_count);
        }
    }
}

void show_ranking() {
    printf("Showing the ranklist hurts students' self-esteem. Don't do that.\n");
}

void show_stat() {
    printf("Please enter class ID, 0 for the whole statistics.\n");
    int CID;
    scanf("%d", &CID);
    int Chinese_total = 0;
    int Chinese_passed = 0;
    int Mathematics_total = 0;
    int Mathematics_passed = 0;
    int English_total = 0;
    int English_passed = 0;
    int Programming_total = 0;
    int Programming_passed = 0;

    int pass_1 = 0;
    int pass_2 = 0;
    int pass_3 = 0;
    int pass_all = 0;

    
    int student_count_in_class = 0;

    for (int i = 0; i < student_count; i++) {
        if(students[i].is_removed == 0 && (students[i].CID == CID || CID == 0)) {
            student_count_in_class++;

            Chinese_total += students[i].scores[0];
            int pass_count = 0;
            if (students[i].scores[0] >= 60) {
                Chinese_passed++;
                pass_count++;
            }
            Mathematics_total += students[i].scores[1];
            if (students[i].scores[1] >= 60) {
                Mathematics_passed++;
                pass_count++;
            }
            English_total += students[i].scores[2];
            if (students[i].scores[2] >= 60) {
                English_passed++;
                pass_count++;
            }
            Programming_total += students[i].scores[3];
            if (students[i].scores[3] >= 60) {
                Programming_passed++;
                pass_count++;
            }
            if (pass_count == 4) {
                pass_1++;
                pass_2++;
                pass_3++;
                pass_all++;
            } else if (pass_count == 3) {
                pass_1++;
                pass_2++;
                pass_3++;
            } else if (pass_count == 2) {
                pass_1++;
                pass_2++;
            } else if (pass_count == 1) {
                pass_1++;
            }
        }
    }
    printf("Chinese\nAverage Score: %.2f\nNumber of passed students: %d\nNumber of failed students: %d\n\n", Chinese_total * 1.0 / student_count_in_class + EPS, Chinese_passed, student_count_in_class - Chinese_passed);
    printf("Mathematics\nAverage Score: %.2f\nNumber of passed students: %d\nNumber of failed students: %d\n\n", Mathematics_total * 1.0 / student_count_in_class+ EPS, Mathematics_passed, student_count_in_class - Mathematics_passed);
    printf("English\nAverage Score: %.2f\nNumber of passed students: %d\nNumber of failed students: %d\n\n", English_total * 1.0 / student_count_in_class+ EPS, English_passed, student_count_in_class - English_passed);
    printf("Programming\nAverage Score: %.2f\nNumber of passed students: %d\nNumber of failed students: %d\n\n", Programming_total * 1.0 / student_count_in_class+ EPS, Programming_passed, student_count_in_class - Programming_passed);

    printf("Overall:\nNumber of students who passed all subjects: %d\nNumber of students who passed 3 or more subjects: %d\nNumber of students who passed 2 or more subjects: %d\nNumber of students who passed 1 or more subjects: %d\nNumber of students who failed all subjects: %d\n\n", pass_all, pass_3, pass_2, pass_1, student_count_in_class - pass_1);

}

int main() {
    for (;;) {
        int choice;
        print_menu();
        scanf("%d", &choice);
        if (choice == 0) break;
        if (choice == 1) add();
        if (choice == 2) DQ(0); // remove
        if (choice == 3) DQ(1); //query
        if (choice == 4) show_ranking();
        if (choice == 5) show_stat();
    }
    return 0;
}