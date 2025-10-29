/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:01:15 by romukena          #+#    #+#             */
/*   Updated: 2025/10/29 17:41:26 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	main(void)
{
	t_node	*head;
	char	*str;
	int		i;

char *tests[] = {
    "echo Bonjour",                          // Commande simple
    "echo \"42 Paris\" 'Piscine C'",        // Double + simple quotes fermées
    "ls -l /tmp | grep txt > out.txt",      // Pipe et redirection
    "echo $USER $HOME $PWD",                 // Variables à expanser (quoted=0)
    "echo \"Mix de$USER et 'quotes'\"",     // Variable dans double quotes, simple quotes littérales
    "echo 'Test $HOME'",                     // Simple quotes, pas d’expansion
    "echo \"Test $HOME\"",                   // Double quotes, expansion
    "echo 'unclosed",                        // Simple quote non fermée
    "echo \"unclosed",                       // Double quote non fermée
    "cat < file.txt > output.txt",           // Redirections
    "echo salut$USER<<$PWD",                 // Variable + heredoc operator
	"echo mix $USER\"test\"'ouf'",
	"cat 'miam'\"ouf\"",
    "echo 'adjacent''quotes'",               // Quotes simples adjacentes
    "echo \"adjacent\"\"double\"",           // Quotes doubles adjacentes
    "echo Mixed$USER\"Test\"'$HOME'",        // Mix quotes et variables
    "ls | grep \"foo\"",                     // Pipe + quote
    "echo \"  spaced text \"",               // Espaces dans quotes doubles
    "echo ''",                              // Empty simple quotes
    "echo \"\"",                            // Empty double quotes
    "echo $USER$HOME$PWD",                  // Variables concaténées
    "export VAR=test; echo $VAR",            // Point important: pas de ; validé, test to see ignoring
    "echo escaped\\$USER",                   // échappement backslash ($ non expansé)
    "echo \"Nested 'quotes' inside\"",       // Quotes imbriquées dans doubles quotes
    "echo 'Nested \"quotes\" inside'",       // Quotes imbriquées dans simples quotes
    "cat file.txt | grep 'pattern'",         // Pipe + quotes
	"cat<file",                              // Redirection collée → mot unique
"cat < file",                             // Redirection séparée → token <
"echo hello>>file",                       // Append collé → mot unique
"echo hello >> file",                      // Append séparé → token >>
"echo hello|grep h",                      // Pipe collé → mot unique
"echo hello | grep h",                     // Pipe séparé → token |
"echo 'single''adjacent'",              // Simple quotes collées
"echo \"double\"\"adjacent\"",          // Double quotes collées
"echo 'mix\"quotes\"inside'",           // Quotes imbriquées simples+ doubles
"echo \"mix'quotes'inside\"",           // Quotes imbriquées doubles+ simples
"echo \"variable$USERinside\"",          // Variable dans double quotes
"echo 'variable$USERinside'", // Variable dans simple quotes (pas expand)
"echo $USER$HOME",                       // Variables concaténées
"echo \"space $USER inside\"",           // Espaces dans double quotes+ variable
"echo '' '' ''",                         // Plusieurs simples quotes vides
"echo \"\" \"\" \"\"",                   // Plusieurs doubles quotes vides
"echo \"nested 'single' and $HOME\"",    // Mix nested + variable
"echo 'nested \"double\" and $HOME'",    // Mix nested + variable non expand
"echo $0 $? $52",


	NULL
};
	i = 0;
	while (tests[i])
	{
		head = NULL;
		printf("=== TEST %d ===\n", i + 1);
		printf("Input: [%s]\n", tests[i]);
		lexer(tests[i], &head);
		handle_expands(&head);
		print_list(&head);
		clear_nodes(&head);
		printf("\n");
		i++;
	}
	head = NULL;
	// // int k;
	// // k = 0;
	// // str = "start$USERend";
	// // char *expanded = expanded_char(str);
	// // printf("%s", expanded);
	// // // lexer(str, &head);
	// // // print_list(&head);
	// // // clear_nodes(&head);

	return (0);
}