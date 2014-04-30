/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 17:22:59 by mle-roy           #+#    #+#             */
/*   Updated: 2014/04/30 17:50:42 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <utmp.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <libft.h>
#include <fcntl.h>
#include <util.h>

int main()
{
    int fdm, fds, file;
    int pid, i;
    fd_set set;
	char	*name;
    char buf[64];

	name = ft_strnew(0);
	if ((file = open("test_1", O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
		exit(printf("exit fail"));
    if (openpty(&fdm, &fds, name, NULL, NULL))
      exit(1);
	printf("Script started, output file is %s\n", name);
    if ((pid = fork()) < 0)
      exit(2);
    if (!pid) {
      // child
      close(fdm);
      login_tty(fds);
      execl("/bin/zsh", "zsh", NULL);
      exit(3);
    }
    /* father: copy stdin/out to/from master */
    close(fds); system("stty raw -echo");
    FD_ZERO(&set);
    while (waitpid(pid, &i, WNOHANG)!=pid) {
      FD_SET(0, &set);
      FD_SET(fdm, &set);
      select(fdm+1, &set, NULL, NULL, NULL);
      if (FD_ISSET(0, &set)) {
          i = read(0, buf, 64);
          if (i>0)
			  write(fdm, buf, i);
      }
      if (FD_ISSET(fdm, &set)) {
          i = read(fdm, buf, 64);
          if (i>0)
		  {
			  write(1, buf, i);
			  write(file, buf, i);
		  }
      }
    }
	printf("\nScript done, output file is %s", name);
    system("stty sane");
    exit(0);
}
