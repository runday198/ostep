#include <iostream>
#include <string>

#include <unistd.h>
#include <sys/wait.h>


int main() {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        std::cerr << "pipe\n";
        exit(1);
    }

    int rc1 = fork();

    if (rc1 < 0) {
        std::cerr << "fork\n";
        exit(1);
    } else if (rc1 == 0) {
        close(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

        std::cout << "This is rc1! Over\n";
    } else { 
        int rc2 = fork();

        if (rc2 < 0) {
            std::cerr << "fork\n";
            exit(1);
        } else if (rc2 == 0) {
            close(STDIN_FILENO);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            close(pipefd[1]);

            std::string a;
            std::getline(std::cin, a);

            std::cout << a << '\n';
            std::cout << "Received loud and clear! Over\n";
        } else {
            while (wait(NULL) > 0);
        }
    }
    return 0;
}