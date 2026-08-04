#define MAGIC_NUMBER 0xF1

#define GET_BUFFER_LENGTH _IOR(MAGIC_NUMBER, 1, char )//_IOR(type,nr,size)

#define CLR_BUFFER _IO(MAGIC_NUMBER, 2)//_IO(type,nr)

#define FILL_BUFFER _IOW(MAGIC_NUMBER, 3, char )//_IOWR(type,nr,size)