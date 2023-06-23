#ifndef MINISHELL_H
# define MINISHELL_H

/* ---------------------- Bibliothèque----------------------------*/
# include <stdio.h>
# include <fcntl.h>
# include <curses.h>
// # include <term.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <termios.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/resource.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "./libft/include/libft.h"

# define SUCCESS 0

# define RESET "\033[0;39m"
# define GRAY "\033[0;90m"
# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"
# define MAGENTA "\033[0;95m"
# define CYAN "\033[0;96m"
# define WHITE "\033[0;97m"

//int	g_errno;
extern int g_errno;

/* ----------- ENUM -> Type Token --------------- */
enum e_token
{
	WORD,
	S_QUOTE,
	D_QUOTE,
	RED_IN,
	RED_OUT,
	HERE_DOC,
	APPEND,
	//SPACE,
	SPACEE,
	PIPE
}	;

/*------------- Stucture token ------------*/
typedef struct s_tok
{
	char			*tok;
	enum e_token	type;
	struct s_tok	*next;
}	t_tok;

/* ----------- Structure listes --------------- */
typedef t_dlist	t_env;

/* ----------- Structure parsing --------------- */
typedef struct s_shell
{
	int		child;
	int		status;
	char	cwd[1024];
	char	**arg;
	char	*cmd;
	t_env	*env;
	t_tok	*token;
	t_dlist	*trash_lst;
}	t_shell;

/*------------- Stucture executions ------------*/
typedef struct s_exec
{
	int		idx;
	int		number_of_pipes;
	char	**tab_cmd;
	char	**cmd_n_arg;
	char	**env_cpy;
	char	*path;
	char	**access_path;
	char	*cmd_path;
	char	**redi_infile;
	char	**redi_outfile;
	char	**heredoc;
	char	*str_heredoc;
	int		cmd_number;
	t_dlist	**trash_lst_exe;
}	t_exec;

typedef struct s_pipe
{
	int		fd_pipe1[2];
	int		fd_pipe2[2];
	int		fd_in;
	int		fd_out;
	char	*infile;
	char	*outfile;
	t_exec	exec_info;
}	t_pipe;

/* ---------------- Builtings ------------------ */
void		echo_minishell(t_shell *info);
void		cd_minishell(t_shell *info);
void		env_minishell(t_shell *info);
void		pwd_minishell(t_shell *info);
void		exit_minishell(t_shell *info);
void		unset_minishell(t_shell **info);
void		export_minishell(t_shell *info);

/* -------------- Fonctions principales -----------------------*/
int			parse_builtins(t_shell *info);
int			parse_shell(char *buff, t_shell *info);
void		init_shell(t_shell *info, char **envp);
int 		shell_execution(t_exec *info_exec, char **env, t_shell *info);

/* -------------- Fonctions parsing -----------------------*/
char		*ft_word(char *str, t_shell *info);
char		*ft_squote(char *str, t_shell *info);
char		*ft_dquote(char *str, t_shell *info);
int			check_syntax(t_tok *lst, t_dlist **trash);
char		*red_in(char *str, t_tok **lst, t_dlist **trash);
char		*red_out(char *str, t_tok **lst, t_dlist **trash);
char		*ft_pipe(char *str, t_tok **lst, t_dlist **trash);
char		*ft_space(char *str, t_tok **lst, t_dlist **trash);

/* -------------- Fonctions utilitaires -----------------------*/
int			ft_issigle(char c);
int			ft_isquote(char c);
int			ft_isword(int token);
int			ft_quotelen(char *str);
int			ft_tabsize(char **tab);
int			check_printchar(char c);
int			ft_checkquote(char *str);
int			ft_isparsing_char(char c);
char		**ft_split_var(char *var);
void		ft_strswap(char **s1, char **s2);
int			ft_error_msg(int errno, char *str);
int			found_char(const char *str, int c);

/* -------------- Fonctions utiles liste -----------------------*/
void		tok_clearlst(t_tok **lst);
void		tok_addlst(t_tok **lst, t_tok *token);
void		tab_to_lst(t_shell *info, char **envp);
char		**lst_to_tab(t_env *lst, t_shell *info);
t_list		*find_var_env(t_env *env, char *var, int if_dd);
char    	**tokenlst_to_tab(t_tok *token, t_dlist **trash);
t_tok		*new_node(char *str, int token, t_dlist **trash);
void		str_to_node(char *str, t_list *node, t_shell *info);
void		fill_node(t_list *node, char *s1, char *s2, int if_var);
void		creat_and_add(char *tmp, char *str, int type, int index, t_shell *info);

/* -------------- Fonctions test -----------------------*/
void		test(char *str, char *fonction);
void		print_tab(char **tab, char *ft);
void		print_list(t_env *lst, char *ft);
void		print_token(t_tok **lst, char *ft);

/* -------------- Fonctions d'execution ---------------------*/
char		*get_path(char **env);
void		command_not_found(char *cmd);
char		**handle_infile(t_exec *exe);
char		**handle_outfile(t_exec *exe);
int			handle_heredoc(t_exec *d_exe);
void		handle_dup_fd_single_cmd(t_pipe *d_pip, t_exec *exe);
void		close_pipes(t_pipe *d, int process);
void		handle_pipes(int (*fd1)[2], int (*fd2)[2]);
char		*strjoin_exec(char const *s1, char const *s2);
void		handle_redirections(t_exec *exe, t_pipe *pipe);
void		error_infile_outfile(int error_nb, t_exec *exe);
void		last_cmd(t_pipe *d, char *cmd_path, int process, t_exec *d_exe);
char		**ft_split_exec(const char *str, char c, int var);
void		middle_cmd(t_pipe *d, char *cmd_path, int process);
void		first_cmd(t_pipe *d, char *cmd_path, t_exec *d_exe);
void		init_struc_exec(t_exec *d, t_shell infos, char **env);
char		*get_cmd_path(char *cmd, t_exec *info, t_dlist **trash);
int			is_builtins(char *cmd_to_compare, char** builtins_list);
void		builtins_exec(char *builtins_name, t_shell *info, char **cmd);
void		init_struc_pipe(t_pipe *d, char *infile, char *outfile, t_exec *exe);
void		builtins_1(t_pipe *d, t_exec *d_exe, t_shell *d_shell, char *cmd);
void		builtins_0(t_pipe *d_pip, t_exec *d_exe, t_shell *d_shell, char *cmd);
void		child_process_1(t_pipe *d, t_exec *d_exe, t_shell *d_shell, char *cmd);
void		child_process_0(t_pipe *d_pip, t_exec *d_exe, t_shell *d_shell, char *cmd);
void		handle_single_cmd(t_pipe *d_pip, t_exec *d_exe, t_shell *d_shell, char *cmd);

#endif