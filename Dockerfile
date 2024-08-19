FROM debian:12

RUN apt update -y && apt upgrade -y

RUN apt install libreadline-dev -y

RUN apt install -y gcc make

RUN mkdir /minishell

COPY libft /minishell/libft

COPY *.c /minishell/

COPY *.h /minishell/

COPY Makefile /minishell/

COPY readline /minishell/readline

COPY exec /minishell/exec

WORKDIR /minishell

RUN make

CMD ["./minishell"]

