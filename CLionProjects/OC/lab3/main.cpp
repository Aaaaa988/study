#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void Batya();
void Child();

int main() {
    pid_t child_pid, parent_pid;
    int i = 0;
    fprintf(stdout, "Before recreation %i\n", parent_pid = (int) getpid());
    child_pid = fork();
    while(1)
        if(child_pid != 0)
            Batya();
        else
            Child();
    return 0;
}

void Batya(){
    fprintf(stdout, "I'm not Dead! My ID is %i\n", (int)getpid());
}

void Child(){
    fprintf(stdout, "On your Left! My ID is %i\n", (int)getpid());
}