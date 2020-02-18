// copy(s, t)	- 빈 디렉토리 및 단일파일만 복사
// move(s, t)	- 빈 디렉토리 및 단일파일만 이동
// del(s)		- 빈 디렉토리 및 단일파일만 삭제
// xcopy(s, t)	- 하위디렉토리까지 복사
// xmove(s, t)	- 하위디렉토리까지 이동
// xdel(s)	- 하위디렉토리까지 삭제
// create(s)	- 빈 디렉토리 생성
//
// read(f)	- 파일이름이 f인 파일을 읽어서 스트링으로 리턴
// write(s, f)	- 스트링 s를 f로 저장

package com.nuri.kepco.util;

import java.util.*;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;
import java.net.*;
import java.io.*;

import org.apache.log4j.Logger;

public class FileControl
{
	static Logger log = Logger.getLogger("FileControl.class");

    public FileControl()
    {
    }

	public static String read(String f)
	{
		String s = "";
		String temp = "";

		try
		{
			FileInputStream fin = new FileInputStream(f);
			BufferedReader bin = new BufferedReader(new InputStreamReader(fin));

			while((temp = bin.readLine()) != null)
				s += temp + "\n";

			bin.close();
			fin.close();
		}
		catch(IOException e)
		{
			log.debug(e);
		}

		return s;
	}

	public static String urlRead(String furl)
	{
		String s = "";
		String temp = "";
	   	URL fin = null;
	   	URLConnection connection = null;
   		InputStream inStream = null;

		try
		{
      		fin  = new  URL(furl);
    		connection = fin.openConnection();

    		connection.setDoOutput(true); //post방식:true
    		connection.setDoInput(true); //데이타 첨부되는 경우
    		connection.setRequestProperty("Accept","*/*");
    		connection.setRequestProperty("Accept-Charset","euc-kr");
    		connection.setRequestProperty("User-Agent","Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.0; i-NavFourF; .NET CLR 1.1.4322)");

    		inStream = connection.getInputStream();

			BufferedReader bin = new BufferedReader(new InputStreamReader(inStream));

			while((temp = bin.readLine()) != null)
				s += temp + "\n";

			bin.close();
		}
		catch(IOException e)
		{
			log.debug(e);
		}

		return s;
	}

	public static Vector getVtReadFile(String f)
	{
		Vector vt = new Vector();
		String temp = "";

		try
		{
			FileInputStream fin = new FileInputStream(f);
			BufferedReader bin = new BufferedReader(new InputStreamReader(fin));

			while((temp = bin.readLine()) != null){
				vt.addElement(temp);
			}
			bin.close();
			fin.close();
		}
		catch(IOException e)
		{
			log.debug(e);
		}

		return vt;
	}

	public static Vector getVtReadUrl(String furl)
	{
		Vector vt = new Vector();
		String temp = "";

		try
		{
      		URL fin  = new  URL(furl);

			BufferedReader bin = new BufferedReader(new InputStreamReader(fin.openStream()));

			while((temp = bin.readLine()) != null){
				vt.addElement(temp);
			}
			bin.close();
		}
		catch(IOException e)
		{
			log.debug(e);
		}

		return vt;
	}

	public static void write(String s, String f)
	{
		try
		{
			FileOutputStream fout = new FileOutputStream(f);
			DataOutputStream dout = new DataOutputStream(fout);

			dout.writeBytes(s);

			dout.close();
			fout.close();
		}
		catch(IOException e)
		{
			log.debug(e);
		}
	}


	// 단순 파일카피
	// 소스파일이 존재하지 않으면, 1 리턴
    public static int copy(String s, String t)
    {
		File f1 = new File(s);
		int i = 0;

		// 대상 디렉토리가 존재하지 않을 경우, 생성
		create(t);
		del(t);

        try
        {
            if(f1.exists())
            {
	            FileInputStream fin = new FileInputStream(s);
	            FileOutputStream fout = new FileOutputStream(t);
	            byte buffer[] = new byte[1024];
	            int j;
	            while((j = fin.read(buffer)) >= 0)
	                fout.write(buffer, 0, j);

	            fout.close();
	            fin.close();
            }
            else
            	i = 1;
        }
        catch(IOException e)
        {
        	log.debug(e);
        }

        return i;
    }

