/*#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main()
{
    //int i = 0;

   if (chdir("srcs") == 0)
        printf("ok");
    else
        perror("erro");
    //chdir("home/vbritto-/Documents/42/minishell/srcs");
}*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *ent;

    // Abre o diretório atual (".")
    dir = opendir(".");
    if (dir == NULL) {
        perror("Não foi possível abrir o diretório");
        return EXIT_FAILURE;
    }

    // Lê as entradas do diretório
    while ((ent = readdir(dir)) != NULL) {
        // Imprime o nome da entrada
        printf("Nome: %s\n", ent->d_name);
        /*
        // Imprime o tipo de arquivo
        switch (ent->d_type) {
            case DT_REG:
                printf("Tipo: Arquivo regular\n");
                break;
            case DT_DIR:
                printf("Tipo: Diretório\n");
                break;
            case DT_LNK:
                printf("Tipo: Link simbólico\n");
                break;
            default:
                printf("Tipo: Outro\n");
                break;
        }*/

        // Imprime o número do inode
       // printf("Inode: %lu\n", ent->d_ino);
    }

    // Fecha o diretório
    if (closedir(dir) == -1) {
        perror("Erro ao fechar o diretório");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}