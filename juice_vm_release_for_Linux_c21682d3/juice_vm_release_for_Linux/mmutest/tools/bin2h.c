#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdarg.h>

uint32_t *bin_file_buff;
unsigned char tmp_buf[12] = "0xffffffff,";
int main(int argc,char* argv[])
{
    int fd;
    int rd_ret;
    char *firm_addr = 0;
    char *h_addr = 0;
    unsigned long file_size;
    if(argc < 3){
        printf("bin2h input_bin_file output_h_file");
        exit(1);
    }
    firm_addr = argv[1];
    h_addr = argv[2];

    fd = open(firm_addr, O_RDWR);
	if(fd == -1)
	{
		perror("open file error:");//只有上面的函数设置了error全局错误号，才可使用，会根据error输出对应的错误信息
		return -1;
	}
	printf("fd = %d\n", fd);
	lseek(fd, 0, SEEK_SET);//上面的写操作，文件位置偏移量也会相应的移动，此处将文件偏移到文件开始位置，然后才能读取刚刚输入的内容
    file_size = lseek(fd, 0, SEEK_END);
    bin_file_buff = (uint32_t *)malloc(file_size);
	printf("file_size = %lu\n", file_size);
    lseek(fd, 0, SEEK_SET);
    rd_ret = read(fd, bin_file_buff, file_size);
	if(rd_ret == -1)
	{
		perror("read file error:");
		return -1;
	}
	printf("rd_ret = %d\n",rd_ret);
	close(fd);//关闭文件

    fd = open(h_addr, O_RDWR|O_CREAT);
	if(fd == -1)
	{
		perror("open file error:");//只有上面的函数设置了error全局错误号，才可使用，会根据error输出对应的错误信息
		return -1;
	}
    lseek(fd, 0, SEEK_SET);
    write(fd, "uint32_t bin_file_buf[] = {", 27);
    for(uint64_t i = 0; i < (file_size - 1); i++){
        sprintf(tmp_buf,"0x%08lx,",*(bin_file_buff+i));
        write(fd, tmp_buf, 11);
    }
    sprintf(tmp_buf,"0x%08lx",*(bin_file_buff+(file_size - 1)));
    write(fd, tmp_buf, 10);
    write(fd, "};", 2);

    close(fd);//关闭文件
}