#include "server.hh"

int Task_listen_echo::task_run(Buff *buff,int fd) {
    //cout << "into Task_listen task_run()" << endl;
    int connfd = 0;
	if((connfd = accept(fd,NULL,NULL)) < 0)
		return 0;
    setnoblock(connfd);
    Task_echo *task_echo_temp = new Task_echo;
    Agent_connect *agent_connect_pr = new Agent_connect(connfd,task_echo_temp);
    epoll_login(agent_connect_pr, connfd, EPOLLIN | EPOLLOUT, EPOLL_CTL_ADD);
    return 0;
}

int Task_echo::task_run(Buff *buff,int fd,int first_flag) {
    int num = min((buff->from_in_flag - buff->from_out_flag),(&(buff->to_socket_buff[BUFF_SIZE]) 
    - buff->to_in_flag));
    
    //cout << buff->from_in_flag - buff->from_out_flag << "and" << (&(buff->to_socket_buff[BUFF_SIZE]) 
    //- buff->to_in_flag) << " min is:" << num << endl;
    
    //cout << "into Task_echo task_run()" << endl;
    buff->readin(buff->from_out_flag,buff->to_in_flag,num);
    return 0;
}

int Task_listen_trans::task_run(Buff *buff,int fd){
    int connfd = 0;
	if((connfd = accept(fd,NULL,NULL)) < 0)
		return 0;
    setnoblock(connfd);
    Task_trans *task_trans_temp = new Task_trans;
    Agent_connect *agent_connect_pr = new Agent_connect(connfd,task_trans_temp);
    epoll_login(agent_connect_pr, connfd, EPOLLIN | EPOLLOUT, EPOLL_CTL_ADD);
    return 0;
}
int Task_trans::task_run(Buff *buff,int fd,int first_flag){
    if(this->head_read_flag == 0){
        read_head(buff);
        //register_table.insert(pair<int,Agent_connect*>())
    }//发送登陆报文
}
void Task_trans::read_head(Buff *buff){
    //buff->readin(buff->from_out_flag,&(this->from_buff_head),HEADLEN);
    strncpy(buff->from_out_flag,4)
}