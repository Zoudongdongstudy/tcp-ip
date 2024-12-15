#ifndef __SKEL_H__
#define __SKEL_H__
/* UNIX version */

#define INIT()          ( program_name = \
                         strrchr(argv[0], '/'))?\
                         program_name++ : \
                         ( program_name = argv[0])
                        

// chatgpt 写的
// #define INIT()      ( program_name = \
// (strrchr(argv[0], '/')) ? (program_name = strrchr(argv[0], '/') + 1) : \
// (program_name = argv[0]))

#define EXIT(s)         exit(s)
#define CLOSE(s)        if (close(s))   error(1, error, \
                        "close faile")
#define set_error(e)    error = (e)
#define isvalidsock(s)  ((s) >= 0)
typedef int SOCKET;

#endif /* __SKEL_H__ */