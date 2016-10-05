#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hdfs.h" 

int main(int argc, char **argv)
{
    if (argc != 4) {
        fprintf(stderr, "Usage: hdfs_write <host> <port> <filename>\n");
        return 1;
    }
    
    const char* writePath = argv[3];
    const char* host = argv[1];
    tSize port = strtoul(argv[2], NULL, 10);
    
    hdfsFS fs = hdfsConnect(host, port);
    if (!fs) {
        fprintf(stderr, "Failed to connect to hdfs!\n");
        return 1;
    } 

  hdfsFile writeFile = hdfsOpenFile(fs, writePath, O_WRONLY|O_CREAT, 0, 0, 0);

  if(!writeFile) {
    fprintf(stderr, "Failed to open %s for writing!\n", writePath);
    //exit(-1);
    return 0;
  }
  const char* buffer = "Hello, World!";

  tSize num_written_bytes = hdfsWrite(fs, writeFile, (void*)buffer, strlen(buffer)+1);
  printf("written %d bytes!\n", num_written_bytes);
  if (hdfsFlush(fs, writeFile)) {
    fprintf(stderr, "Failed to 'flush' %s\n", writePath); 
    //exit(-1);
    return 0;
  }
  hdfsCloseFile(fs, writeFile);
}
