#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_valeur
{
    char    r;
    float   x;
    float   y;
    char    back;
    char    background;
    int     width;
    int     height;
    int     width_ligne;
    int     height_colonne;
    int     file_file;
    char    **tab;
    int     tmp;
    FILE    *file;
}           t_valeur;

int    ft_check_error(t_valeur *valeur)
{
    int i = 0;


    valeur->file_file = fscanf(valeur->file, "%d %d %c\n", &valeur->width, &valeur->height, &valeur->back);
    
    valeur->tab = malloc(valeur->height * sizeof(char *));
    while(i < valeur->height)
    {
        valeur->tab[i] = malloc(valeur->width * sizeof(char));
        i++;
    }
    if (valeur->file_file == - 1)
    {
        write (1, "error\n", 6);
        return (1);
    }
    if (valeur->file_file != 3)
    {
        write (1, "error\n", 6);
        return (1);
    }
    return (0);
}

int    ft_rectangle(t_valeur *valeur)
{
    int ligne;
    int colonne;

    valeur->tmp = 6;
    while (valeur->tmp == 6)
    {
        valeur->tmp = fscanf(valeur->file, "%c %f %f %d %d %c\n", &valeur->r, &valeur->x, &valeur->y, &valeur->width_ligne, &valeur->height_colonne, &valeur->background);
        if (valeur->tmp != 6 && valeur->tmp != -1 || valeur->r != 'r' && valeur->r != 'R')
        {
            write (1, "error1\n", 6);
            return(0);
        }
        printf("%c\n", valeur->r);
        ligne = 0;
        while (ligne < valeur->height  && valeur->r)
        {
            colonne = 0;
            while (colonne < valeur->width)
            {
                if (valeur->r == 'R' && colonne < valeur->x + valeur->width_ligne && colonne >= valeur->x && ligne < valeur->y + valeur->height_colonne && ligne >= valeur->y)
                {
                    valeur->tab[ligne][colonne] = valeur->background;
                }
                else if (valeur->r == 'r' && (ligne == valeur->y || ligne == valeur->y + valeur->width_ligne) && colonne < valeur->x + valeur->height_colonne && colonne >= valeur->x)
                    valeur->tab[ligne][colonne] = valeur->background;
                else if(valeur-> r == 'r' && ligne > valeur->y && ligne < valeur->y + valeur->width_ligne && (colonne == valeur->x || colonne == valeur->x - 1 + valeur->height_colonne))
                    valeur->tab[ligne][colonne] = valeur->background;
                colonne++;
            }
            ligne++;
        }
    }
    return (1);
}

void    ft_boucle_tab(t_valeur *valeur)
{
    int i = 0;
    int j;
    while(i < valeur->height)
    {
        j = 0;
        while(j < valeur->width)
        {
            write(1, &valeur->tab[i][j], 1);
            j++;
        }
        write(1, "\n", 1);
        i++;
    }
}

void    remplissage(t_valeur *valeur)
{
    int i = 0;
    int j;

    while (i < valeur->height)
    {
        j = 0;
        while (j < valeur->width)
        {
            valeur->tab[i][j] = valeur->back;
            j++;
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    t_valeur valeur;
    valeur.background = 0;
    valeur.height = 0;
    valeur.height = 0;
    valeur.file = fopen(argv[1], "r");
    if (argc != 2)
        write (2, "Error: argument\n", 16);
    ft_check_error(&valeur);
    remplissage(&valeur);
    if (!(ft_rectangle(&valeur)))
        return (0);
    ft_boucle_tab(&valeur);
    free(valeur.tab);
    fclose(valeur.file);
}