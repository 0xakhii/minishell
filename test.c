t_vals    *tokens(t_lex **lexer, char *str, int type)
{
    go_next(*lexer);
    return (initialize_token(str, type));
}

t_vals    *others(t_lex *lexer)
{
    if (lexer->l == '|')
        return (tokens(&lexer, "|", V_PIPE));
    if (lexer->l == '<')
    {
        go_next(lexer);
        if (lexer->l == '<')
            return (tokens(&lexer, "<<", V_HDK));
        return (initialize_token("<", V_IN_RDIR));
    }
    if (lexer->l == '>')
    {
        go_next(lexer);
        if (lexer->l == '>')
            return (tokens(&lexer, ">>", V_APP));
        return (initialize_token(">", V_OUT_RDIR));
    }
    else
        return (initialize_token("newline", V_EOF));
}

t_vals    *select_token(t_lex *lexer)
{
    t_vals    *token;
    char    *str;
    char    c;

    str = NULL;
    while (lexer->l && (lexer->l == ' ' || lexer->l == '\t'))
        go_next(lexer);
    c = 0;
    while (lexer->l)
    {
        if ((lexer->l == '\"' || lexer->l == '\'') && c == 0)
            c = lexer->l;
        else if (c != 0 && lexer->l == c)
            c = 0;
        if ((lexer->l == '|' || lexer->l == '<'
                || lexer->l == '>' || lexer->l == ' ') && c == 0)
            break ;
        str = add_str(str, lexer->l);
        go_next(lexer);
    }
    if (str)
        token = initialize_token(str, V_STR);
    else
        token = others(lexer);
    return (token);
}

t_list    *lexecal_analyzer(char *str)
{
    t_lex    lexer;
    t_vals    *token;
    t_list    *list;

    if (!str)
        return (NULL);
    initialize_lexer(&lexer, str);
    list = NULL;
    while (lexer.l != '\0')
    {
        token = select_token(&lexer);
        ft_lstadd_back(&list, ft_lstnew(token));
    }
    token = initialize_token(NULL, V_EOF);
    ft_lstadd_back(&list, ft_lstnew(token));
    return (list);
}
t_vals    *initialize_token(char *str, int type)
{
    t_vals    *token;

    token = malloc(sizeof(t_vals));
    if (!token)
        return (NULL);
    token->e_token = type;
    token->val = str;
    return (token);
}
void    initialize_lexer(t_lex *lexer, char *str)
{
    lexer->fill = str;
    lexer->nxt = 0;
    lexer->l = lexer->fill[lexer->nxt];
}

void    go_next(t_lex *lexer)
{
    lexer->nxt++;
    lexer->l = lexer->fill[lexer->nxt];
}

t_vals    *initialize_token(char *str, int type)
{
    t_vals    *token;

    token = malloc(sizeof(t_vals));
    if (!token)
        return (NULL);
    token->e_token = type;
    token->val = str;
    return (token);
}
char    *add_str(char *str, char c)
{
    char    *charachter;
    char    *save;

    charachter = malloc(sizeof(char) * 2);
    charachter[0] = c;
    charachter[1] = '\0';
    if (!str)
    {
        str = charachter;
        return (str);
    }
    else
    {
        save = str;
        str = ft_strjoin(str, charachter);
        free(save);
        free(charachter);
    }
    return (str);
}