    // 파일이동(이동할 파일이 없으면 1 리턴)
    public static int move(String s, String t)
    {
		int i = copy(s, t);
		if(i == 0)
			del(s);

    	return i;
    }

    // '빈'디렉토리 및 싱글파일삭제
    // 비어있는 디렉토리만 삭제하고 싶은 경우, 이용도 있음
    // 1 - 삭제할 파일 혹은 디렉토리가 없는 경우,
    // 2 - 하위 디렉토리로 인해 디렉토리 삭제가 불가능한 경우,
    public static int del(String s)
    {
    	File f1 = new File(s);
    	int i = 0;

    	if(f1.exists())
    		if(!f1.delete())
    			i = 2;
    	else
    		i = 1;

    	return i;
    }

    // 디렉토리 및 파일삭제(하위디렉토리 포함) - 재귀함수
    // 1 - 삭제할 디렉토리 없음
    public static int xdel(String t)
    {
    	File f1 = new File(t);
    	int i = 0;
    	if(f1.exists())
    	{
    		// 하위디렉토리(혹은 파일)로 인해 삭제가 안된다면,
    		if(!f1.delete())
    		{
    			String[] fl = f1.list();
    			for(int j = 0; j < fl.length; j++)
    				xdel(t.endsWith("/") ? t+fl[j] : t+"/"+fl[j]);
    			f1.delete();
    		}
    	}
    	else
    		i = 1;
    	return i;
    }
    
    // 디렉토리 생성(중간 디렉토리까지 모두 생성됨!)
    public static void create(String s)
    {
        File file = new File(s);
        if(!file.exists()){
        	file.mkdirs();
        }
    }

    // 디렉토리 및 파일카피(하위디렉토리 포함) - 재귀함수
    // 결국, 최종 파일간 카피는 copy(s, t)이용
    // 0 - 정상처리
    // 1 - 디렉토리 혹은 파일 없음
    public static int xcopy(String s, String t)
    {
    	File f1 = new File(s);
		int i = 0;

    	// 파일객체 존재여부 확인
    	if(f1.exists())
    	{
    		if(f1.isDirectory())
    		{
    			create(t);
    			String[] sa = f1.list();
    			for(int j = 0; j < sa.length; j++)
    			{
    				xcopy(s.endsWith("/") ? s+sa[j] : s+"/"+sa[j], t.endsWith("/") ? t+sa[j] : t+"/"+sa[j]);
    			}
    		}
    		else
				copy(s, t);
    	}
    	else
    		i = 1;

    	return i;
    }

    // 0 - 정상이동
    // 1 - 소스 디렉토리 혹은 파일 없음
    // xcopy와 xdel이용
    public static int xmove(String s, String t)
    {
    	int i = 0;

    	i = xcopy(s, t);
    	xdel(s);

    	return i;
    }
    
    
    public static void zip(String zipFileName, String fileName, String filePath) throws IOException
    {
    	byte[] buffer = new byte[1024];
    		 
		FileOutputStream fos = new FileOutputStream(filePath + "/" + zipFileName);
		ZipOutputStream zos = new ZipOutputStream(fos);
		ZipEntry ze= new ZipEntry(fileName);
		zos.putNextEntry(ze);
		FileInputStream in = new FileInputStream(filePath + "/" + fileName);
 
		int len;
		while ((len = in.read(buffer)) > 0) {
    		zos.write(buffer, 0, len);
    	}
   		in.close();
  		zos.closeEntry();
   	
  		zos.close();   	
    }
}