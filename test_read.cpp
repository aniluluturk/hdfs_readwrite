#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hdfs.h" 

int main(int argc, char **argv) {

    if (argc != 5) {
        fprintf(stderr, "Usage: hdfs_read <host> <port> <filename> <filesize>\n");
        return 1;
    }
    
    const char* rfile = argv[3];
    const char* host = argv[1];
    tSize port = strtoul(argv[2], NULL, 10);
    tSize bufferSize = strtoul(argv[4], NULL, 10);
    
    hdfsFS fs = hdfsConnect(host, port); // ("hostname.com", 8020);
    if (!fs) {
        fprintf(stderr, "Failed to connect to hdfs!\n");
        return 1;
    } 
   
    hdfsFile readFile = hdfsOpenFile(fs, rfile, O_RDONLY, bufferSize, 0, 0);
    if (!readFile) {
        fprintf(stderr, "Failed to open %s for reading!\n", rfile);
        return 1;
    }

    // buffer to read file into
    char* buffer = (char *) malloc(sizeof(char) * bufferSize);
    if(buffer == NULL) {
        return 1;
    }
    
    // read from the file
    tSize curSize = bufferSize;
    for (; curSize == bufferSize;) {
        curSize = hdfsRead(fs, readFile, (void*)buffer, curSize);
    }
    
    printf("%s", buffer);
    free(buffer);
    hdfsCloseFile(fs, readFile);
    hdfsDisconnect(fs);

    return 0;
}
