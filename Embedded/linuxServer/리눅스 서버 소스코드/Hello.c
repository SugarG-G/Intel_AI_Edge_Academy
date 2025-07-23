#include <stdio.h>
char *user_strcpy(char *fp, const char *str){
    char *cfp = fp;

    while(*str != 0 ){
        *(cfp++) = *(str++);
    }

    return fp;
}

char *user_strcat(char *fp, const char *str){
    char *cfp = fp;

    while(*fp != 0 ){
        fp++;
    }
    while(*str != 0){
        *(fp++) = *(str++);
    }

    return fp;
}

int main(){
    char fruit[20] = "straw";
    char *fp = fruit;

    user_strcpy(fp, "starwberry");
    printf("%s\n", fruit);
    printf("%s",user_strcat(fp, "starwberry"));

    printf("%s", fruit);
}