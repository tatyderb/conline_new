#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 100

char *sex(char *otch);

struct fio
{
        char sname[N];
        char otch[N];
        char name[N];
        char sex[N];
};

int main(int argc, char const *argv[])
{
        struct fio * a;
        int n, male = 0, female = 0;
        scanf("%d ", &n);

        a = calloc(n, sizeof(struct fio));

        for (int i = 0; i < n; i++)
        {
                scanf("%99s %99s %99s", a[i].name, a[i].otch, a[i].sname);

                if (0 == strcmp("ич", sex(a[i].otch))) {
                        male++;
                        //a[i].sex = "м";
                        strcpy(a[i].sex, "м");
                }
                else {
                        female++;
                        //a[i].sex = "ж";
                        strcpy(a[i].sex, "ж");
                }

        }

        for (int i = 0; i < n; i++)
        {
                printf("%s %s %s %s\n", a[i].sname, a[i].name, a[i].otch, a[i].sex);
        }

        printf("%d %d\n", male, female);
        free(a);

        return 0;
}

char *sex(char *otch) {
        int end_len = strlen("ич");
        char *prov;

        prov = otch + strlen(otch) - end_len;

        return prov;

}