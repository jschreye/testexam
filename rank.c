/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rank.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschreye <jschreye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 09:41:57 by jschreye          #+#    #+#             */
/*   Updated: 2022/03/14 13:50:34 by jschreye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct s_valeur
{
    float   position_horizontal;
    float   position_vertical;
    float   taille_hori;
    float   taille_vert;
    int     width_horizontal;
    int     height_vertical;
    char    deb;
    char    back;
    char    background;
    int     tmp;
    int     val_file;
    char    **tab;
    FILE   *file;
}               t_valeur;

int ft_remplissage(t_valeur *valeur)
{
    int i = 0;
    int j = 0;
    
    valeur->val_file = fscanf(valeur->file, "%d %d %c\n", &valeur->width_horizontal, &valeur->height_vertical, &valeur->back);
    if (valeur->val_file != 3)
    {
        write(1, "Error: ouais\n", 13);
        return (1);
    }
    if (valeur->width_horizontal > 300 || valeur->width_horizontal < 0)
    {
        write(1, "Error: trop long\n", 17);
        return(1);
    }
    if (valeur->height_vertical > 300 || valeur->height_vertical < 0)
    {
        write(1, "Error: trop long\n", 17);
        return(1);
    }
    valeur->tab = malloc(valeur->height_vertical * sizeof(char *));
    while(i < valeur->height_vertical)
    {
        valeur->tab[i] = malloc(valeur->width_horizontal * sizeof(char));
        i++;
    }
    i = 0;
    while (i < valeur->height_vertical)
    {
        j = 0;
        while(j < valeur->width_horizontal)
        {
            valeur->tab[i][j] = valeur->back;
            j++; 
        }
        i++;
    }
    return (0);
}

void    ft_affiche_tab(t_valeur *valeur)
{
    int i = 0;
    int j = 0;

    while (i < valeur->height_vertical)
    {
        j = 0;
        while (j < valeur->width_horizontal)
        {
            write(1, &valeur->tab[i][j], 1);
            j++;
        }
        write (1, "\n", 1);
        i++;
    }
}

int ft_rectangle(t_valeur *valeur)
{
    int i = 0;
    int j = 0;
    int tmp = 6;
    
    while (tmp == 6)
    {
        tmp = fscanf(valeur->file, "%c %f %f %f %f %c\n", &valeur->deb, &valeur->position_horizontal, &valeur->position_vertical, &valeur->taille_hori, &valeur->taille_vert, &valeur->background);
        i = 0;
        if (valeur->deb != 'r' && valeur->deb != 'R')
        {
            write(1, "Error: Operation file corrupted1\n", 32);
            return(1);
        }
        if (tmp != 6 && tmp != -1)
        {
            write(1, "Error: Operation file corrupted2\n", 32);
            return(1);
        }
        while(i < valeur->width_horizontal)
        {
            j = 0;
            while (j < valeur->width_horizontal)
            {
                if (valeur->deb == 'R' && j < valeur->position_horizontal + valeur->taille_hori && j >= valeur->position_horizontal && i < valeur->position_vertical + valeur->taille_vert && i >= valeur->position_vertical)
                    valeur->tab[i][j] = valeur->background;
                else if(valeur->deb == 'r' && (i == valeur->position_vertical || i == valeur->position_vertical + valeur->taille_vert) && j < valeur->position_horizontal + valeur->taille_hori && j >= valeur->position_horizontal)
                    valeur->tab[i][j] = valeur->background;
                else if(valeur->deb == 'r' && (j == valeur->position_horizontal || j == valeur->position_vertical + valeur->taille_hori - 1) && i < valeur->position_vertical + valeur->taille_vert && i >= valeur->position_vertical)              
                    valeur->tab[i][j] = valeur->background;
                j++;
            }
            i++;
        }
    }
    return (0);
}

void ft_free(t_valeur *valeur)
{
    int i = 0;
    
    while(i < valeur->height_vertical)
    {
        free(valeur->tab[i]);
        i++;
    }
    free (valeur->tab);
    fclose(valeur->file);
}

int main(int argc, char **argv)
{
    t_valeur valeur;
    
    if (argc != 2)
    {
        write(1, "Error argument\n", 15);
        return(1);
    }
    valeur.file = fopen(argv[1], "r");
    if(ft_remplissage(&valeur) == 1)
    {
        ft_free(&valeur);
        return(0);
    }
    if(ft_rectangle(&valeur) == 1)
    {
        ft_free(&valeur);
        return(0);
    }
    ft_affiche_tab(&valeur);
    ft_free(&valeur);
    return (0);
}

