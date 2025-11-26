````bash #include <iostream>
#include <string>
#include <fcntl.h> // For open flags like O_WRONLY, O_CREAT, O_TRUNC
#include <unistd.h> // For write(), close()
#include <vector>
#include <initializer_list>



class FileActions {
    private:
    std::string path;

    int* fd = new int; // allocated in heap
    int *& fd_ptr = fd; 
    std::vector<std::pair<std::string, int>> actions_;

    public:
    FileActions(std::string obj){ // default constructor
        path = obj;
        *fd = open(path.c_str(), O_RDWR);
        if(*fd < 0){
            perror("Open failed!:(\n");
            return;
        }
        else{ /* do nothing */}
    }
    FileActions(const FileActions& copy){ //copy constructor
        actions_ = copy.actions_; // copy vector
        fd = new int(*copy.fd); // deep copy of fd
    }

    ~FileActions(){ // destructor
        if(*fd >= 0){
        close(*fd);
        }
        else{ /* do nothing*/}
        delete fd;
    }
    void registerActions(std::initializer_list<std::pair<std::string, int>> list){
        for(auto& act : list){
            actions_.push_back(act);
        }
    }
    void execute(void){
        for(auto& act : actions_){
            switch(act.second){
                case 0: // close
                if(*fd >= 0){
                    close(*fd);
                    *fd = -1;
                    std::cout << "File closed(:\n";
                }
                else{ /* do nothing*/ }
                break;
                
                case 1: // read
                if(*fd >= 0){
                    char buffer[10];
                    int n = read(*fd, buffer, sizeof(buffer));
                    for (int i = 0; i < n; i++){
                    std::cout << buffer[i];
                    }
                    std::cout << std::endl;
                }
                else{ /* do nothing*/ }
                break;

                case 2: // write
                if(*fd >= 0){
                write(*fd, "1", 1);
                std::cout << "Wrote [1] successfully(:" << std::endl;
                }
                else{ /*do nothing*/}
                break;

                default:
                break;
            }
        }
    }
    void FileActions_on(){
        write(*fd, "1", 1);
    }
};

int main(){
    FileActions fa("/sys/class/leds/input7::capslock/brightness");
    fa.registerActions({{"Write", 2}, {"Read", 1}, {"Close", 0}});
    fa.execute();
    return 0;
}
```
