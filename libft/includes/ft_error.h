/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walter <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:10:23 by walter            #+#    #+#             */
/*   Updated: 2025/03/04 11:16:14 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# define ERR_HD "\e[0;31m\e[1mPipeX - \e[0m"

# define DENIED_PERM "Permission denied"
# define BAD_FD "Bad file descriptor"
# define REDIR "Redirection"
# define INFILE "Infile"
# define OUTFILE "Outfile"
# define PIPE_FAILED "pipe failed"

# define CMD_NOT_FND "Command not found"
# define ENV_NOT_FND "Command not found (no environment provided)"

# define TRY_AGAIN "Try again"

# define MALLOC "Malloc failed"
# define PARSING_FAILED "Parsing failed"

#endif
