#ifndef VFILE_H
#define VFILE_H

#include <stdio.h>

#define VFILE_LINE_MAX 255

class VFile {
public:
  VFile();
  ~VFile();
  int open(const char *path, const char *mode );
  void close();
  int size();
  int read(void *buf, int len);
  int write(void *buf, int len);
  int readLine( char *buf);
private:
  FILE *m_fp;
  int m_size;
};

#endif
