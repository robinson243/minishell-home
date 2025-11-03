/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:01:15 by romukena          #+#    #+#             */
/*   Updated: 2025/11/03 13:41:27 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
/*
int main(void)
{
    // Création manuelle de nodes simulant : "ls -l | grep txt > out.txt"
    t_node n1 = {WORD, "ls", 0, NULL};
    t_node n2 = {WORD, "-l", 0, NULL};
    t_node n3 = {PIPE, "|", 0, NULL};
    t_node n4 = {WORD, "grep", 0, NULL};
    t_node n5 = {WORD, "txt", 0, NULL};
    t_node n6 = {REDIR_OUT, "out.txt", 0, NULL};

    // Chaînage
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = &n5;
    n5.next = &n6;

    // Pointeur pour parser
    t_node *head = &n1;
    t_cmd *cmd_list = parser(&head);

    // Affichage des commandes
    for (t_cmd *c = cmd_list; c; c = c->next)
    {
        // Arguments
        if (c->argv)
        {
            for (int i = 0; c->argv[i]; i++)
                printf("argv[%d]: %s\n", i, c->argv[i]);
        }

        // Redirections
        if (c->redir)
        {
            for (t_redir *r = c->redir; r; r = r->next)
                printf("redir type=%d file=%s\n", r->type, r->file);
        }

        // Pipe
        printf("pipe_out=%d\n\n", c->pipe_out);
    }

    return 0;
}
*/