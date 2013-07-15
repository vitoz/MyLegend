#include "VFile.h"
#include <stdio.h>
#include "Util.h"

int VFile::open(const char *path, const char *mode )
{
  if(m_fp)
  {
    fclose(m_fp);
    m_fp = NULL;
  }

  m_fp = fopen(path, mode);
  if(m_fp == NULL)
  {
    LOG("VFile::open() path:%s,mode:%s\n", path, mode);
    return -1;
  }

  fseek(m_fp, 0, SEEK_END);
  m_size = ftell(m_fp);
  fseek(m_fp, 0, SEEK_SET);

  return 0;
}

int VFile::size()
{
  if(m_fp == NULL)
  {
    LOG("VFile::size() m_fp is null\n");
    return -1;
  }

  return m_size;
}

int VFile::read( void *buf, int len )
{
  if(m_fp == NULL)
  {
    LOG("VFile::read() m_fp is null\n");
    return -1;
  }

  return fread(buf, 1, len, m_fp);
}

int VFile::write( void *buf, int len )
{
  if(m_fp == NULL)
  {
    LOG("VFile::write() m_fp is null\n");
    return -1;
  }

  return fwrite(buf, 1, len, m_fp);
}

VFile::VFile()
{
  m_fp = NULL;
  m_size = 0;
}

VFile::~VFile()
{
  close();
}

void VFile::close()
{
  if(m_fp)
  {
    fclose(m_fp);
    m_fp = NULL;
  }
}

int VFile::readLine( char *buf)
{
  if(m_fp == NULL)
  {
    LOG("havn't open file yet!");
  }
  if(fgets(buf, VFILE_LINE_MAX, m_fp) == NULL)
  {
    return -1;
  }

  return 0;
}

