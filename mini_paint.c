#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

typedef struct s_valeur
{
    int wight;
    int height;
    int val_file;
    float   pos_hor;
    float   pos_vert;
    float   radius;
    char    deb;
    char    **tab;
    char    back;
    char    background;
    FILE    *files;
}           t_valeur;

int ft_remplissage(t_valeur *valeur)
{
    int i = 0;
    int j = 0;

    valeur->val_file = fscanf(valeur->files, "%d %d %c\n", &valeur->wight, &valeur->height, &valeur->back);
    if (valeur->val_file != 3)
        return (1);
    if (valeur->wight <= 0 || valeur->wight > 300)
        return (1);
    if (valeur->height <= 0 || valeur->height > 300)
        return (1);
    valeur->tab = malloc(valeur->height * sizeof(char *));
    if (!valeur->tab)
        return (1);
    while (i < valeur->height)
    {
        valeur->tab[i] = malloc(valeur->wight * sizeof(char));
        i++;
    }
    i = 0;
    while (i < valeur->height)
    {
        j = 0;
        while (j < valeur->wight)
        {
            valeur->tab[i][j] = valeur->back;
            j++;
        }
        i++;
    }
    return (0);
}

int ft_rond(t_valeur *valeur)
{
    int i = 0;
    int j = 0;
    int tmp = 0;
    float val = 0;
    while (1)
    {
        tmp = fscanf(valeur->files, "%c %f %f %f %c\n", &valeur->deb, &valeur->pos_hor, &valeur->pos_vert, &valeur->radius, &valeur->background);
        if (tmp != 5)
            break ;
        if (valeur->deb != 'C' && valeur->deb != 'c')
            return (0);
        if (valeur->radius <= 0)
            return (0);
        i = 0;
        while(i < valeur->height)
        {
            j = 0;
            while (j < valeur->wight)
            {
                val = sqrtf(powf(j - valeur->pos_hor, 2) + powf(i - valeur->pos_vert, 2));
                if (valeur->deb == 'C' && val <= valeur->radius)
                    valeur->tab[i][j] = valeur->background;
                else if (valeur->deb == 'c' && val <= valeur->radius && val > valeur->radius - 1)
                    valeur->tab[i][j] = valeur->background;
                j++;
            }
            i++;
        }
    }
    return (tmp == EOF);
}

void ft_affiche_tab(t_valeur *valeur)
{
    int i = 0;
    int j = 0;

    while (i < valeur->height)
    {
        j = 0;
        while (j < valeur->wight)
        {
            write (1, &valeur->tab[i][j], 1);
            j++;
        }
        write (1, "\n", 1);
        i++;
    }
}

void ft_free(t_valeur *valeur)
{
    int i = 0;

    fclose(valeur->files);
    if (!valeur->tab)
        return ;
    while (i < valeur->height)
    {
        free(valeur->tab[i]);
        i++;
    }
    free(valeur->tab);
}

int main(int argc, char **argv)
{
    t_valeur valeur;

    if (argc != 2)
    {
        write(1, "Error: Operation file corrupted\n", 32);
        ft_free(&valeur);
        return (1); 
    }
    valeur.files = fopen(argv[1], "r");
    if (!fopen(argv[1], "r"))
    {
        write(1, "Error: Operation file corrupted\n", 32);
        ft_free(&valeur);
        return (1);
    }
    if (ft_remplissage(&valeur) == 1)
    {
        write(1, "Error: Operation file corrupted\n", 32);
        ft_free(&valeur);
        return (1);     
    }
    if (!ft_rond(&valeur))
    {
        write(1, "Error: Operation file corrupted\n", 32);
        ft_free(&valeur);
        return (1);         
    }
    ft_affiche_tab(&valeur);
    ft_free(&valeur);
    return (0);
}