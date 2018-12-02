#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdint.h>

size_t my_write(int fd, char *buf, size_t bytesToWrite) {
    for (size_t bytesWritten = 0; bytesWritten < bytesToWrite;) {
        ssize_t currentWritten = write(fd, buf + bytesWritten, bytesToWrite - bytesWritten);
        if (currentWritten == -1) {
            return 10000000;
        }
        if (currentWritten == 0) {
            return bytesWritten;
        }
        bytesWritten += currentWritten;
    }
    return bytesToWrite;
}

size_t my_read(int fd, char *buf, size_t bytesToRead) {
    for (size_t bytesRead = 0; bytesRead < bytesToRead;) {
        ssize_t currentRead = read(fd, buf + bytesRead, bytesToRead - bytesRead);
        if (currentRead == -1) {
            return 10000000;
        }
        if (currentRead == 0) {
            return bytesRead;
        }
        bytesRead += currentRead;
    }
    return bytesToRead;
}

int compare (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

int make_files(char *buf, int fd) {
    int numberOfFiles = 1;
    for (char c1 = 'a'; c1 <= 'z'; c1++) {
        for (char c2 = 'a'; c2 <= 'z'; c2++) {
            char file[3];
            file[0] = c1;
            file[1] = c2;
            file[2] = '\0';

            char *file_ptr = file;
            int a = open(file_ptr, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (a == -1) {
                return -1;
            }
            size_t read = my_read(fd, buf, 1024*1024*4);
            if (read == -1 || read % 4 != 0) {
                return -1;
            }

            qsort((int*)buf, read / 4, sizeof(int), compare);

            size_t written = my_write(a, buf, read);
            if (written == -1) {
                close(a);
                return -1;
            }
            close(a);
            if (read < 1024*1024*4) {
                return numberOfFiles;
            }
            numberOfFiles++;
        }
    }
}

int Exit(char* in, char* out) {
    int outFile = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (outFile == -1) {
        return 1;
    }
    close(outFile);
    outFile = open(out, O_WRONLY | O_CREAT, 0640);
    if (outFile == -1) {
        return 1;
    }
    int inFile = open(in, O_RDONLY);
    if (inFile == -1) {
        return 1;
    }
    int *buf = malloc(1024*1024*4);
    while (1) {
        size_t read = my_read(inFile, (char*)buf, 1024*1024*4);
        if (read == 10000000) {
            close(inFile);
            close(outFile);
            return 1;
        }
        if (read < 1024*1024*4) {
            my_write(outFile, (char*)buf, read);
            break;
        }
        my_write(outFile, (char*)buf, read);
    }
    close(outFile);
    close(inFile);
    int remove1 = unlink(in);
    if (remove1 == -1){
        return 1; 
    }
    return 0;
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
//    argv[1] = "int.bin";
    int *buf = malloc(1024*1024*4);

    int in = open(argv[1], O_RDONLY);
    if (in < 0) {
        return 1;
    }
    int numberOfFiles = make_files((char *) buf, in);

    if (numberOfFiles == -1) {
        return 1;
    }

    close(in);

    free(buf);

    int i = 0;
    char *mainFilePtr = malloc(3);
    mainFilePtr[0] = 'a';
    mainFilePtr[1] = 'a';
    mainFilePtr[2] = '\0';
    for (char c1 = 'a'; c1 <= 'z'; c1++) {
        for (char c2 = 'a'; c2 <= 'z'; c2++) {
            if (i == numberOfFiles - 1) {
                goto finally;
            }
            if (c1 == 'a' && c2 == 'a') {
                continue;
            }
            int first = open(mainFilePtr, O_RDONLY);
            if (first == -1) {
                return 1;
            }
            char file[3];
            file[0] = c1;
            file[1] = c2;
            file[2] = '\0';
            char *file_ptr = file;
            int second = open(file_ptr, O_RDONLY);
            if (second == -1) {
                close(first);
                return 1;
            }
            char* temp_ptr = malloc(7);
            temp_ptr[0] = 't';
            temp_ptr[1] = 'e';
            temp_ptr[2] = 'm';
            temp_ptr[3] = 'p';
            temp_ptr[4] = c1;
            temp_ptr[5] = c2;
            temp_ptr[6] = '\0';
            int tempFile = open(temp_ptr, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (tempFile == -1) {
                close(first);
                close(second);
                return 1;
            }
            int *buf1 = malloc(1024*1024*4);
            int *buf2 = malloc(1024*1024*4);
            int *bufAns = malloc(1024*1024*4);
            size_t p = 0;

            size_t size1 = 0, size2 = 0;
            int j = 0, k = 0;
            while (1) {
                if (size1 == j) {
                    j = 0;
                    size1 = my_read(first, (char *) buf1, 1024*1024*4) / 4;
                    if (size1 == 0) {
                        break;
                    }
                    if (size1 == 10000000) {
                        close(first);
                        close(second);
                        close(tempFile);
                        free(buf1);
                        free(buf2);
                        free(bufAns);
                        return 1;
                    }
                }
                if (size2 == k) {
                    k = 0;
                    size2 = my_read(second, (char *) buf2, 1024*1024*4) / 4;
                    if (size2 == 0) {
                        break;
                    }
                    if (size2 == 10000000) {
                        close(first);
                        close(second);
                        close(tempFile);
                        free(buf1);
                        free(buf2);
                        free(bufAns);
                        return 1;
                    }
                }
                if (p == 8 / 4) {
                    p = 0;
                    size_t ansSize = my_write(tempFile, (char *) bufAns, 1024*1024*4) / 4;
                    if (ansSize == 10000000) {
                        close(first);
                        close(second);
                        close(tempFile);
                        free(buf1);
                        free(buf2);
                        free(bufAns);
                        return 1;
                    }
                }

                if (buf1[j] < buf2[k]) {
                    bufAns[p] = buf1[j];
                    p++;
                    j++;
                } else {
                    bufAns[p] = buf2[k];
                    p++;
                    k++;
                }
            }

            if (size2 == 0) {
                while (1) {
                    if (size1 == j) {
                        j = 0;
                        size1 = my_read(first, (char *) buf1, 1024*1024*4) / 4;
                        if (size1 == 0) {
                            size_t ansSize = my_write(tempFile, (char *) bufAns, p * 4) / 4;
                            p = 0;
                            if (ansSize == 10000000) {
                                close(first);
                                close(second);
                                close(tempFile);
                                free(buf1);
                                free(buf2);
                                free(bufAns);
                                return 1;
                            }
                            break;
                        }
                        if (size1 == 10000000) {
                            close(first);
                            close(second);
                            close(tempFile);
                            free(buf1);
                            free(buf2);
                            free(bufAns);
                            return 1;
                        }
                    }
                    if (p == 8 / 4) {
                        p = 0;
                        size_t ansSize = my_write(tempFile, (char *) bufAns, 1024*1024*4) / 4;
                        if (ansSize == 10000000) {
                            close(first);
                            close(second);
                            close(tempFile);
                            free(buf1);
                            free(buf2);
                            free(bufAns);
                            return 1;
                        }
                    }
                    bufAns[p] = buf1[j];
                    p++;
                    j++;
                }

            }
            else {
                while (1) {
                    if (size2 == k) {
                        k = 0;
                        size2 = my_read(second, (char *) buf2, 1024*1024*4) / 4;
                        if (size2 == 0) {
                            size_t ansSize = my_write(tempFile, (char *) bufAns, p * 4) / 4;
                            p =0;
                            if (ansSize == 10000000) {
                                close(first);
                                close(second);
                                close(tempFile);
                                free(buf1);
                                free(buf2);
                                free(bufAns);
                                return 1;
                            }
                            break;
                        }
                        if (size2 == 10000000) {
                            close(first);
                            close(second);
                            close(tempFile);
                            free(buf1);
                            free(buf2);
                            free(bufAns);
                            return 1;
                        }
                    }
                    if (p == 8 / 4) {
                        p = 0;
                        size_t ansSize = my_write(tempFile, (char *) bufAns, 1024*1024*4) / 4;
                        if (ansSize == 10000000) {
                            close(first);
                            close(second);
                            close(tempFile);
                            free(buf1);
                            free(buf2);
                            free(bufAns);
                            return 1;
                        }
                    }
                    bufAns[p] = buf2[k];
                    p++;
                    k++;
                }
            }

            close(first);
            close(second);
            close(tempFile);

            int remove1 = unlink(mainFilePtr);
            int remove2 = unlink(file_ptr);
            if (remove1 == -1 || remove2 == -1) {
                free(mainFilePtr);
                free(buf1);
                free(buf2);
                free(bufAns);
                return 1;
            }
            free(mainFilePtr);
            mainFilePtr = temp_ptr;
            free(buf1);
            free(buf2);
            free(bufAns);
            i++;
        }
    }

    finally:
    return Exit(mainFilePtr, argv[1]);


}
