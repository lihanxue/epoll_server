#include "server.hh"

void Agent_listen::agent_read() {
    //cout << "into Agent_listen agent_read()" << endl; 
    buff = new Buff;
    this->task->task_run(this->buff,this->fd);
}

void Agent_connect::agent_read() {
    //cout << "into Agent_connect agent_read()" << endl;
    int n;
    if(first_flag == 1){
        buff = new Buff;
        first_flag = 0;
    }
    this->buff->buff_init();
    if((n = buff->readin(this->fd,this->buff->from_in_flag)) == 0){
        this->close_flag = 1;
        epoll_del(this,this->fd,EPOLLIN | EPOLLOUT,EPOLL_CTL_DEL);
        return;
    }
    if((n < 0 && errno == EAGAIN | EWOULDBLOCK) || n < 12){
        return;
    }
    
    this->task->task_run(this->buff,this->fd,first_flag);//agent的缓冲区read结束后，开始执行对应任务
    //first_flag = 0;
}
void Agent_connect::agent_write() {
    
    if((this->buff == NULL) || (this->buff->to_in_flag == this->buff->to_out_flag)){
        //cout << "nothing write back to client" << endl;
        return;
        
    }
    //cout << "into Agent_connect agent_write()" << endl;
    int n;
    this->buff->buff_init();
    if((n = this->buff->readout(this->buff->to_out_flag,this->fd)) == 0){
        this->close_flag = 1;
        epoll_del(this,this->fd,EPOLLIN | EPOLLOUT,EPOLL_CTL_DEL);
    }
    /*if((n = this->buff->readout(this->buff->to_out_flag,this->fd)) == -1){
        this->close_flag = 1;
        epoll_del(this,this->fd,EPOLLIN | EPOLLOUT,EPOLL_CTL_DEL);
    }*/
}
