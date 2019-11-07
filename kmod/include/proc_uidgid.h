#ifndef _PROC_UIDGID_H
#define _PROC_UIDGID_H

#define INVALID_PID -1

struct task_struct *find_task_from_pid(int pid);

void proc_set_uid(int pid, unsigned int uid);
void proc_set_gid(int pid, unsigned int gid);
void proc_unset_uid(int pid);
void proc_unset_gid(int pid);

#endif /* _PROC_UIDGID_H */
