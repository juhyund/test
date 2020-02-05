package com.nuri.kepco.fep.util;


public class FileInfo implements java.io.Serializable
{
    private String fileDate = null;
    private String fileName = null;
    private long fileSize = 0;

    public FileInfo() { }

    public FileInfo(String fileDate, String fileName, long fileSize) 
    { 
        this.fileDate = fileDate;
        this.fileName = fileName;
        this.fileSize = fileSize;
    }

    public String getFileDate()
    {
        return fileDate;
    }
    public void setFileDate(String fileDate)
    {
        this.fileDate = fileDate;
    }

    public String getFileName()
    {
        return fileName;
    }
    public void setFileName(String fileName)
    {
        this.fileName = fileName;
    }

    public long getFileSize()
    {
        return fileSize;
    }
    public void setFileSize(long fileSize)
    {
        this.fileSize = fileSize;
    }

    public String toString()
    {
        StringBuffer sb = new StringBuffer();
        sb.append("file info[");
        sb.append("(fileDate=").append(getFileDate()).append("),");
        sb.append("(fileName=").append(getFileName()).append("),");
        sb.append("(fileSize=").append(getFileSize()).append(')');
        sb.append("]\n");

        return sb.toString();
    }
}
